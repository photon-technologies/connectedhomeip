# Photon Fork Changes — connectedhomeip (rebase guide)

**Purpose:** exact record of every Photon change to this connectedhomeip fork, so a future
rebase/sync onto a newer upstream can be reproduced precisely.

- **Fork base:** branch `fresh-v1.4.0` (upstream CHIP **1.4.0**). Categories A and B were
  committed on top of `fresh-v1.4.0-photon.6` (`8392e7fec3`); before that they existed only as
  uncommitted edits in one local checkout, so the app's CHIP libs could not be rebuilt from any
  fork commit.
- **Consumed by:** the Android app `fresh-android-app`, which vendors the built
  `libCHIPController.so` (×4 ABIs) + `CHIPController.jar` + `libc++_shared.so` (×4) under
  `app/thirdparty/connectedhomeip/libs/`.
- Last updated: 2026-10-05.

---

## TL;DR rebase checklist

1. **Re-apply Category A verbatim** — the fabric-GC JNI/Java. These are Photon-only; upstream
   will never have them. They are the only *functional* product change.
2. **Category B — check upstream first.** These are upstream's own Android NDK-r28 / SDK-34 /
   JDK-17 toolchain modernization, backported onto our older 1.4.0 tree. If the rebase target
   already contains them, **take upstream's versions and drop ours.** If not, re-apply ours.
3. **Category C — ignore/revert** (file-mode flip + submodule dirtiness; not real changes).
4. **Category D — separate workstreams** (iOS), out of scope here.
5. **Rebuild 4 ABIs + re-vendor** into the app (see "Build & re-vendor recipe").
6. **Re-run on-device verification** (commissioning end-to-end, fabric-GC, 16 KB) — per the
   matter-commissioning skill, an SDK bump requires re-validating callback/ICD paths.

---

## Category A — Photon-only additions (RE-APPLY ON EVERY REBASE)

Implements **Matter fabric-table garbage collection**: removing a home or logging out never
freed the home's fabric from CHIP's `FabricTable`, so fabrics accumulated to
`CHIP_CONFIG_MAX_FABRICS` (16) and bricked all further commissioning. These JNI methods let the
app delete fabrics (by fabric-id, or all) from the process-wide shared `FabricTable`.

Two files. Both are pure additions (no upstream lines modified), so they re-apply cleanly.

### A1 — `src/controller/java/CHIPDeviceController-JNI.cpp`

**(a) Three includes** (add alongside the existing controller/credentials/transport includes):

```cpp
#include <controller/CHIPDeviceControllerFactory.h>   // DeviceControllerFactory::GetInstance().GetSystemState()
#include <credentials/FabricTable.h>                   // FabricTable::Delete / DeleteAllFabrics / iteration
#include <transport/SessionManager.h>                  // SessionManager::ExpireAllSessionsForFabric
```

**(b) Two JNI methods** — insert immediately after the `shutdownCommissioning` JNI_METHOD:

```cpp
JNI_METHOD(void, deleteAllFabricsFromTable)(JNIEnv * env, jobject self, jlong handle)
{
    chip::DeviceLayer::StackLock lock;

    // Logout: clears EVERY fabric (incl. prior-session ones with no live
    // controller) from the shared FabricTable in one shot. Leaves the in-memory
    // table empty (count 0, indices reusable) -- next login starts clean with no
    // factory teardown or process restart.
    const DeviceControllerSystemState * systemState = DeviceControllerFactory::GetInstance().GetSystemState();
    VerifyOrReturn(systemState != nullptr && !systemState->IsShutDown() && systemState->Fabrics() != nullptr,
                   ChipLogError(Controller, "deleteAllFabricsFromTable(): no live system state"));

    if (systemState->SessionMgr() != nullptr)
    {
        for (const auto & fabric : *systemState->Fabrics())
        {
            systemState->SessionMgr()->ExpireAllSessionsForFabric(fabric.GetFabricIndex());
        }
    }

    systemState->Fabrics()->DeleteAllFabrics();
    ChipLogProgress(Controller, "deleteAllFabricsFromTable: removed all fabrics");
}

JNI_METHOD(void, deleteFabricByFabricId)(JNIEnv * env, jobject self, jlong handle, jlong fabricIdJ)
{
    chip::DeviceLayer::StackLock lock;
    const FabricId fabricId = static_cast<FabricId>(fabricIdJ);

    // Delete the fabric whose Matter Fabric-ID matches, regardless of which
    // controller is active. Lets a home be deleted from "Manage Homes" (a
    // NON-active home) without disturbing the active home's fabric. The app's
    // model is one unique fabric-id per home, so the match is unambiguous.
    const DeviceControllerSystemState * systemState = DeviceControllerFactory::GetInstance().GetSystemState();
    VerifyOrReturn(systemState != nullptr && !systemState->IsShutDown() && systemState->Fabrics() != nullptr,
                   ChipLogError(Controller, "deleteFabricByFabricId(): no live system state"));

    FabricTable * fabricTable = systemState->Fabrics();
    FabricIndex targetIndex   = kUndefinedFabricIndex;
    for (const auto & fabricInfo : *fabricTable)
    {
        if (fabricInfo.GetFabricId() == fabricId)
        {
            targetIndex = fabricInfo.GetFabricIndex();
            break;
        }
    }
    VerifyOrReturn(targetIndex != kUndefinedFabricIndex,
                   ChipLogProgress(Controller, "deleteFabricByFabricId(0x%llx): no matching fabric (already removed?)",
                                   static_cast<unsigned long long>(fabricId)));

    if (systemState->SessionMgr() != nullptr)
    {
        systemState->SessionMgr()->ExpireAllSessionsForFabric(targetIndex);
    }
    CHIP_ERROR err = fabricTable->Delete(targetIndex);
    VerifyOrReturn(err == CHIP_NO_ERROR,
                   ChipLogError(Controller, "deleteFabricByFabricId: Delete(0x%x) failed: %" CHIP_ERROR_FORMAT,
                                static_cast<unsigned>(targetIndex), err.Format()));
    ChipLogProgress(Controller, "deleteFabricByFabricId: removed fabric id 0x%llx (index 0x%x)",
                    static_cast<unsigned long long>(fabricId), static_cast<unsigned>(targetIndex));
}
```

> Relies on `using namespace chip;` + `using namespace chip::Controller;` already at the top of
> this file (gives `FabricId`, `FabricIndex`, `kUndefinedFabricIndex`, `DeviceControllerFactory`,
> `DeviceControllerSystemState`, `FabricTable` unqualified).

> **Note:** the app uses `deleteFabricByFabricId` for delete-home and `deleteAllFabricsFromTable`
> for logout. (An earlier index-based `deleteFabricFromTable(int)` was added, then removed as unused.)

### A2 — `src/controller/java/src/chip/devicecontroller/ChipDeviceController.java`

**(a) Two public methods** — add after the `shutdownCommissioning()` method:

```java
  /**
   * Deletes ALL fabrics from the controller's shared fabric table (in-memory + persistent storage),
   * including fabrics persisted by prior sessions that no live controller references. Intended for
   * logout / full reset.
   */
  public void deleteAllFabricsFromTable() {
    deleteAllFabricsFromTable(deviceControllerPtr);
  }

  /**
   * Deletes the fabric whose Matter Fabric-ID matches {@code fabricId} from the controller's shared
   * fabric table (in-memory + persistent storage), regardless of which controller is active. Use
   * this to remove a specific home's fabric — including a home that is not the currently active one.
   * No-op if no fabric matches. The AndroidKeyStore alias is removed separately.
   */
  public void deleteFabricByFabricId(long fabricId) {
    deleteFabricByFabricId(deviceControllerPtr, fabricId);
  }
```

**(b) Two native declarations** — add next to the `shutdownCommissioning` native decl:

```java
  private native void deleteAllFabricsFromTable(long deviceControllerPtr);

  private native void deleteFabricByFabricId(long deviceControllerPtr, long fabricId);
```

---

## Category B — Upstream toolchain backports (DROP IF TARGET UPSTREAM ALREADY HAS THEM)

These are **not Photon inventions** — they are upstream connectedhomeip's own modernization of
the Android build to **NDK r28.2 / SDK 34 / JDK 17 / Gradle 8.7**, backported onto our older
CHIP 1.4.0 tree so it builds with that toolchain (needed for 16 KB-page alignment). The upstream
commit(s) touched `build/chip/java/BUILD.gn`, `scripts/build/builders/android.py`, and
`docs/platforms/android/android_building.md` together.

**On rebase:** if the target upstream is new enough to already contain this modernization
(check whether `build/chip/java/BUILD.gn`'s `shared_cpplib` already reads from
`toolchains/llvm/prebuilt/.../sysroot/usr/lib/<triple>/libc++_shared.so`), then **discard our
versions of B1–B3 and take upstream's.** Only re-apply ours if rebasing onto a tree that still
predates the modernization.

Upstream source of each file (all three are byte-identical to upstream at that commit):

| File | Upstream commit |
|---|---|
| `build/chip/java/BUILD.gn` | `8adaf97c15` (#40613), on top of `cbc3feed2e` (#40455, NDK r28c + 16 KB) |
| `scripts/build/builders/android.py` | `8adaf97c15` (#40613), on top of `eef3dff349` (#40476) |
| `docs/platforms/android/android_building.md` | `f5389c21eb` (#40616) |

Not taken from those upstream commits: #40455's `-Wl,-z,max-page-size=16384` in
`src/controller/java/BUILD.gn` (NDK r28 already aligns 64-bit segments to 16 KB by default; check
with `llvm-readelf` as in the recipe), its `InetInterfaceImpl.cpp` unused-variable cleanup (covered
by `treat_warnings_as_errors = false`), and #40616's API-level bump in the BUILD.gn files. So the
Java targets still compile against `platforms/android-30/android.jar`, even though B3's doc text
says SDK 34.

### B1 — `build/chip/java/BUILD.gn`  (the load-bearing one)
Old code copied `libc++_shared.so` from the **pre-r25** path
`${android_ndk_root}/sources/cxx-stl/llvm-libc++/libs/${android_abi}/` — which **NDK r28 removed**,
breaking the `:java` target (and thus `CHIPController.jar`). The replacement:
- derives `android_ndk_host_platform` from `host_os` (e.g. `darwin-x86_64`),
- maps `current_cpu` → toolchain triple (`arm`→`arm-linux-androideabi`, `arm64`→`aarch64-linux-android`,
  `x64`→`x86_64-linux-android`, `x86`→`i686-linux-android`, `riscv64`→`riscv64-linux-android`),
- copies from `${android_ndk_root}/toolchains/llvm/prebuilt/${host}/sysroot/usr/lib/<triple>/libc++_shared.so`.

The `print(...)` statements that fire on every `gn gen` are upstream's own (still present on
upstream `master`). They are kept so the file stays byte-identical to upstream for rebases.

### B2 — `scripts/build/builders/android.py`
sdkmanager discovery across modern (`cmdline-tools/latest`), versioned (`cmdline-tools/10.0`),
and legacy (`tools/bin`) SDK layouts + a license-acceptance helper. **Off the path we actually
build with** (`gn gen` + `ninja` directly; this file is only used by `build_examples.py`), so it
does not affect the vendored artifacts. Pure convenience/robustness backport.

### B3 — `docs/platforms/android/android_building.md`
Doc bump: SDK 26→34, NDK 23.2.8568313→28.2.13676358, Gradle 7.3.3→8.7, JDK 11→17. Doc only.

---

## Category E — Generated code must be committed with its IDL

`3c1db1718a` (#14) added the `FreshWaterHeaterController` `NotifyError` event to
`controller-clusters.matter` and listed its Kotlin event classes in both `files.gni` files, but
never committed the two `FreshWaterHeaterControllerClusterNotifyErrorEvent.kt` files. Every
Android build of `photon.6` then failed at `ninja` with "missing and no known rule to make it".
The files were added afterwards, generated with `scripts/codegen.py` (`java-class` /
`kotlin-class`) and formatted with `ktfmt 0.51 --google-style`, the same steps
`scripts/tools/zap_regen_all.py` runs. That process reproduces the committed `FreshMideaController`
siblings byte-for-byte.

After changing a Photon cluster, regenerate and **commit the new untracked files too**
(`git status --untracked-files=all`). `git commit -a` silently skips them.

---

## Category C — Incidental, not real changes (ignore / revert on rebase)

- **`scripts/py_matter_idl/setup.py`** — file **mode** flip `100644 → 100755` only (no content
  change). Revert with `chmod 644 scripts/py_matter_idl/setup.py` (or ignore).
- **`third_party/*` submodules** showing dirty (`asr`, `boringssl`, `infineon`, `mbed-*`,
  `mt793x_sdk/*`, …) — submodule working-tree state from checkout/build, **not Photon edits**.
  `git submodule update --init` resets them. Do **not** commit these.

---

## Category D — Separate workstreams (NOT part of this Android fabric-GC work)

- **`src/darwin/PhotonMatter/`** (untracked) — iOS Photon work (separate codebase/team). iOS uses
  the factory-reset pattern (`stopControllerFactory` / `MTRStorage` wipe / `startControllerFactory`)
  for the equivalent fabric cleanup; it does **not** use these Android JNI methods. Document/track
  separately.
- **`ChipLogError-Audit.md`** (untracked) — audit note from prior work; unrelated to fabric-GC.

---

## Build & re-vendor recipe (after a rebase)

**Toolchain (validated):** NDK **28.2.13676358**, JDK **17** (e.g. corretto-17 / temurin-17),
`kotlinc` on PATH (2.1.x), Android SDK **34** plus the SDK platform **`android-30`** (the Java
targets compile against `platforms/android-30/android.jar`). macOS host: NDK prebuilt is
`darwin-x86_64`.

**One-time checkout setup** (a fresh clone has none of this):
```bash
./scripts/checkout_submodules.py --platform android --shallow
source scripts/bootstrap.sh                   # creates .environment + build_overrides/pigweed_environment.gni
third_party/java_deps/set_up_java_deps.sh     # jsr305, gson, kotlin-stdlib, … into third_party/java_deps/artifacts
```

**Per-ABI `args.gn`** (in each `out/android-<cpu>-chip-tool/`; NOT committed — `out/` is build
output). `<cpu>` ∈ {`arm64`,`arm`,`x64`,`x86`}:
```gn
target_os = "android"
target_cpu = "arm64"   # arm64 | arm | x64 | x86
android_ndk_root = "<ANDROID_HOME>/ndk/28.2.13676358"
android_sdk_root = "<ANDROID_HOME>"
chip_enable_nfc_based_commissioning = true
chip_build_controller_dynamic_server = true
treat_warnings_as_errors = false
enable_im_pretty_print = false
```
> `treat_warnings_as_errors = false` is required because NDK r28's clang-19 emits new warnings
> (e.g. `-Wunused-but-set-variable`) that `-Werror` makes fatal on the **1.4.0** tree. After
> rebasing onto a newer upstream that compiles cleanly under clang-19, this can likely be dropped.
>
> `enable_im_pretty_print = false` turns off `CHIP_CONFIG_IM_PRETTY_PRINT`, which defaults on
> because `is_debug` is true and floods logcat with every parsed read/write/invoke/report payload.
> The libs vendored in the app were built with it off.

**Build (per ABI):**
```bash
export ANDROID_HOME=<sdk>; export ANDROID_NDK_HOME=$ANDROID_HOME/ndk/28.2.13676358
export JAVA_HOME=<jdk17>; export PATH="$JAVA_HOME/bin:$PATH"
source scripts/activate.sh
gn gen out/android-<cpu>-chip-tool          # only needed when args.gn / BUILD.gn changed
ninja -C out/android-<cpu>-chip-tool src/controller/java:jni src/controller/java:java
# capture RC=$? immediately after ninja (a ninja wrapper can mask its exit code)
```
- `:jni`  → `out/android-<cpu>-chip-tool/lib/jni/<abi>/libCHIPController.so` (+ `libc++_shared.so`)
- `:java` → `.../lib/src/controller/java/CHIPController.jar`

**Verify the rebuilt `.so`** carries the new symbols:
```bash
$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/darwin-x86_64/bin/llvm-nm -D <libCHIPController.so> \
  | grep -E "deleteFabricFromTable|deleteAllFabricsFromTable|deleteFabricByFabricId"
```
…and that 64-bit libs are 16 KB-aligned (`llvm-readelf -l … | grep LOAD` → `0x4000`; 32-bit stays `0x1000`, which is correct).

**Re-vendor into the app** (`fresh-android-app`):
- `libCHIPController.so` (×4) → `app/thirdparty/connectedhomeip/libs/jniLibs/<abi>/`
  (abi map: arm64→arm64-v8a, arm→armeabi-v7a, x64→x86_64, x86→x86)
- `libc++_shared.so` (×4) → same dirs
- `CHIPController.jar` → `app/thirdparty/connectedhomeip/libs/`

The app calls these via `ChipClient` → `FabricGarbageCollector` (delete-home / logout). After
re-vendoring, run the app's `./gradlew testDebugUnitTest lint assembleDebug` and the on-device
fabric-GC checks.

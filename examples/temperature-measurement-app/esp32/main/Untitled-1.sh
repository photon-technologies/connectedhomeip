===============================================================
==================== ESP32 CORE DUMP START ====================
The ROM ELF file won't load automatically since it was not found for the provided chip type.

Crashed task handle: 0x3ffe1fe8, name: 'wifi', GDB name: 'process 1073618920'
Crashed task is not in the interrupt context

================== CURRENT THREAD REGISTERS ===================
exccause       0x1c (LoadProhibitedCause)
excvaddr       0x0
epc1           0x400d94a3
epc2           0x0
epc3           0x40008544
epc4           0x40008544
epc5           0x0
epc6           0x0
eps2           0x0
eps3           0x60020
eps4           0x60020
eps5           0x0
eps6           0x0
pc             0x4009ccb4          0x4009ccb4 <esf_buf_alloc+244>
lbeg           0x4000c2e0          1073791712
lend           0x4000c2f6          1073791734
lcount         0xffffffff          4294967295
sar            0x0                 0
ps             0x60020             393248
threadptr      <unavailable>
br             <unavailable>
scompare1      <unavailable>
acclo          <unavailable>
acchi          <unavailable>
m0             <unavailable>
m1             <unavailable>
m2             <unavailable>
m3             <unavailable>
expstate       <unavailable>
f64r_lo        <unavailable>
f64r_hi        <unavailable>
f64s           <unavailable>
fcr            <unavailable>
fsr            <unavailable>
a0             0x8009cf32          -2146840782
a1             0x3ffe1e40          1073618496
a2             0x3ffe4920          1073629472
a3             0x3ffbf2fc          1073476348
a4             0x0                 0
a5             0x0                 0
a6             0x0                 0
a7             0x3ffbf39c          1073476508
a8             0x184               388
a9             0x3ffe1e20          1073618464
a10            0x0                 0
a11            0x3ffd719c          1073574300
a12            0x1fd               509
a13            0x60823             395299
a14            0x3142f36           51654454
a15            0xcdcd              52685

==================== CURRENT THREAD STACK =====================
#0  0x4009ccb4 in esf_buf_alloc ()
#1  0x4009cf32 in wDev_IndicateFrame ()
#2  0x4009d4f4 in wDev_ProcessRxSucData ()
#3  0x4009d5c9 in wdevProcessRxSucDataAll ()
#4  0x40098a18 in ppTask ()
#5  0x400901fc in vPortTaskWrapper (pxCode=0x40098894 <ppTask>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

======================== THREADS INFO =========================
  Id   Target Id          Frame 
* 1    process 1073618920 0x4009ccb4 in esf_buf_alloc ()
  2    process 1073446072 0x4008e142 in esp_cpu_wait_for_intr () at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_hw_support/cpu.c:64
  3    process 1073445716 0x4008e142 in esp_cpu_wait_for_intr () at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_hw_support/cpu.c:64
  4    process 1073427804 vTaskDelay (xTicksToDelay=8) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
  5    process 1073607076 0x4000bff0 in ?? ()
  6    process 1073488004 0x4000bff0 in ?? ()
  7    process 1073446428 0x40090abd in prvProcessTimerOrBlockTask (xNextExpireTime=5170, xListWasEmpty=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/xtensa/include/xt_utils.h:41
  8    process 1073676940 vTaskDelay (xTicksToDelay=500) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
  9    process 1073437680 vTaskDelay (xTicksToDelay=100) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
  10   process 1073507296 vTaskDelay (xTicksToDelay=100) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
  11   process 1073487416 0x4000bff0 in ?? ()
  12   process 1073660140 0x4000bff0 in ?? ()
  13   process 1073442932 0x4000bff0 in ?? ()
  14   process 1073602384 0x4000bff0 in ?? ()
  15   process 1073444316 0x4000bff0 in ?? ()
  16   process 1073436204 0x4000bff0 in ?? ()
  17   process 1073695420 0x4000bff0 in ?? ()
  18   process 1073436560 0x4000bff0 in ?? ()
  19   process 1073432004 0x4000bff0 in ?? ()
  20   process 1073444672 0x4000bff0 in ?? ()
  21   process 1073507836 0x4000bff0 in ?? ()
  22   process 1073436916 0x4000bff0 in ?? ()


       TCB             NAME PRIO C/B  STACK USED/FREE
---------- ---------------- -------- ----------------
0x3ffe1fe8             wifi    23/23         512/6140
0x3ffb7cb8            IDLE1      0/0         416/1104
0x3ffb7b54            IDLE0      0/0         416/1108
0x3ffb355c             tone      3/3         400/2584
0x3ffdf1a4              tiT    18/18         528/3040
0x3ffc2084        mqtt_task      5/5         944/5192
0x3ffb7e1c          Tmr Svc      1/1         368/3716
0x3fff028c  PeriodicPowerUp      5/5         448/2620
0x3ffb5bf0  power_measure_t      5/5         416/3676
0x3ffc6be0          BBG_CTL      5/5         400/3680
0x3ffc1e38  photon_queue_ta      5/5         512/6644
0x3ffec0ec             CHIP    10/10         576/7608
0x3ffb7074             ipc0    24/24          448/560
0x3ffddf50          sys_evt    20/20         544/4052
0x3ffb75dc             ipc1    24/24          448/568
0x3ffb562c           HEATER      5/5         496/3192
0x3fff4abc  IN_EventReceive      5/5         528/3160
0x3ffb5790  BOOST_SMART_STA      5/5         496/3200
0x3ffb45c4            RELAY      5/5         496/3200
0x3ffb7740        esp_timer    22/22         448/2108
0x3ffc6dfc          DISPLAY      5/5         496/3200
0x3ffb58f4            RESET      5/5         496/3200

==================== THREAD 1 (TCB: 0x3ffe1fe8, name: 'wifi') =====================
#0  0x4009ccb4 in esf_buf_alloc ()
#1  0x4009cf32 in wDev_IndicateFrame ()
#2  0x4009d4f4 in wDev_ProcessRxSucData ()
#3  0x4009d5c9 in wdevProcessRxSucDataAll ()
#4  0x40098a18 in ppTask ()
#5  0x400901fc in vPortTaskWrapper (pxCode=0x40098894 <ppTask>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 2 (TCB: 0x3ffb7cb8, name: 'IDLE1') =====================
#0  0x4008e142 in esp_cpu_wait_for_intr () at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_hw_support/cpu.c:64
#1  0x401feb20 in esp_vApplicationIdleHook () at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_system/freertos_hooks.c:58
#2  0x4009156a in prvIdleTask (pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:4350
#3  0x400901fc in vPortTaskWrapper (pxCode=0x400914e4 <prvIdleTask>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 3 (TCB: 0x3ffb7b54, name: 'IDLE0') =====================
#0  0x4008e142 in esp_cpu_wait_for_intr () at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_hw_support/cpu.c:64
#1  0x401feb20 in esp_vApplicationIdleHook () at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_system/freertos_hooks.c:58
#2  0x4009156a in prvIdleTask (pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:4350
#3  0x400901fc in vPortTaskWrapper (pxCode=0x400914e4 <prvIdleTask>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 4 (TCB: 0x3ffb355c, name: 'tone') =====================
#0  vTaskDelay (xTicksToDelay=8) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
#1  0x400dd2dd in Tone::task (args=0x3ffc5134 <WH+988>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/hardware/tone.h:156
#2  0x400901fc in vPortTaskWrapper (pxCode=0x400dd244 <Tone::task(void*)>, pvParameters=0x3ffc5134 <WH+988>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 5 (TCB: 0x3ffdf1a4, name: 'tiT') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffde2b8) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffde26c, pvBuffer=0x3ffdf0e0, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x40175095 in sys_arch_mbox_fetch (mbox=0x3ffd5548 <tcpip_mbox>, msg=0x3ffdf0e0, timeout=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/lwip/port/freertos/sys_arch.c:313
#5  0x40166213 in tcpip_timeouts_mbox_fetch (mbox=<optimized out>, msg=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/lwip/lwip/src/api/tcpip.c:104
#6  tcpip_thread (arg=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/lwip/lwip/src/api/tcpip.c:142
#7  0x400901fc in vPortTaskWrapper (pxCode=0x4016618c <tcpip_thread>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 6 (TCB: 0x3ffc2084, name: 'mqtt_task') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffc2350) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x40090045 in xQueueSemaphoreTake (xQueue=0x3ffc2304, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1853
#4  0x40174faa in sys_arch_sem_wait (sem=0x3ffc22f4, timeout=1000) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/lwip/port/freertos/sys_arch.c:175
#5  0x40176624 in lwip_select (maxfdp1=55, readset=0x3ffdaed8 <vflash_mem+1656>, writeset=0x0, exceptset=0x3ffdaed0 <vflash_mem+1648>, timeout=0x3ffdaec0 <vflash_mem+1632>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/lwip/lwip/src/api/sockets.c:2142
#6  0x400d7f91 in esp_vfs_select (nfds=55, readfds=0x3ffdaed8 <vflash_mem+1656>, writefds=0x0, errorfds=0x3ffdaed0 <vflash_mem+1648>, timeout=0x3ffdaec0 <vflash_mem+1632>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/vfs/vfs.c:1619
#7  0x40180b80 in base_poll_read (t=0x3ffc21e8, timeout_ms=1000) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/tcp_transport/transport_ssl.c:176
#8  0x401fa67e in esp_transport_poll_read (t=<optimized out>, timeout_ms=1000) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/tcp_transport/transport.c:156
#9  0x40159476 in esp_mqtt_task (pv=0x3fff0de8) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/mqtt/esp-mqtt/mqtt_client.c:1819
#10 0x400901fc in vPortTaskWrapper (pxCode=0x4015857c <esp_mqtt_task>, pvParameters=0x3fff0de8) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 7 (TCB: 0x3ffb7e1c, name: 'Tmr Svc') =====================
#0  0x40090abd in prvProcessTimerOrBlockTask (xNextExpireTime=5170, xListWasEmpty=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/xtensa/include/xt_utils.h:41
#1  prvTimerTask (pvParameters=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/timers.c:685
#2  0x400901fc in vPortTaskWrapper (pxCode=0x40090a38 <prvTimerTask>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 8 (TCB: 0x3fff028c, name: 'PeriodicPowerUp') =====================
#0  vTaskDelay (xTicksToDelay=500) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
#1  0x400dc884 in WaterHeaterDevice::periodicPowerUpdate (pvParameters=<optimized out>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/matter/whDevice.cpp:890
#2  WaterHeaterDevice::periodicPowerUpdate (pvParameters=0x3ffc4d58 <WH>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/matter/whDevice.cpp:824
#3  0x400901fc in vPortTaskWrapper (pxCode=0x400dc680 <WaterHeaterDevice::periodicPowerUpdate(void*)>, pvParameters=0x3ffc4d58 <WH>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 9 (TCB: 0x3ffb5bf0, name: 'power_measure_t') =====================
#0  vTaskDelay (xTicksToDelay=100) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
#1  0x400e6e03 in power_measure_task (arg=<optimized out>) at /Users/badra/dev/photonsmart/fresh_water_heater/managed_components/espressif__power_measure/power_measure.c:84
#2  0x400901fc in vPortTaskWrapper (pxCode=0x400e6dd8 <power_measure_task>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 10 (TCB: 0x3ffc6be0, name: 'BBG_CTL') =====================
#0  vTaskDelay (xTicksToDelay=100) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:1615
#1  0x400ddf6d in HeaterControl::BangBangControlTask (pvParameters=0x3ffc50a8 <WH+848>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/logic/heater_control.cpp:117
#2  0x400901fc in vPortTaskWrapper (pxCode=0x400ddefc <HeaterControl::BangBangControlTask(void*)>, pvParameters=0x3ffc50a8 <WH+848>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 11 (TCB: 0x3ffc1e38, name: 'photon_queue_ta') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffeff10) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffefec4, pvBuffer=0x3ffb1cf0, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x40156ea9 in esp_photon_handle_work_queue () at /Users/badra/dev/photonsmart/fresh_water_heater/managed_components/photon-technologies__photon_chip_common/src/work_queue.c:71
#5  esp_photon_work_queue_task (param=0x0) at /Users/badra/dev/photonsmart/fresh_water_heater/managed_components/photon-technologies__photon_chip_common/src/work_queue.c:80
#6  0x400901fc in vPortTaskWrapper (pxCode=0x40156e5c <esp_photon_work_queue_task>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 12 (TCB: 0x3ffec0ec, name: 'CHIP') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffe8fa0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffe8f54, pvBuffer=0x3ffebfd0, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x4011684c in chip::DeviceLayer::Internal::GenericPlatformManagerImpl_FreeRTOS<chip::DeviceLayer::PlatformManagerImpl>::_RunEventLoop (this=0x3ffce0f0 <chip::DeviceLayer::PlatformManagerImpl::sInstance+8>) at ../../../../../../opt/test/connectedhomeip/config/esp32/third_party/connectedhomeip/src/include/platform/internal/GenericPlatformManagerImpl_FreeRTOS.ipp:250
#5  0x40116878 in chip::DeviceLayer::PlatformManager::RunEventLoop (this=0x3ffce0e8 <chip::DeviceLayer::PlatformManagerImpl::sInstance>) at ../../../../../../opt/test/connectedhomeip/config/esp32/third_party/connectedhomeip/src/include/platform/PlatformManager.h:409
#6  chip::DeviceLayer::Internal::GenericPlatformManagerImpl_FreeRTOS<chip::DeviceLayer::PlatformManagerImpl>::EventLoopTaskMain (arg=0x3ffce0f0 <chip::DeviceLayer::PlatformManagerImpl::sInstance+8>) at ../../../../../../opt/test/connectedhomeip/config/esp32/third_party/connectedhomeip/src/include/platform/internal/GenericPlatformManagerImpl_FreeRTOS.ipp:275
#7  0x400901fc in vPortTaskWrapper (pxCode=0x40116870 <chip::DeviceLayer::Internal::GenericPlatformManagerImpl_FreeRTOS<chip::DeviceLayer::PlatformManagerImpl>::EventLoopTaskMain(void*)>, pvParameters=0x3ffce0f0 <chip::DeviceLayer::PlatformManagerImpl::sInstance+8>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 13 (TCB: 0x3ffb7074, name: 'ipc0') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbdc98 <xKernelLock>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x400929f1 in ulTaskGenericNotifyTake (uxIndexToWait=0, xClearCountOnExit=1, xTicksToWait=4294967295) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:5768
#4  0x400819d5 in ipc_task (arg=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_system/esp_ipc.c:62
#5  0x400901fc in vPortTaskWrapper (pxCode=0x40081994 <ipc_task>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 14 (TCB: 0x3ffddf50, name: 'sys_evt') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffdcbdc) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffdcb90, pvBuffer=0x3ffdde60, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x401fda04 in esp_event_loop_run (event_loop=0x3ffbdb0c, ticks_to_run=4294967295) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_event/esp_event.c:644
#5  0x401fda1a in esp_event_loop_run_task (args=0x3ffbdb0c) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_event/esp_event.c:106
#6  0x400901fc in vPortTaskWrapper (pxCode=0x401fda10 <esp_event_loop_run_task>, pvParameters=0x3ffbdb0c) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 15 (TCB: 0x3ffb75dc, name: 'ipc1') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbdc98 <xKernelLock>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x400929f1 in ulTaskGenericNotifyTake (uxIndexToWait=0, xClearCountOnExit=1, xTicksToWait=4294967295) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:5768
#4  0x400819d5 in ipc_task (arg=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_system/esp_ipc.c:62
#5  0x400901fc in vPortTaskWrapper (pxCode=0x40081994 <ipc_task>, pvParameters=0x1) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 16 (TCB: 0x3ffb562c, name: 'HEATER') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbcd60) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffbcd14, pvBuffer=0x3ffb54d0, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x400dd629 in Photon::Object::run (args=0x3ffc4e68 <WH+272>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/Phsm.h:513
#5  0x400901fc in vPortTaskWrapper (pxCode=0x400dd5fc <Photon::Object::run(void*)>, pvParameters=0x3ffc4e68 <WH+272>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 17 (TCB: 0x3fff4abc, name: 'IN_EventReceive') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3fff3b30) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3fff3ae4, pvBuffer=0x3fff49d8, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x400dcad5 in InputWrapper::HW_IN_EventReceiverTask (pvParameters=<optimized out>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/logic/Input_wrapper.cpp:390
#5  0x400901fc in vPortTaskWrapper (pxCode=0x400dca54 <InputWrapper::HW_IN_EventReceiverTask(void*)>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 18 (TCB: 0x3ffb5790, name: 'BOOST_SMART_STA') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbceb4) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffbce68, pvBuffer=0x3ffee870, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x400dd629 in Photon::Object::run (args=0x3ffc4ee8 <WH+400>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/Phsm.h:513
#5  0x400901fc in vPortTaskWrapper (pxCode=0x400dd5fc <Photon::Object::run(void*)>, pvParameters=0x3ffc4ee8 <WH+400>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 19 (TCB: 0x3ffb45c4, name: 'RELAY') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbd2b0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffbd264, pvBuffer=0x3ffb4470, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x400dd629 in Photon::Object::run (args=0x3ffc5060 <WH+776>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/Phsm.h:513
#5  0x400901fc in vPortTaskWrapper (pxCode=0x400dd5fc <Photon::Object::run(void*)>, pvParameters=0x3ffc5060 <WH+776>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 20 (TCB: 0x3ffb7740, name: 'esp_timer') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbdc98 <xKernelLock>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x400929f1 in ulTaskGenericNotifyTake (uxIndexToWait=0, xClearCountOnExit=1, xTicksToWait=4294967295) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/tasks.c:5768
#4  0x40162530 in timer_task (arg=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/esp_timer/src/esp_timer.c:459
#5  0x400901fc in vPortTaskWrapper (pxCode=0x40162520 <timer_task>, pvParameters=0x0) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 21 (TCB: 0x3ffc6dfc, name: 'DISPLAY') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbd008) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffbcfbc, pvBuffer=0x3ffc7d00 <StateManager::DISPLAY_BUFFER+3844>, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x400dd629 in Photon::Object::run (args=0x3ffc4f60 <WH+520>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/Phsm.h:513
#5  0x400901fc in vPortTaskWrapper (pxCode=0x400dd5fc <Photon::Object::run(void*)>, pvParameters=0x3ffc4f60 <WH+520>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139

==================== THREAD 22 (TCB: 0x3ffb58f4, name: 'RESET') =====================
#0  0x4000bff0 in ?? ()
#1  0x400904cc in vPortClearInterruptMaskFromISR (prev_level=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:560
#2  vPortExitCritical (mux=0x3ffbd15c) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:514
#3  0x4008ff61 in xQueueReceive (xQueue=0x3ffbd110, pvBuffer=0x3ffed080, xTicksToWait=<optimized out>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/queue.c:1632
#4  0x400dd629 in Photon::Object::run (args=0x3ffc4f20 <WH+456>) at /Users/badra/dev/photonsmart/fresh_water_heater/main/Phsm.h:513
#5  0x400901fc in vPortTaskWrapper (pxCode=0x400dd5fc <Photon::Object::run(void*)>, pvParameters=0x3ffc4f20 <WH+456>) at /Users/badra/opt/esp/V5_5_1/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139


======================= ALL MEMORY REGIONS ========================
Name   Address   Size   Attrs
.rtc.text 0x400c0000 0x0 RW  
.rtc.dummy 0x3ff80000 0x0 RW  
.rtc.force_fast 0x3ff80000 0x0 RW  
.rtc.force_slow 0x50000ce8 0x20 RW A
.rtc_fast_reserved 0x3ff82000 0x0 RW  
.iram0.vectors 0x40080000 0x404 R XA
.iram0.text 0x40080404 0x1facb R XA
.dram0.data 0x3ffbdb60 0x6258 RW A
.dram0.data 0x3ffbdb60 0x6258 RW A
.ext_ram_noinit 0x3f800000 0x0 RW  
.ext_ram.bss 0x3f800000 0x0 RW  
.flash.appdesc 0x3f400020 0x100 R  A
.flash.rodata 0x3f400120 0x4494c RW A
.flash.text 0x400d0020 0x131649 R XA
.iram0.data 0x4009fed0 0x0 RW  
.iram0.bss 0x4009fed0 0x0 RW  
.dram0.heap_start 0x3ffdb068 0x0 RW  
.coredump.tasks.data 0x3ffe1fe8 0x154 RW 
.coredump.tasks.data 0x3ffe1d80 0x260 RW 
.coredump.tasks.data 0x3ffb7cb8 0x154 RW 
.coredump.tasks.data 0x3ffbcb60 0x1a0 RW 
.coredump.tasks.data 0x3ffb7b54 0x154 RW 
.coredump.tasks.data 0x3ffbc560 0x1a0 RW 
.coredump.tasks.data 0x3ffb355c 0x154 RW 
.coredump.tasks.data 0x3ffb3370 0x190 RW 
.coredump.tasks.data 0x3ffdf1a4 0x154 RW 
.coredump.tasks.data 0x3ffdef80 0x210 RW 
.coredump.tasks.data 0x3ffdac60 0x3b0 RW 
.coredump.tasks.data 0x3ffb7e1c 0x154 RW 
.coredump.tasks.data 0x3ffdc1d0 0x170 RW 
.coredump.tasks.data 0x3fff028c 0x154 RW 
.coredump.tasks.data 0x3fff2bd0 0x1c0 RW 
.coredump.tasks.data 0x3ffb5bf0 0x154 RW 
.coredump.tasks.data 0x3fff5c00 0x1a0 RW 
.coredump.tasks.data 0x3ffc6be0 0x154 RW 
.coredump.tasks.data 0x3ffc6a40 0x190 RW 
.coredump.tasks.data 0x3ffb1bc0 0x200 RW 
.coredump.tasks.data 0x3ffec0ec 0x154 RW 
.coredump.tasks.data 0x3ffebea0 0x240 RW 
.coredump.tasks.data 0x3ffb7074 0x154 RW 
.coredump.tasks.data 0x3ffb6ea0 0x1c0 RW 
.coredump.tasks.data 0x3ffddf50 0x154 RW 
.coredump.tasks.data 0x3ffddd20 0x220 RW 
.coredump.tasks.data 0x3ffb75dc 0x154 RW 
.coredump.tasks.data 0x3ffb7410 0x1c0 RW 
.coredump.tasks.data 0x3ffb562c 0x154 RW 
.coredump.tasks.data 0x3ffb53a0 0x1f0 RW 
.coredump.tasks.data 0x3fff4abc 0x154 RW 
.coredump.tasks.data 0x3fff4890 0x210 RW 
.coredump.tasks.data 0x3ffb5790 0x154 RW 
.coredump.tasks.data 0x3ffee740 0x1f0 RW 
.coredump.tasks.data 0x3ffb45c4 0x154 RW 
.coredump.tasks.data 0x3ffb4340 0x1f0 RW 
.coredump.tasks.data 0x3ffb7740 0x154 RW 
.coredump.tasks.data 0x3ffba540 0x1c0 RW 
.coredump.tasks.data 0x3ffc6dfc 0x154 RW 
.coredump.tasks.data 0x3ffc7bd0 0x1f0 RW 
.coredump.tasks.data 0x3ffb58f4 0x154 RW 
.coredump.tasks.data 0x3ffecf50 0x1f0 RW 

===================== ESP32 CORE DUMP END =====================
===============================================================
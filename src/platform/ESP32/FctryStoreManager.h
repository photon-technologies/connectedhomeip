/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 * @file
 *
 * @brief
 *   API function declarations for using persistent key value storage.
 */

#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include <lib/core/CHIPError.h>
#include <platform/CHIPDeviceConfig.h>

namespace chip {
namespace DeviceLayer {
namespace PersistedStorage {
class FctryStoreManager
{
public:
    /**
     * @brief
     *   Reads the value of an entry in the KVS. The value is read into the
     *   provided buffer and the number of bytes read is returned. If desired,
     *   the read can be started at an offset.
     *
     *   If the output buffer is too small for the value, Get returns
     *   CHIP_ERROR_BUFFER_TOO_SMALL with the number of bytes read returned in
     *   read_bytes_size, which should be the buffer_size.
     *
     *   The remainder of the  value can be read by calling get with an offset.
     *
     * @param[in]     key               The name of the key to get, this is a
     *                                  null-terminated string.
     * @param[in,out] buffer            A buffer to read the value into.
     * @param[in]     buffer_size       The size of the buffer in bytes.
     * @param[in]     read_bytes_size   The number of bytes which were
     *                                  copied into the buffer. Optionally can
     *                                  provide nullptr if not needed.
     * @param[in]     offset_bytes      The offset byte index to start the read.
     *
     * @return CHIP_NO_ERROR the entry was successfully read
     *         CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND the key is not
     *                                                       present in the KVS
     *         CHIP_ERROR_INTEGRITY_CHECK_FAILED found the entry, but the data
     *                                           was corrupted
     *         CHIP_ERROR_BUFFER_TOO_SMALL the buffer could not fit the entire
     *                                     value, but as many bytes as possible
     *                                     were written to it
     *         CHIP_ERROR_UNINITIALIZED the KVS is not initialized
     *         CHIP_ERROR_INVALID_ARGUMENT key is empty or too long or value is
     *                                     too large
     */
    CHIP_ERROR Get(const char * key, void * buffer, size_t buffer_size, size_t * read_bytes_size = nullptr,
                   size_t offset_bytes = 0);

    /**
     * @brief
     * This overload of Get accepts a pointer to a trivially copyable object.
     * The size of the object is inferred from the type.
     *
     * @param[in]      key     The name of the key in to get, this is a
     *                         null-terminated string.
     * @param[in,out]  value   Pointer to a trivially copyable object.
     *
     * @return CHIP_NO_ERROR the entry was successfully read
     *         CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND the key is not
     *                                                      present in the KVS
     *         CHIP_ERROR_INTEGRITY_CHECK_FAILED found the entry, but the data
     *                                           was corrupted
     *         CHIP_ERROR_BUFFER_TOO_SMALL the buffer could not fit the entire
     *                                     value, but as many bytes as possible
     *                                     were written to it
     *         CHIP_ERROR_UNINITIALIZED the KVS is not initialized
     *         CHIP_ERROR_INVALID_ARGUMENT key is empty or too long or value is
     *                                     too large
     */
    template <typename T>
    CHIP_ERROR Get(const char * key, T * value)
    {
        static_assert(std::is_trivially_copyable<T>(), "KVS values must copyable");
        static_assert(!std::is_pointer<T>(), "KVS values cannot be pointers");
        static_assert(CHAR_BIT == 8, "Current implementation assumes 8 bit.");
        return Get(key, value, sizeof(T));
    }

    /**
     * @brief
     * Adds a key-value entry to the KVS. If the key was already present, its
     * value is overwritten.
     *
     * @param[in]  key          The name of the key to update, this is a
     *                          null-terminated string.
     * @param[in]  value        Pointer to the data.
     * @param[in]  value_size   Size of the data.
     *
     * @return CHIP_NO_ERROR the entry was successfully added or updated
     *         CHIP_ERROR_INTEGRITY_CHECK_FAILED checksum validation failed after
     *                                           writing the data
     *         CHIP_ERROR_PERSISTED_STORAGE_FAILED failed to write the value.
     *         CHIP_ERROR_UNINITIALIZED the KVS is not initialized
     *         CHIP_ERROR_INVALID_ARGUMENT key is empty or too long or value is
     *                                     too large
     */
    CHIP_ERROR Put(const char * key, const void * value, size_t value_size);

    /**
     * @brief
     * This overload of Put accepts a reference to a trivially copyable object.
     * The size of the object is inferred from the type.
     *
     * @param[in]  key     The name of the key to update, this is a
     *                     null-terminated string.
     * @param[in]  value   Reference of a trivially copyable object.
     *
     * @return CHIP_NO_ERROR the entry was successfully added or updated
     *         CHIP_ERROR_INTEGRITY_CHECK_FAILED checksum validation failed after
     *                                           writing the data
     *         CHIP_ERROR_PERSISTED_STORAGE_FAILED failed to write the value.
     *         CHIP_ERROR_UNINITIALIZED the KVS is not initialized
     *         CHIP_ERROR_INVALID_ARGUMENT key is empty or too long or value is
     *                                     too large
     */
    template <typename T>
    CHIP_ERROR Put(const char * key, const T & value)
    {
        static_assert(std::is_trivially_copyable<T>(), "KVS values must copyable");
        static_assert(!std::is_pointer<T>(), "KVS values cannot be pointers");
        static_assert(CHAR_BIT == 8, "Current implementation assumes 8 bit.");
        return Put(key, &value, sizeof(T));
    }

    /**
     * @brief
     * Removes a key-value entry from the KVS.
     *
     * @param[in]      key       The name of the key to delete, this is a
     *                           null-terminated string.
     *
     * @return CHIP_NO_ERROR the entry was successfully deleted.
     *         CHIP_ERROR_PERSISTED_STORAGE_VALUE_NOT_FOUND the key is not
     *                                                      present in the KVS
     *         CHIP_ERROR_INTEGRITY_CHECK_FAILED checksum validation failed after
     *                                           erasing data
     *         CHIP_ERROR_PERSISTED_STORAGE_FAILED failed to erase the value.
     *         CHIP_ERROR_UNINITIALIZED the KVS is not initialized
     *         CHIP_ERROR_INVALID_ARGUMENT key is empty or too long
     */
    CHIP_ERROR Delete(const char * key);


protected:
    // Construction/destruction limited to subclasses.
    FctryStoreManager()  = default;
    ~FctryStoreManager() = default;

    // No copy, move or assignment.
    FctryStoreManager(const FctryStoreManager &)             = delete;
    FctryStoreManager(const FctryStoreManager &&)            = delete;
    FctryStoreManager & operator=(const FctryStoreManager &) = delete;
};


} // namespace PersistedStorage
} // namespace DeviceLayer
} // namespace chip




#ifdef FACTORY_STORE_MANAGER_IMPLEMENTATION
#include <platform/ESP32/ScopedNvsHandle.h>
#include <string.h>

#include "nvs.h"
#include "nvs_flash.h"
#include <crypto/CHIPCryptoPAL.h>
#include <lib/core/CHIPSafeCasts.h>
#include <lib/support/BytesToHex.h>
#include <lib/support/CodeUtils.h>
using namespace chip;
static const char kNamespace[] = "PHOTON";

namespace chip {
namespace DeviceLayer {
namespace PersistedStorage {
namespace {
// Implementation Note: esp-idf nvs implementation cannot handle key length > 15,
// Below implementation tries to handle that case by hashing the key
// If key length is > 15 then take the SHA1 of the key and convert the first 7.5 bytes to hex string.
// Not sure how likely we would run into a conflict as we are only using 8 bytes out of 20
//
// key returned by below function will not collide with any existing "normal" keys because those always have a "/" in
// the first few chars and the output of this code never will.
//
// Returns true if key is hashed, false otherwise.
bool HashIfLongKey(const char * key, char * keyHash)
{
    VerifyOrReturnError(strlen(key) >= NVS_KEY_NAME_MAX_SIZE, false);

    uint8_t hashBuffer[chip::Crypto::kSHA1_Hash_Length];
    VerifyOrReturnError(Crypto::Hash_SHA1(Uint8::from_const_char(key), strlen(key), hashBuffer) == CHIP_NO_ERROR, false);

    BitFlags<Encoding::HexFlags> flags(Encoding::HexFlags::kNone);
    Encoding::BytesToHex(hashBuffer, NVS_KEY_NAME_MAX_SIZE / 2, keyHash, NVS_KEY_NAME_MAX_SIZE, flags);
    keyHash[NVS_KEY_NAME_MAX_SIZE - 1] = 0;

    ChipLogDetail(DeviceLayer, "Using hash:%s for nvs key:%s", keyHash, StringOrNullMarker(key));
    return true;
}
} // namespace

CHIP_ERROR FctryStoreManager::Get(const char * key, void * value, size_t value_size, size_t * read_bytes_size,
                                          size_t offset_bytes)
{
    // value may be NULL when checking whether the key exists

    // Offset and partial reads are not supported in nvs, for now just return NOT_IMPLEMENTED. Support can be added in the
    // future if this is needed.
    VerifyOrReturnError(offset_bytes == 0, CHIP_ERROR_NOT_IMPLEMENTED);

    chip::DeviceLayer::Internal::ScopedNvsHandle handle;
    ReturnErrorOnFailure(handle.Open(kNamespace, NVS_READONLY, CHIP_DEVICE_CONFIG_CHIP_FACTORY_NAMESPACE_PARTITION));

    char keyHash[NVS_KEY_NAME_MAX_SIZE];
    VerifyOrDo(HashIfLongKey(key, keyHash) == false, key = keyHash);

    ReturnMappedErrorOnFailure(nvs_get_blob(handle, key, value, &value_size));

    if (read_bytes_size)
    {
        *read_bytes_size = value_size;
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR FctryStoreManager::Put(const char * key, const void * value, size_t value_size)
{
    VerifyOrReturnError(value, CHIP_ERROR_INVALID_ARGUMENT);

    chip::DeviceLayer::Internal::ScopedNvsHandle handle;
    ReturnErrorOnFailure(handle.Open(kNamespace, NVS_READWRITE, CHIP_DEVICE_CONFIG_CHIP_FACTORY_NAMESPACE_PARTITION));

    char keyHash[NVS_KEY_NAME_MAX_SIZE];
    VerifyOrDo(HashIfLongKey(key, keyHash) == false, key = keyHash);

    ReturnMappedErrorOnFailure(nvs_set_blob(handle, key, value, value_size));

    // Commit the value to the persistent store.
    ReturnMappedErrorOnFailure(nvs_commit(handle));

    return CHIP_NO_ERROR;
}

CHIP_ERROR FctryStoreManager::Delete(const char * key)
{
    chip::DeviceLayer::Internal::ScopedNvsHandle handle;

    ReturnErrorOnFailure(handle.Open(kNamespace, NVS_READWRITE, CHIP_DEVICE_CONFIG_CHIP_FACTORY_NAMESPACE_PARTITION));

    char keyHash[NVS_KEY_NAME_MAX_SIZE];
    VerifyOrDo(HashIfLongKey(key, keyHash) == false, key = keyHash);

    ReturnMappedErrorOnFailure(nvs_erase_key(handle, key));

    // Commit the value to the persistent store.
    ReturnMappedErrorOnFailure(nvs_commit(handle));

    return CHIP_NO_ERROR;
}

} // namespace PersistedStorage
} // namespace DeviceLayer
} // namespace chip


#endif

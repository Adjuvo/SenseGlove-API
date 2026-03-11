/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Uploads Firmware files to a Specific SGDevice.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>

#include "EFWErrorCodes.hpp"

namespace SGConnect
{
    class FirmwareUploader;
    class SGDevice;
    class Nova2BleDevice;
}// namespace SGConnect

class SGCONNECT_API SGConnect::FirmwareUploader
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    FirmwareUploader();

public:
    /**
     * The copy constructor.
     */
    FirmwareUploader(const FirmwareUploader& rhs) = delete;

    /**
     * The move constructor.
     */
    FirmwareUploader(FirmwareUploader&& rhs) noexcept;

public:
    virtual ~FirmwareUploader();

public:
    /**
     * The copy assignment operator.
     */
    FirmwareUploader& operator=(const FirmwareUploader& rhs) = delete;

    /**
     * The move assignment operator.
     */
    FirmwareUploader& operator=(FirmwareUploader&& rhs) noexcept;

public:
    int32_t UploadProgress() const;

    bool IsUploading() const;

    EFWErrorCodes GetLastResult() const;
    void SetLastResult(const EFWErrorCodes newCode);

public:
    /// <summary> Uplaod new firmware to the specified device, with additional parameters: </summary>
    /// <param name="toDevice"></param>
    /// <param name="filePath"></param>
    /// <param name="chunkSize"></param>
    /// <returns></returns>
    EFWErrorCodes UploadFirmware_BTS_to_BTS(std::shared_ptr<SGDevice> toDevice, const std::string& filePath, const int32_t chunkSize);

    EFWErrorCodes UploadFirmware_BTS_to_BLE(std::shared_ptr<SGDevice> toDevice, const std::string& filePath, const int32_t chunkSize);
    void Continue_BTS_to_BLE();

    EFWErrorCodes UploadFirmware_BLE_to_BLE(std::shared_ptr<Nova2BleDevice> toDevice, const std::string& filePath, const int32_t chunkSize);
};

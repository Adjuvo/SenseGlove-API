/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Base class for Device Models containing the minimum amount of data gathered
 * through Communications Protocol. Used for shared functionality.
 */


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    /// <summary> Base class containing the minimum amount of data for device models. </summary>
    class SGCORE_API DeviceModel;
}// namespace SGCore

/// <summary> Base class containing the minimum amount of data for device models. </summary>
class SGCORE_API SGCore::DeviceModel
{
public:
    /// <summary> Parse a 32-bit integer value into a set of booleans (010010011) that indicate which (optional)
    /// functions this device has. </summary>
    static std::vector<bool> ParseFunctions(int32_t value, int32_t size);

    /// <summary>  </summary>
    /// <param name="rawFirmware"></param>
    /// <param name="out_mainVersion"></param>
    /// <param name="out_subVersion"></param>
    static void ParseFirmware(const std::string& rawFirmware, int32_t& out_mainVersion, int32_t& out_subVersion);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    DeviceModel();// empty constructor to be used by child classes.
    DeviceModel(const std::string& id,
                const std::string& hardwareVersion, int32_t firmwareVersion, int32_t subFirmwareVersion);

    /**
     * The copy constructor.
     */
    DeviceModel(const DeviceModel& rhs);

    /**
     * The move constructor.
     */
    DeviceModel(DeviceModel&& rhs) noexcept;

    virtual ~DeviceModel();

public:
    /**
     * The copy assignment operator.
     */
    DeviceModel& operator=(const DeviceModel& rhs);

    /**
     * The move assignment operator.
     */
    DeviceModel& operator=(DeviceModel&& rhs) noexcept;

public:
    /// <summary> Retrieve the Unique identifier of this device. </summary>
    SG_NODISCARD std::string GetDeviceId() const;

protected:
    /// <summary> Unique identifier of this device. </summary>
    void SetDeviceId(const std::string& id);

public:
    /// <summary> Retrieve the Hardware (sub) version of this Sense Glove Device. </summary>
    SG_NODISCARD std::string GetHardwareVersion() const;

protected:
    /// <summary> Hardware (sub) version of this Sense Glove Device. </summary>
    void SetHardwareVersion(const std::string& version);

public:
    /// <summary> Firmware version running on the device's MicroController. (as of v4.12, this is the 4). </summary>
    SG_NODISCARD int32_t GetFirmwareVersion() const;

protected:
    /// <summary> Firmware version running on the device's MicroController. </summary>
    void SetFirmwareVersion(int32_t version);

public:
    /// <summary> Sub firmware version running on the device's microcontroller (as of v4.12, this is the 12). </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetSubFirmwareVersion() const;

protected:
    /// <summary> Sub-Firmware version running on the device's MicroController. </summary>
    void SetSubFirmwareVersion(int32_t version);

public:
    /// <summary> Returns true if this glove's firmware is newer than certain version. </summary>
    /// <param name="firmwareMain"></param>
    /// <param name="firmwareSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    SG_NODISCARD bool FirmwareNewerThan(int32_t firmwareMain, int32_t firmwareSub, bool bInclusive) const;

    /// <summary> Returns true if this glove's firmware is older than certain version. </summary>
    /// <param name="firmwareMain"></param>
    /// <param name="firmwareSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    SG_NODISCARD bool FirmwareOlderThan(int32_t firmwareMain, int32_t firmwareSub, bool bInclusive) const;
};
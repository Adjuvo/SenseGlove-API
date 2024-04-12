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
 * Represents a Sense Glove Device that has no specific class within the API.
 * Used to test different iterations of the same product before integrating it
 * into the Core API.
 * Allows access to raw sensor values and commands of such a device.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Platform.hpp"
#include "SGDevice.hpp"

namespace SGCore
{
    /// <summary> A Device that adheres to the SenseGlove communications protocol, but which has no implementation in
    /// this API. </summary>
    class SGCORE_API BetaDevice;
}// namespace SGCore

/// <summary> A Device that adheres to the SenseGlove communications protocol, but which has no implementation in this
/// API. </summary>
class SGCORE_API SGCore::BetaDevice : public SGDevice
{
public:
    /// <summary> Deserialize a beta device from its basic constants string. Returns nullptr is unsuccessful. </summary>
    static std::shared_ptr<SGDevice> Parse(const std::string& constantsString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The basic class constructor. </summary>
    BetaDevice();

    /// <summary> Creates a new instance of a Beta Device. </summary>
    BetaDevice(const std::string& constantsString, const std::string& deviceId,
               const std::string& hardwareVersion, int32_t firmwareVersion, int32_t subFirmwareVersion);

    /**
     * The copy constructor.
     */
    BetaDevice(const BetaDevice& rhs);

    /**
     * The move constructor.
     */
    BetaDevice(BetaDevice&& rhs) noexcept;

    /// <summary> The basic class destructor. </summary>
    virtual ~BetaDevice();

public:
    /**
     * The copy assignment operator.
     */
    BetaDevice& operator=(const BetaDevice& rhs);

    /**
     * The move assignment operator.
     */
    BetaDevice& operator=(BetaDevice&& rhs) noexcept;

public:
    /// <summary> Get the DeviceType enumerator of this SenseGlove, used in DeviceList enumeration. </summary>
    SG_NODISCARD virtual EDeviceType GetDeviceType() const override;

    /// <summary> Get the unique identifier of this device. </summary>
    SG_NODISCARD virtual const std::string& GetDeviceId() const override;

    /// <summary> Retrieve this device's hardware version. </summary>
    SG_NODISCARD virtual const std::string& GetHardwareVersion() const override;

    /// <summary> Retrieve this device's firmware version. </summary>
    SG_NODISCARD virtual int32_t GetFirmwareVersion() const override;

    /// <summary> Retrieve this device's sub-firmware version. </summary>
    SG_NODISCARD virtual int32_t GetSubFirmwareVersion() const override;

public:
    /// <summary> Retrieve the constants string for additional processing. </summary>
    SG_NODISCARD const std::string& GetConstantsString() const;

    /// <summary> Retrieve a raw sensor string from this Beta Device. </summary>
    SG_NODISCARD std::string GetSensorData() const;

    /// <summary> Retrieve the last command retrieved from this Beta Device. </summary>
    SG_NODISCARD const std::string& GetLastCommand() const;

public:
    /// <summary> Send a raw string command to this device. </summary>
    bool SendHaptics(const std::string& command, int32_t channel = 0) const;

public:
    /// <summary> Create a string representation of this device for reporting purposes. </summary>
    SG_NODISCARD virtual std::string ToString() const override;
};
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
 * Represents a Device built by the Sense Glove company that is compatible with
 * our Communications Protocol. All such devices derive from this abstract
 * class.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "DeviceTypes.hpp"
#include "Platform.hpp"
#include "HapticChannelInfo.hpp"

namespace SGCore
{
    /// <summary> Represents a generic SenseGlove Device, with some basic interfaces. </summary>
    class SGCORE_API SGDevice;
}// namespace SGCore

/// <summary> Represents a generic SenseGlove Device, with some basic interfaces. </summary>
class SGCORE_API SGCore::SGDevice
{
public:
    /// <summary> Connection type of this device, as detected by the SGConnect library. </summary>
    enum class EConnectionType : int8_t
    {
        /// <summary> Could not determine which connection type this SGDevice is using, most likely because it is
        /// disconnected. </summary>
        Unknown = -1,

        /// <summary> USB Serial communication. </summary>
        Serial,

        /// <summary> A bluetooth connection that creates up to two Serial Ports. </summary>
        BluetoothSerial,

        /// <summary> Bluetooth Connection Via Android/Java SDK </summary>
        BluetoothAndroid
    };

public:
    /// <summary> Parse a main and sub firmware version from its raw (v4.12) notation. </summary>
    static void ParseFirmware(const std::string& rawFirmware, int32_t& out_mainVersion, int32_t& out_subVersion);

    /// <summary> If true, my firmware is newer than the reference firmware. </summary>
    /// <param name="myFirmwareMain"></param>
    /// <param name="myFirmwareSub"></param>
    /// <param name="referenceMain"></param>
    /// <param name="referenceSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    static bool FirmwareNewerThan(int32_t myFirmwareMain, int32_t myFirmwareSub,
                                  int32_t referenceMain, int32_t referenceSub,
                                  bool bInclusive);

    /// <summary> If true, my firmware is older than the reference firmware. </summary>
    /// <param name="myFirmwareMain"></param>
    /// <param name="myFirmwareSub"></param>
    /// <param name="referenceMain"></param>
    /// <param name="referenceSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    static bool FirmwareOlderThan(int32_t myFirmwareMain, int32_t myFirmwareSub,
                                  int32_t referenceMain, int32_t referenceSub,
                                  bool bInclusive);

    static std::string ToString(EDeviceType deviceType);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The basic constructor. </summary>
    SGDevice();

    /**
     * The copy constructor.
     */
    SGDevice(const SGDevice& rhs);

    /**
     * The move constructor.
     */
    SGDevice(SGDevice&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~SGDevice();

public:
    /**
     * The copy assignment operator.
     */
    SGDevice& operator=(const SGDevice& rhs);

    /**
     * The move assignment operator.
     */
    SGDevice& operator=(SGDevice&& rhs) noexcept;

public:
    //--------------------------------------------------------------------------------------
    // Device Accessors

    /// <summary> Check which DeviceType this class belongs to. </summary>
    SG_NODISCARD virtual EDeviceType GetDeviceType() const;

    /// <summary> Retrieve this device's unique identifier. </summary>
    SG_NODISCARD virtual const std::string& GetDeviceId() const
#if ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN
        = 0
#endif  /* ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    ;

    /// <summary> Retrieve this device's hardware version. </summary>
    SG_NODISCARD virtual const std::string& GetHardwareVersion() const
#if ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN
        = 0
#endif  /* ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    ;

    /// <summary> Retrieve this device's main firmware version. v4.12 returns 4. </summary>
    SG_NODISCARD virtual int32_t GetFirmwareVersion() const
#if ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN
        = 0
#endif  /* ! SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    ;

    /// <summary> Retrieve this device's sub firmware version. v4.12 returns 12. </summary>
    SG_NODISCARD virtual int32_t GetSubFirmwareVersion() const;

    SG_NODISCARD virtual const std::string& GetFirmwareString() const;

public:

    /// <summary> Returns true if this glove's firmware is newer than certain version. </summary>
    /// <param name="firmwareMain"></param>
    /// <param name="firmwareSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    bool FirmwareNewerThan(int32_t firmwareMain, int32_t firmwareSub, bool bInclusive) const;

    /// <summary> Returns true if this glove's firmware is older than certain version. </summary>
    /// <param name="firmwareMain"></param>
    /// <param name="firmwareSub"></param>
    /// <param name="bInclusive"></param>
    /// <returns></returns>
    bool FirmwareOlderThan(int32_t firmwareMain, int32_t firmwareSub, bool bInclusive) const;

protected:
    SG_NODISCARD const std::string& GetIpcAddress() const;

public:
    //--------------------------------------------------------------------------------------
    // I/O Accessors

    /// <summary> Retrieve this Device's Serial/Bluetooth address. </summary>
    SG_NODISCARD std::string GetAddress() const;

    /// <summary> Check if this device is currently connected to the system. </summary>
    SG_NODISCARD bool IsConnected() const;

    /// <summary> Retrieve the connection type of this Sense Glove. </summary>
    SG_NODISCARD EConnectionType GetConnectionType() const;

    /// <summary> Retrieve the device's Packets per Second Variable. </summary>
    SG_NODISCARD int32_t PacketsPerSecondReceived() const;

    /// <summary> Retrieve the device's Packets per Second Variable. </summary>
    SG_NODISCARD int32_t PacketsPerSecondSent() const;

    /// <summary> Retrieve the index of this device within SenseCom. </summary>
    SG_NODISCARD int32_t GetDeviceIndex() const;

    /// <summary> Change this device's index within the SenseCom. Warning: Can cause errors. </summary>
    virtual void SetDeviceIndex(int32_t newIndex);

    /// <summary> Returns true if this device is connected over a connection other than usb cable. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool IsWireless() const;

    /// <summary> Returns true if this device operates on a battery. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool HasBattery() const;

    /// <summary> Returns true if this device is currently charging. </summary>
    /// <returns></returns>
    SG_NODISCARD virtual bool IsCharging();

    /// <summary> Returns the device's battery level, as a value between 0 (empty) and 1 (full). </summary>
    /// <param name="out_batteryLevel"></param>
    /// <returns></returns>
    virtual bool GetBatteryLevel(float& out_batteryLevel);

public:
    /// <summary> Assign this Device's Haptic Channels. Should not be done outside the API unless you know what you're
    /// doing. </summary>
    /// <param name="channels"></param>
    virtual void SetHapticChannels(const HapticChannelInfo& channels);

    /// <summary> The number of haptic channels this device can support. </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetHapticChannelCount() const;

    /// <summary> How many channels of a specific type this SGDevice possesses. </summary>
    /// <param name="channelType"></param>
    /// <returns></returns>
    SG_NODISCARD int32_t GetHapticChannelCount(EHapticChannelType channelType) const;

protected:
    /// <summary> Returns the address that corresponds to the nth channel of a specific type. It's unguarded, which
    /// means I dont check the validity of index - could result in an exception. Optimized piece of code for for loops.
    /// Used for Internals. </summary>
    void GetIpcParams_Unguarded(EHapticChannelType type, int32_t typeIndex,
                                int32_t& out_index, std::string& out_addressString) const;

public:
    /// <summary> Get a string representation of this SGDevice, used for debugging. </summary>
    SG_NODISCARD virtual std::string ToString() const;
};
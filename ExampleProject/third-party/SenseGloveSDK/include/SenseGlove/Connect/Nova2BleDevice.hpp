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
 * Implementation of a Nova 2.0 BLE Device.
 *
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    enum class SGCONNECT_API ENovaBleState : uint8_t
    {
        Unknown,

        DiscoveringPeripheral,

        EstablishConnection,

        SubscribeData,

        ExchangingData,

        Disconnected,

        RetryConnection,

        UploadingFirmware,

        //For logging purposes
        AwaitingNextDiscovery, //
        AwaitingNextConnect, //logging purpose
        AwaitSubscribe, //logging purposes
        UpdateDeviceFailed,
        DeviceInfoFailed,
        FailedSubscribe,
    };

    enum class SGCONNECT_API ENova2FWState : uint8_t
    {
        /// <summary> State has not (yet) been determined or returned a code that we did not understand. </summary>
        Unknown,

        /// <summary> Status was updated with no data (indicates a failure) </summary>
        OTAFailure,

        /// <summary> Sucessfully started an OTA update </summary>
        OTAStarted,
        /// <summary> Successfully written a packet of data </summary>
        OTAWritten,
        /// <summary> Successfully completed an OTA update </summary>
        OTACompleted,
    };

    class BleInfo;
    class Nova2BleDevice;
}

/// <summary> The processed ID Response of a Sense Glove Device, which we use to identify it. </summary>
class SGCONNECT_API SGConnect::Nova2BleDevice
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new instance of a processed IdResponse </summary>
    Nova2BleDevice(const BleInfo& bleInf, int32_t ipcId);

    /**
     * The copy constructor.
     */
    Nova2BleDevice(const Nova2BleDevice& rhs) = delete;

    /**
     * The move constructor.
     */
    Nova2BleDevice(Nova2BleDevice&& rhs) noexcept;

    virtual ~Nova2BleDevice();

public:
    /**
     * The copy assignment operator.
     */
    Nova2BleDevice& operator=(const Nova2BleDevice& rhs) = delete;

    /**
     * The move assignment operator.
     */
    Nova2BleDevice& operator=(Nova2BleDevice&& rhs) noexcept;

public:

    /// <summary> Returns this Device's ID inside the Shared Memory list. </summary>
    /// <returns></returns>
    [[nodiscard]] int32_t GetIPCId() const;

    void SetIPCId(const int32_t newID);

    /// <summary> Returns this Device's Address for sensor data etc. </summary>
    /// <returns></returns>
    [[nodiscard]] std::string GetIpcAddress() const;

    /// <summary> Returns this Device's BleInfo, telling you about its address, localName, and type. </summary>
    /// <returns></returns>
    [[nodiscard]] BleInfo GetBleInfo() const;

    /// <summary> Returns true if this Nova2BLE Device shares the same Device ID as the one contained in inf. </summary>
    /// <param name="inf"></param>
    /// <returns></returns>
    [[nodiscard]] bool SameDevice(const BleInfo& inf) const;


    [[nodiscard]] bool HandShakeComplete() const;

    /// <summary> Returns this Device's Address for sensor data etc. </summary>
    /// <returns></returns>
    [[nodiscard]] std::string GetDeviceString() const;


    void UpdatePps(double deltaTime);


public:

    [[nodiscard]] bool CommunicationsLive() const;

    /// <summary> Starts a worker thread to exchange data with a BLE Peripheral via the SGBLe library. </summary>
    void BeginCommunications();

    /// <summary> Ends the worker thread and cleans up resources. But keeps device (id) data in memory in case we need to restart it. (Unpair <> Pair) </summary>
    void EndCommunications();


    [[nodiscard]] bool IsConnected() const;

    //Firmware Upload Related

public:

    [[nodiscard]] bool SubscribeFWCharacteristics();

    [[nodiscard]] ENova2FWState GetLastFirmwareState();
    void ResetLastFirmwareState();

    /// <summary> After the Firmware upload, re-start the hand shake process...? </summary>
    void RestartConnection();

    void ReleaseIdleConnection();

public:

    static void RunUnitTests();

};

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
 * A threading resource that scans the computer for connections and Sense Gloves.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "ExitCodes.hpp"
#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp" /* Do not forward declare this, or else we'll encounter LINK2019 build error on MSVC */
#include "EFWErrorCodes.hpp"

namespace SGConnect
{
    class Connection;
    class DeviceScanner;
    class IdResponse;
}// namespace SGConnect

/// <summary> A threading resource that scans the computer for connections and Sense Gloves. </summary>
class SGCONNECT_API SGConnect::DeviceScanner// only one of these should be running at a time.
{
public:
    /// <summary> Check if the Device Scanner is still alive. </summary>
    static bool IsLive();

    /// <summary> Set the live value of the deviceScanner from an external source. </summary>
    static void SetLive(bool bLive);

    static bool AlreadyDetected(const IdResponse& Id);

    /// <summary> (Re)Connect a Device to the DeviceScanner list. </summary>
    /// <param name="deviceId"></param>
    /// <param name="constants"></param>
    /// <param name="newAddress"></param>
    /// <returns></returns>
    static bool ConnectDevice(const IdResponse& deviceId, const std::string& constants, const std::string& newAddress);

    static bool GetConnection(int32_t connectionIndex, std::shared_ptr<Connection>& out_connection);

    static void ReleaseIdle(const PortInfo& ofPort);

    static bool Send(int32_t connectionIndex, const std::string& command, bool bHapticCommand);
    static bool GetLastData(int32_t connectionIndex, std::string& out_data);
    static bool GetLastCommand(int32_t connectionIndex, std::string& out_cmd);
    static bool IsConnected(int32_t connectionIndex);
    static bool Disconnect(int32_t connectionIndex, EExitCode exitCode);
    static bool GetPortInfo(int32_t connectionIndex, PortInfo& out_portInfo);

    static void SetSerialEnabled(bool bEnabled);
    static int32_t RegisterBLEConnection(const std::string& deviceJson);
    static int32_t UnregisterBLEConnection(const std::string& deviceJson);

    static int32_t GetNearbyBLEDevices(std::string& out_nearbyDevices);

    static bool GetPreferInternalForHaptics(); 
    static void SetPreferInternalForHaptics(bool bInternalPreferred);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Creates a new instance of a DeviceScanner, which immedeately begins scanning for SG Devices.
    /// </summary>
    DeviceScanner();

public:
    /**
     * The copy constructor.
     */
    DeviceScanner(const DeviceScanner& rhs) = delete;

    /**
     * The move constructor.
     */
    DeviceScanner(DeviceScanner&& rhs) noexcept;

public:
    /// <summary> Cleans up any remaining unmanaged resources. </summary>
    virtual ~DeviceScanner();

public:
    /**
     * The copy assignment operator.
     */
    DeviceScanner& operator=(const DeviceScanner& rhs) = delete;

    /**
     * The move assignment operator.
     */
    DeviceScanner& operator=(DeviceScanner&& rhs) noexcept;

public:
    EFWErrorCodes OTAFirmwareUpload(int32_t deviceIndex, const std::string& filePath, const int32_t chunkSize);
    int32_t GetFirmwareProgress() const;
    EFWErrorCodes GetLastFirmwareResult() const;
    void SetLastFirmwareResult(const EFWErrorCodes errCode);

    EFWErrorCodes Nova2OTAFirmwareUpload_BTS_to_BLE(int32_t deviceIndex, const std::string& filePath, const int32_t chunkSize);
    void CompleteNova2Nova2OTAFirmwareUpload();
};

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
 * Class that contains data of a Sense Glove device that has been detected on
 * the system.
 * Has an interchangeable communications component, which it uses to exchange
 * data based on its transmit mode.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp" /* Do not forward declare this, or else we'll encounter LINK2019 build error on MSVC */
#include "TransmissionMode.hpp"

namespace SGConnect
{
    class Connection;
    class IdResponse;
    class SGDevice;
    class HapticResponse;
}// namespace SGConnect

class SGCONNECT_API SGConnect::SGDevice
{
public:
    /// <summary> Extract firmware main/sub versions from a constants string </summary>
    static void ExtractFirmware(const std::string& constantsString, int32_t& out_mainVersion, int32_t& out_subVersion);

    /// <summary> Determine the communications mode based on this device type and firmware version. </summary>
    static ETransmissionMode CommunicationMode(int32_t deviceType,
                                               int32_t mainFirmwareVersion, int32_t subFirmwareVersion);

    /// <summary> Convert a TransmissionMode into a string for debugging purposes. </summary>
    static std::string ToString(ETransmissionMode transmissionMode);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    SGDevice();

    /// <summary> Create a new SGDevice based on a connection and its responses. </summary>
    SGDevice(std::shared_ptr<Connection> startComm, const IdResponse& idInfo, const std::string& constantsResponse,
             std::string& hapticsResponse, int32_t deviceIndex);

protected:
    SGDevice(const IdResponse& idInfo, const std::string& constantsResponse,
             std::string& hapticsResponse, int32_t deviceIndex);

public:
    /**
     * The copy constructor.
     */
    SGDevice(const SGDevice& rhs) = delete;

    /**
     * The move constructor.
     */
    SGDevice(SGDevice&& rhs) noexcept;

public:
    /// <summary> Destructor cleans up any remaining resources. </summary>
    virtual ~SGDevice();

public:
    /**
     * The copy assignment operator.
     */
    SGDevice& operator=(const SGDevice& rhs) = delete;

    /**
     * The move assignment operator.
     */
    SGDevice& operator=(SGDevice&& rhs) noexcept;

public:
    [[nodiscard]] virtual const IdResponse& GetDeviceInfo() const;

    /// <summary> Update this device's index in the DeviceScanner list, and generate a new IpcAddress. </summary>
    virtual void SetDeviceIndex(int32_t deviceIndex);

    [[nodiscard]] virtual int32_t GetDeviceIndex() const;

protected:
    void SetHapticResponse(const HapticResponse& response);
    [[nodiscard]] const HapticResponse& GetHapticResponse() const;

    virtual void RegenerateAddresses(int32_t deviceIndex);

    [[nodiscard]] const std::string& GetConstantsString() const;
    void SetConstantsString(const std::string& constants) const;

    [[nodiscard]] const IdResponse& GetIDResponse() const;
    void SetIDResponse(const IdResponse& idResponse) const;

public:
    /// <summary> Check if this device's connection has the same address a port on the system. </summary>
    [[nodiscard]] virtual bool SameAddress(const PortInfo& port) const;

    /// <summary> Check if this device's connection is still active. </summary>
    [[nodiscard]] virtual bool IsConnected() const;

    /// <summary> End any existing connection and link this device to a new connection. </summary>
    virtual void ReConnect(std::shared_ptr<Connection> newComm);

    /// <summary> Update the Packets/Per/Second of this SGDevice. </summary>
    virtual void UpdatePps(double deltaTime);

    /// <summary> Retrieve the IPC Address of this SG Device </summary>
    [[nodiscard]] virtual const std::string& GetIpcAddress() const;

    /// <summary> Retrieve the IPC string for deviceInfo. </summary>
    [[nodiscard]] virtual std::string GetDeviceString() const;

    virtual void StopUpdating();

    virtual std::shared_ptr<Connection> GetConnection() const;

    virtual void SetDeviceDataUpdates(bool bEnabled);

    virtual void UpdateConstants(const std::string& newConstants);

    virtual int32_t GetPacketsPerSecondReceived() const;
};

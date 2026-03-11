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
#include "PortInfo.hpp"
#include "TransmissionMode.hpp"

namespace SGConnect
{
    class IdResponse;

    class NewSGDevice;
}// namespace SGConnect

class SGCONNECT_API SGConnect::NewSGDevice
{
public:
    static std::string ToString(ETransmissionMode transmissionMode);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    NewSGDevice(const IdResponse& id, const std::string& constants, int32_t deviceIndex,
                ETransmissionMode transmissionMode = ETransmissionMode::Async);

public:
    /**
     * The copy constructor.
     */
    NewSGDevice(const NewSGDevice& rhs) = delete;

    /**
     * The move constructor.
     */
    NewSGDevice(NewSGDevice&& rhs) noexcept;

public:
    virtual ~NewSGDevice();

public:
    /**
     * The copy assignment operator.
     */
    NewSGDevice& operator=(const NewSGDevice& rhs) = delete;

    /**
     * The move assignment operator.
     */
    NewSGDevice& operator=(NewSGDevice&& rhs) noexcept;

public:
    [[nodiscard]] bool CanUpdate() const;

    /// <summary> Stops this SG Device's data thread </summary>
    void StopUpdating();

    /// <summary> Update this device's index in the DeviceScanner list, and generate a new IpcAddress. </summary>
    void SetDeviceIndex(int32_t deviceIndex);

    /// <summary> Retrieve the IPC Address of this SG Device </summary>
    [[nodiscard]] const std::string& GetIpcAddress() const;

    /// <summary> Retrieve the IPC string for deviceInfo. </summary>
    [[nodiscard]] std::string GetDeviceString() const;

    [[nodiscard]] const IdResponse& GetDeviceInfo() const;

    void Reconnect(int32_t newConnectionIndex);

    [[nodiscard]] bool SameAddress(const PortInfo& portInfo) const;

    [[nodiscard]] bool IsConnected() const;
};

/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * Callback implementation taken from Klemen Peganc version of SenseComm.
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Serial Communication interface. Based on a 'SGCONNECT_SERIAL_MODE' variable
 * defined in the CMakeLists.txt file, a different method of interfacing is
 * used.
 */


#pragma once

#include <exception>
#include <iostream>
#include <memory> /* if a read-thread is desired. */
#include <thread> /* if a read-thread is desired. */
#include <vector>

#include "Connection.hpp"
#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp" /* Do not forward declare this, or else we'll encounter LINK2019 build error on MSVC */

namespace SGConnect
{
    class SerialConnection;
}// namespace SGConnect

class SGCONNECT_API SGConnect::SerialConnection : public SGConnect::Connection
{
public:
    /// <summary> Default BAUD rate to communicate with Sense Glove Devices. </summary>
    static int32_t GetBaudRate();

    /// <summary> Default data bit rate to communicate with Sense Glove Devices. </summary>
    static int32_t GetDataBitRate();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    explicit SerialConnection(const PortInfo& intendedPort);

public:
    /**
     * The copy constructor.
     */
    SerialConnection(const SerialConnection& rhs) = delete;

    /**
     * The move constructor.
     */
    SerialConnection(SerialConnection&& rhs) noexcept;

public:
    virtual ~SerialConnection();

public:
    /**
     * The copy assignment operator.
     */
    SerialConnection& operator=(const SerialConnection& rhs) = delete;

    /**
     * The move assignment operator.
     */
    SerialConnection& operator=(SerialConnection&& rhs) noexcept;

public:
    virtual bool IsConnected() const override;

    virtual int32_t Connect(bool bWithReadThread) override;

    virtual int32_t Disconnect(EExitCode exitCode) override;

    /// <summary> Send a command string through this connection to the Device. </summary>
    virtual int32_t SendToDevice(const std::string& command, bool bHapticCommand) override;

    /// <summary> Access the last received sensor data packet from this device. </summary>
    [[nodiscard]] virtual const std::string& GetLastData() const override;

    /// <summary> Access the last received command from this device. </summary>
    [[nodiscard]] virtual const std::string& GetLastCommand() const override;

    /// <summary> Reset the last received Sensor Data </summary>
    virtual void ResetData() override;

    /// <summary> Reset the last received command. </summary>
    virtual void ResetComamnd() override;
};

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
 * An abstract parent class for communication lines with Sense Glove Devices.
 * We use this to allow us to add more forms of communication to the
 * Sense Glove later on.
 */


#pragma once

#include <memory>
#include <string>

#include "ExitCodes.hpp"
#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp" /* Do not forward declare this, or else we'll encounter LINK2019 build error on MSVC */

namespace SGConnect
{
    /// <summary> Testing State of connection </summary>
    enum class SGCONNECT_API EConnectionTestingState : uint8_t
    {
        /* Connection needs testing. */
        NeedsTesting = 0,

        /* Connection is testing. */
        Testing,

        /* The connection test is completed. */
        TestingCompleted,
    };

    class Connection;
}// namespace SGConnect

/// <summary> Parent class for any connection with which our Sense Glove can exchange data. </summary>
class SGCONNECT_API SGConnect::Connection
{
public:
    /* Communication Constants */

    /// <summary> Indicates a new command </summary>
    static char GetCommandOpen();

    /// <summary> Indicates the end of a command summary>
    static char GetCommandClose();

    /// <summary> Indicates a new sensor data packet </summary>
    static char GetSDataOpen();

    /// <summary> Indicates the end of a sensor data packet </summary>
    static char GetSDataClose();

    /// <summary>  </summary>
    static char GetResetByte();

    /// <summary>  / </summary>
    static char GetIdleByte();

    /// <summary> Command to request ID from a device </summary>
    static const std::string& GetIdRequest();

    /// <summary> Command to request device-specific constants </summary>
    static const std::string& GetConstRequest();

    /// <summary> Command to start sensor steaming (Legacy Mode) </summary>
    static const std::string& GetStartSensors();

    /// <summary> Command to end sensor steaming (Legacy Mode) </summary>
    static const std::string& GetEndSensors();

    /// <summary> Default command to request sensor data (Ping-Pong mode) </summary>
    static const std::string& GetPingCommand();

    /// <summary> Haptic Channel Request. Sent after {I}{C} but does not need to be responded to... </summary>
    static const std::string GetHapticChannelRequest();
    /// <summary>  Haptic Bytes response </summary>
    static const char GetHapticByte();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

protected:
    explicit Connection(const PortInfo& intendedPort);

public:
    /**
     * The copy constructor.
     */
    Connection(const Connection& rhs) = delete;

    /**
     * The move constructor.
     */
    Connection(Connection&& rhs) noexcept;

public:
    virtual ~Connection();

public:
    /**
     * The copy assignment operator.
     */
    Connection& operator=(const Connection& rhs) = delete;

    /**
     * The move assignment operator.
     */
    Connection& operator=(Connection&& rhs) noexcept;

public:
    /* Uitlity functions */

    virtual void LinkToDevice(int32_t deviceIndex);
    [[nodiscard]] virtual int32_t GetLinkedIndex() const;
    [[nodiscard]] virtual const std::string& GetDeviceAddress() const;

    /* Connections / Disconnections */

    /// <summary> Returns true if this connection is active and can send/receive data. </summary>
    virtual bool IsConnected() const = 0;

    /// <summary> Connect this instance to a specific port. </summary>
    virtual int32_t Connect(bool bWithReadThread) = 0;

    /// <summary> Disconnect this port from its connection and unmanaged resources. </summary>
    virtual int32_t Disconnect(EExitCode exitCode) = 0;

    /// <summary>  </summary>
    /// <returns></returns>
    [[nodiscard]] virtual const PortInfo& GetPortInfo() const;

    /// <summary> Return communications address </summary>
    /// <returns></returns>
    [[nodiscard]] virtual const std::string& GetAddress() const;

    /* I/O */

    /// <summary> Send a command string through this connection to the Device. </summary>
    virtual int32_t SendToDevice(const std::string& command, bool hapticCommand) = 0;

    /// <summary> Access the last received sensor data packet from this device. </summary>
    [[nodiscard]] virtual const std::string& GetLastData() const;

    /// <summary> Access the last received command from this device. </summary>
    [[nodiscard]] virtual const std::string& GetLastCommand() const;

    /// <summary> Access the last received sensor data packet from this device. </summary>
    virtual void ResetComamnd();

    /// <summary> Access the last received command from this device. </summary>
    virtual void ResetData();

    [[nodiscard]] virtual int32_t GetPacketId() const;

    /* Packets Per Second */

    [[nodiscard]] int32_t GetPacketsReceived() const;
    void ResetPacketsReceived();

    [[nodiscard]] int32_t GetPacketsSent() const;
    void ResetPacketsSent();

    void ResetPackets();

    [[nodiscard]] bool IsLinked() const;
    void SetLinked(bool bLinked);

    [[nodiscard]] EConnectionTestingState GetTestingState() const;
    void SetTestingState(EConnectionTestingState testingState);

protected:
    void IncrementPacketsReceived();
    void IncrementPacketsSent();
    void IncrementSDataPacket();
    void ResetSDataPacket();

    const PortInfo& GetIntendedPort() const;
};

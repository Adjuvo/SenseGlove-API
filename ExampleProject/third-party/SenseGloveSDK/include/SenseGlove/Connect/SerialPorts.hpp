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
 * Used to retrieve serial port information on this PC, before actually
 * connecting.
 * Placed in a separate class because so that this is the only one accessing
 * the Serial library.
 */


#pragma once

#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGSerial
{
    struct SGSerialPortInfo;
}// namespace SGSerial

namespace SGConnect
{
    struct PortInfo;
    class SerialPorts;
}// namespace SGConnect

/// <summary> Utility Class to retrieve serial ports and their relevant information. </summary>
class SGCONNECT_API SGConnect::SerialPorts
{
private:
    struct Impl;

private:
    SerialPorts() = delete;
    virtual ~SerialPorts() = delete;

public:
    /// <summary> Retrieve detailed port into of everything connected to this system </summary>
    [[nodiscard]] static std::vector<std::string> GetPorts();

    /// <summary> Get ports that represent Sense Glove connections, Optional Bluetooth filter </summary>
    [[nodiscard]] static std::vector<PortInfo> GetSGPorts(bool bWithBluetooth);

    /// <summary> Get all bluetooth ports that represent Sense Glove connections, Optional Bluetooth filter </summary>
    [[nodiscard]] static std::vector<PortInfo> GetBluetoothPorts(bool bWithWired);

    /// <summary> Returns true if a hardware_id indicated that is a Bluetooth connection </summary>
    [[nodiscard]] static bool IsBluetoothPort(const SGSerial::SGSerialPortInfo& portInfo);

    /// <summary> Returns true if this Bluetooth port can be opened without locking the application. </summary>
    [[nodiscard]] static bool IsValidBluetoothPort(const SGSerial::SGSerialPortInfo& portInfo);

    /// <summary> Returns true if this hardware id belongs to a Sense Glove Device. </summary>
    [[nodiscard]] static bool IsSenseGlovePort(const SGSerial::SGSerialPortInfo& portInfo);

    /// <summary> Returns true if this hardware id belongs to a Sense Glove Device. </summary>
    [[nodiscard]] static bool AddToWhiteList(const std::string& pidVidContains);

    /// <summary> Returns true if this hardware id belongs to a Sense Glove Device. </summary>
    [[nodiscard]] static bool RemoveFromWhiteList(const std::string& pidVidContains);
};

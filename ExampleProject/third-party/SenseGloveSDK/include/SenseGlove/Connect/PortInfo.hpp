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
 * Data class to pass around, contains connection info.
 * Placed in a separate class because we do not want to pass around structs from
 * the serial library.
 * (otherwise projects using SGConnect will need to link serial as well).
 */


#pragma once

#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    /// <summary> Connection Type that helps us identify which connection to build, and if this connection is wireless.
    /// </summary>
    enum class SGCONNECT_API EConnectionType : int8_t
    {
        /// <summary> No data available, most likely because it is an invalid connection. </summary>
        Unknown = -1,
        /// <summary> A normal hardware serial port. </summary>
        Serial = 0,
        /// <summary> A serial port created by a bluetooth connection. </summary>
        BluetoothSerial,
        /// <summary> Indicator reserved for Android-Bluetooth connection </summary>
        BluetoothAndroid,
        /// <summary> MVP BLE Implementation </summary>
        BLE,
    };

    struct PortInfo;
}// namespace SGConnect

/// <summary> Data class containing connection info. </summary>
struct SGCONNECT_API SGConnect::PortInfo {
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    PortInfo();

    /// <summary> Create a new instance of the PortInfo. </summary>
    PortInfo(const std::string& address, const std::string& pidVid, EConnectionType connectionType);

    /**
     * The copy constructor.
     */
    PortInfo(const PortInfo& rhs);

    /**
     * The move constructor.
     */
    PortInfo(PortInfo&& rhs) noexcept;

    /// <summary> Default Destructor </summary>
    virtual ~PortInfo();

public:
    /**
     * The copy assignment operator.
     */
    PortInfo& operator=(const PortInfo& rhs);

    /**
     * The move assignment operator.
     */
    PortInfo& operator=(PortInfo&& rhs) noexcept;

public:
    /// <summary> The Mac/Serial address of the connected device. </summary>
    [[nodiscard]] const std::string& GetAddress() const;

    /// <summary> The PID/VID of the connected device. </summary>
    [[nodiscard]] const std::string& GetPidVid() const;

    /// <summary> The type of connection of this port. </summary>
    [[nodiscard]] EConnectionType GetConnectionType() const;

public:
    /// <summary> Returns true is this port has the same address as another. </summary>
    [[nodiscard]] bool SameAddress(const PortInfo& other) const;

public:
    [[nodiscard]] bool Equals(const PortInfo& portInfo) const;

public:
    // Optional: public static ToConnection(), which converts this port back into a connection based on its
    // ConnectionType?
    [[nodiscard]] std::string ToString() const;
};

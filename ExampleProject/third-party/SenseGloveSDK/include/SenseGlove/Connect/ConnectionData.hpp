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
 * A single piece of connection data with helper functions.
 */


#pragma once

#include <memory>
#include <string>

#include "Connection.hpp"
#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp"

namespace SGConnect
{
    class ConnectionData;
}

class SGCONNECT_API SGConnect::ConnectionData
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

private:
    ConnectionData();

public:
    ConnectionData(const std::string& address, EConnectionType connectionType, bool bConnected);

    /**
     * The copy constructor.
     */
    ConnectionData(const ConnectionData& rhs) = delete;

    /**
     * The move constructor.
     */
    ConnectionData(ConnectionData&& rhs) noexcept;

    virtual ~ConnectionData();

public:
    /**
     * The copy assignment operator.
     */
    ConnectionData& operator=(const ConnectionData& rhs) = delete;

    /**
     * The move assignment operator.
     */
    ConnectionData& operator=(ConnectionData&& rhs) noexcept;

public:
    [[nodiscard]] const std::string& GetAddress() const;
    void SetAddress(const std::string& address);

    [[nodiscard]] EConnectionType GetConnectionType() const;
    void SetConnectionType(EConnectionType connectionType);

    [[nodiscard]] bool IsConnected() const;
    void SetConnected(bool bConnected);

    [[nodiscard]] int32_t GetLastConnectCode() const;
    void SetLastConnectCode(int32_t connectCode);

    [[nodiscard]] int32_t GetLastExitCode() const;
    void SetLastExitCode(int32_t exitCode);

    [[nodiscard]] int32_t GetLastTestState() const;
    void SetLastTestState(int32_t testState);

    [[nodiscard]] int32_t GetDeviceType() const;
    void SetDeviceType(int32_t deviceType);

public:
    [[nodiscard]] bool Matches(const std::string& address, EConnectionType connectionType) const;

    [[nodiscard]] std::string Report() const;
};

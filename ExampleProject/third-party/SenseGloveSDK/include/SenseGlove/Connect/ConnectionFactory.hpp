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
 * Creates new connections based on PortInfo info.
 */


#pragma once

#include <memory>

#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp" /* Do not forward declare this, or else we'll encounter LINK2019 build error on MSVC. */

namespace SGConnect
{
    class Connection;

    class ConnectionFactory;
}// namespace SGConnect

class SGCONNECT_API SGConnect::ConnectionFactory
{
public:
    static bool CreateConnection(const PortInfo& portInfo, std::shared_ptr<Connection>& out_connection);

public:
    ConnectionFactory() = delete;
    virtual ~ConnectionFactory() = delete;
};

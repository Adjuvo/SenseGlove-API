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
 * A way for me to (safely) report on different connection states from several threads.
 */


#pragma once

#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>
#include "PortInfo.hpp" /* Do not forward declare this, or else we'll encounter LINK2019 build error on MSVC. */

namespace SGConnect
{
    enum class SGCONNECT_API EReportSource : uint8_t
    {
        Connection,
        Tester,
        Nova2BleDevice
    };

    class ConnectionData;
    class ConnectionsTracker;
}// namespace SGConnect

/// <summary> Tracks connection states on this machine specifically. </summary>
class SGCONNECT_API SGConnect::ConnectionsTracker
{
public:
    /// <summary> Clears the list of any data. </summary>
    static void ClearList();

    /// <summary> Report the connections in a string </summary>
    static void ListConnections(std::string& out_list);

    /// <summary> Fired from a Connection whenever it connects </summary>
    /// <param name="connected"></param>
    /// <param name="connectionCode"></param>
    static void ReportConnection(EReportSource source, const PortInfo& portInfo, bool bConnected,
                                 int32_t connectionCode);

    /// <summary> Fired from a Connection whenever it disconnects. Does not actually remove the entry(!) </summary>
    static void ReportDisconnected(EReportSource source, const PortInfo& portInfo, int32_t exitCode);

    /// <summary> Report an updated testing stage of a connection  </summary>
    /// <param name="source"></param>
    /// <param name="portInfo"></param>
    /// <param name="testState"></param>
    static void ReportTestStage(EReportSource source, const PortInfo& portInfo, bool bConnected, int32_t testState);

    /// <summary> Report the discovery of a SGDevice. </summary>
    /// <param name="source"></param>
    /// <param name="portInfo"></param>
    /// <param name="sgDeviceType"></param>
    static void ReportSGDevice(EReportSource source, const PortInfo& portInfo, int32_t sgDeviceType);

    static void RemoveFromList(const PortInfo& portInfo);

private:
    struct Impl;

public:
    ConnectionsTracker() = delete;
    virtual ~ConnectionsTracker() = delete;
};
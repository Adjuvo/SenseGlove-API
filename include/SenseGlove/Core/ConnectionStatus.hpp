/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Parsed Data from SGConnect Back-End to display internal connection status.
 * Used for debugging connections from, SGCore.
 */


#pragma once

#include <memory>

#include "Platform.hpp"
#include "SGDevice.hpp" //EConnectionType
#include "DeviceTypes.hpp" // EDeviceType

namespace SGCore
{
    namespace Util
    {
        /// <summary> Data from SGConnect Back-End to display internal connection status. </summary>
        class SGCORE_API ConnectionStatus;
    }// namespace Util
}// namespace SGCore

/// <summary> Data from SGConnect Back-End to display internal connection status. </summary>
class SGCORE_API SGCore::Util::ConnectionStatus
{

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:

    /**
     * The copy constructor.
     */
    ConnectionStatus(const ConnectionStatus& rhs);

    /**
     * The move constructor.
     */
    ConnectionStatus(ConnectionStatus&& rhs) noexcept;

    virtual ~ConnectionStatus();


    /**
     * The copy assignment operator.
     */
    ConnectionStatus& operator=(const ConnectionStatus& rhs);

    /**
     * The move assignment operator.
     */
    ConnectionStatus& operator=(ConnectionStatus&& rhs) noexcept;

public:

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    ConnectionStatus();
#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */


    ConnectionStatus(std::string& address, int32_t connType, bool connected, int32_t connCode, int32_t exitCode, int32_t testStage, int32_t devType);

public:

    /// <summary> Get the Connection's COM or MAC address </summary>
    /// <returns></returns>
    SG_NODISCARD std::string GetAddress() const;


     /// <summary> The type of connection this address is using </summary>
    /// <returns></returns>
    SG_NODISCARD SGDevice::EConnectionType GetConnectionType() const;

    /// <summary> Returns true if this Connection is live. </summary>
    /// <returns></returns>
    SG_NODISCARD bool GetIsConnected() const;

    /// <summary> Get the last connection code </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetLastConnectionCode() const;

    /// <summary> Get the last exit code </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetLastExitCode() const;

    /// <summary> Ge the latest testing stage, in case this isn't a SenseGlove Device or to see if we're still connecting </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetLastTestState() const;

     /// <summary> Get the DeviceType connected to this address </summary>
    /// <returns></returns>
    SG_NODISCARD EDeviceType GetDeviceType() const;


public:

    /// <returns> A reportable string </returns>
    SG_NODISCARD std::string ToString() const;

public:

    /// <summary> Parse a ConnectionStatus into a proper data class. </summary>
    /// <param name="single"></param>
    /// <returns></returns>
    static ConnectionStatus Parse(const std::string& single);
};
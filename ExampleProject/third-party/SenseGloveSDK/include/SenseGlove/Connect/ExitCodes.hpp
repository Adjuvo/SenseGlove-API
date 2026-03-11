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
 */


#pragma once

#include <cstdint>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    /// <summary> Exit Codes for the Disconnect function, which tells us why it has been disconnected. </summary>
    enum class SGCONNECT_API EExitCode : int8_t
    {
        /// <summary> Unknown Exit Code  </summary>
        Unknown = -1,

        /// <summary> Exited because the Connection was destructed. </summary>
        ConnectionDestructed,
        /// <summary> Exited because there was an error while opening. </summary>
        ConnectionOpenError,
        /// <summary> Exited because there was an error while sending. </summary>
        ConnectionSendError,
        /// <summary> Exited because the unmanaged thread of this connection has ended. </summary>
        ConnectionThreadEnded,

        /// <summary> Exited because the DeviceScanner does not think this is a Sense Glove Device </summary>
        DeviceScannerNotSenseGloveDevice,
        /// <summary> Exited because there was an error in opening the port. </summary>
        DeviceScannerNotOpened,
        /// <summary> Exited because this port is no longer connected to the system. </summary>
        DeviceScannerPortGone,
        /// <summary> Exited because the DeviceScanner is cleaning up </summary>
        DeviceScannerEndConnection,
        /// <summary> Exited because this SenseGlove device is not yet ready. Trying again later. </summary>
        DeviceScannerIdleDevice,
        /// <summary> Exited because this SenseGlove device is not yet ready. Trying again later. </summary>
        DeviceScannerNoConstants,

        /// <summary> Exited because the SGDevice is being reconnected with another connection. </summary>
        DeviceReconnect,
        /// <summary> Exited because the parent SGDevice is being cleaned up. </summary>
        DeviceDestructor,
        /// <summary> The device has requested a reset. </summary>
        DeviceResetRequest,
        /// <summary> No packets have been received for the longest time. </summary>
        DeviceNoPackets,

        /// <summary> Connection Test Destructor </summary>
        ConnectionTestDestructor,
        /// <summary> Connection Test Thread Exit </summary>
        ConnectionTestExitCheck,
    };
}// namespace SGConnect
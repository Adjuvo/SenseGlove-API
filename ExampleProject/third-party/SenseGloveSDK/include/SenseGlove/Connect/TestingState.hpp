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
    enum class SGCONNECT_API ETestingState : int8_t
    {
        /// <summary> Undefined Testing State </summary>
        Unknown = -1,

        /// <summary> We've created a testing state </summary>
        CreatedNotStarted,

        /// <summary> We've entered the the testing thread </summary>
        EnteredThread,

        /// <summary> I'm Attempting a connection </summary>
        AttemptingConnection,

        /// <summary> Succesfully connected </summary>
        Connected,

        /// <summary> Awaiting the next connection attempt. </summary>
        AwaitingNextAttempt,

        /// <summary> Constants Error. Need to try again. </summary>
        ConstantsError,

        //----------------------------
        // Exit Codes?

        /// <summary> YAY </summary>
        NewSenseGloveDevice,

        /// <summary> Yay 2 </summary>
        ExistingSenseGloveDevice,

        /// <summary> We have reached the limit of the amount of times we can connect to this device, and have stopped.
        /// </summary>
        ReachedAttemptLimit,

        /// <summary> Critical Error, we must stop. </summary>
        ThreadError,

        /// <summary> This was not a SenseGlove Device, so we have stopped the tester. </summary>
        NotSenseGloveDevice,

        //----------------------------
        // Special

        /// <summary> If we've failed to connect to a BTSerial too many times, we enter an idling state. Checks the
        /// release variable every X ms to see if we're allowed to try again...  </summary>
        Idling,
    };
}
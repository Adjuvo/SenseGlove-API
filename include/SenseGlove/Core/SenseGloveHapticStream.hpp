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
 * A buffer to queue and flush SenseGlove DK1 commands specifically. Not guarateed to work with other devices.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"
#include "SenseGloveThumperCommand.hpp"

namespace SGCore
{
    namespace SG
    {
        /// <summary> A buffer to queue and flush SenseGlove DK1 commands specifically. Not guarateed to work with other devices. </summary>
        class SGCORE_API SenseGloveHapticStream;
    }// namespace SG
}// namespace SGCore

/// <summary> A buffer to queue and flush SenseGlove DK1 commands specifically. Not guarateed to work with other devices. </summary>
class SGCORE_API SGCore::SG::SenseGloveHapticStream
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /**
     * The copy constructor.
     */
    SenseGloveHapticStream(const SenseGloveHapticStream& rhs);

    /**
     * The move constructor.
     */
    SenseGloveHapticStream(SenseGloveHapticStream&& rhs)
    noexcept;

    virtual ~SenseGloveHapticStream();


    /**
     * The copy assignment operator.
     */
    SenseGloveHapticStream& operator=(const SenseGloveHapticStream& rhs);

    /**
     * The move assignment operator.
     */
    SenseGloveHapticStream& operator=(SenseGloveHapticStream&& rhs) noexcept;

public:

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    SenseGloveHapticStream();

    
    //---------------------------------------------------------------------------------------------------
    // "Set Force-Feedback Level" commands

    /// <summary> Sets the force level for a specific finger in the buffer. </summary>
    /// <param name="level01"></param>
    /// <param name="finger"></param>
    void AddForceLevel(int32_t finger, float level01);

    /// <summary> Copy a set of FFB levels into the 'previous command', which will be used as a fallback value in case no change is made to a specific finger. </summary>
    /// <param name="levels"></param>
    void StoreLastFFB(const std::vector<float>& levels);


    //---------------------------------------------------------------------------------------------------
    // "Set Vibration Level" commands

    /// <summary> Sets the amplitude for a specific finger in the buffer. </summary>
    /// <param name="amplitude"></param>
    /// <param name="finger"></param>
    void AddVibrationLevel(int32_t finger, float amplitude);

    /// <summary> Copy a set of amplitiudes into the 'previous command', which will be used as a fallback value in case no change is made to a specific finger. </summary>
    /// <param name="levels"></param>
    void StoreLastVibro(const std::vector<float>& levels);


    //---------------------------------------------------------------------------------------------------
    // DK1 Thumper Commands

    /// <summary> Set the next SenseGlove Thumper Command for this queue. Default = none </summary>
    /// <param name="nextCmd"></param>
    void SetNextThumperCommand(Haptics::ESenseGloveThumperCommand nextCmd);

    /// <summary> Get the next Thumper Command that is to be sent to the Glove. Default = None </summary>
    /// <returns></returns>
    Haptics::ESenseGloveThumperCommand GetNextThumperCommand();


public:

    //---------------------------------------------------------------------------------------------------
    // Command Compilation

    /// <summary> Compile the commands into a set of traditional Nova Commands. </summary>
    /// <returns></returns>
    void CompileTraditionalCommands(std::vector<float>& out_ffbLevels, std::vector<float>& out_buzzLevels, Haptics::ESenseGloveThumperCommand& out_thumper);

    /// <summary> Clears any active command(s) on the Nova Glove, completely resetting the stream. </summary>
    void ClearAllCommands();

    /// <summary> Removes all non-active or elapsed Nova effects from the stream, ready for the next frame. </summary>
    void ResetBuffer();

};

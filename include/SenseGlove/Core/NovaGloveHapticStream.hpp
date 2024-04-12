/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Internal class to help a Nova Glove keep track of active effects.
 * Since the Nova's Haptics are significantly different from a SenseGlove DK1, they get their own stream.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Nova
    {
        /// <summary> Internal class to help a Nova Glove keep track of active effects. </summary>
        class SGCORE_API NovaGloveHapticStream;
    } // namespace Nova

    namespace Haptics
    {
        /// <summary> Internal class to help a Nova Glove keep track of active effects. </summary>
        class SGCORE_API ThresholdCommand;
    }// namespace Haptics

}// namespace SGCore

/// <summary> Internal class to help a Nova Glove keep track of active effects. </summary>
class SGCORE_API SGCore::Nova::NovaGloveHapticStream
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    //---------------------------------------------------------------------------------
    // Actual C++ Constructors
    /**
     * The default constructor.
     */
    NovaGloveHapticStream();

    /**
     * The copy constructor.
     */
    NovaGloveHapticStream(const NovaGloveHapticStream& rhs);

    /**
     * The move constructor.
     */
    NovaGloveHapticStream(NovaGloveHapticStream&& rhs)
    noexcept;

    virtual ~NovaGloveHapticStream();

public:
    /**
     * The copy assignment operator.
     */
    NovaGloveHapticStream& operator=(const NovaGloveHapticStream& rhs);

    /**
     * The move assignment operator.
     */
    NovaGloveHapticStream& operator=(NovaGloveHapticStream&& rhs) noexcept;

public:
    //---------------------------------------------------------------------------------------------------
    // "Set Force-Feedback Level" commands

    /// <summary> Sets the force level for a specific finger in the buffer. </summary>
    /// <param name="level01"></param>
    /// <param name="finger"></param>
    void AddForceLevel(int32_t finger, float level01);

    /// <summary> Copy a set of FFB levels into the 'previous command', which will be used as a fallback value in case
    /// no change is made to a specific finger. </summary>
    /// <param name="levels"></param>
    void StoreLastForceFeedback(const std::vector<float>& levels);

    //---------------------------------------------------------------------------------------------------
    // "Set FFB Threshold" Command

    /// <summary> Queue a finger's threshold </summary>
    /// <param name="finger"></param>
    /// <param name="value"></param>
    void QueueThreshold(int32_t finger, float value);

    /// <summary> Queue thresholds for all fingers </summary>
    /// <param name="affectedFingers"></param>
    /// <param name="values"></param>
    void QueueThresholds(const std::vector<bool>& affectedFingers, const std::vector<float>& values);

    /// <summary> Clear a Threshold on a specifc finger </summary>
    /// <param name="finger"></param>
    void ClearThreshold(int32_t finger);

    /// <summary> Clears thresholds on all fingers. </summary>
    void ClearThresholds();

    /// <summary> Returns true if there have been updates to the Thresholds. </summary>
    /// <returns></returns>
    bool ThresholdsUpdated();

    /// <summary> The next Threshold command made to be sent next frame. </summary>
    /// <returns></returns>
    Haptics::ThresholdCommand GetNextThresholdCommand();

    /// <summary> Store the Threshold command you've just sent to optimize sending it. </summary>
    /// <param name="command"></param>
    void StoreLastThresholdCommand(Haptics::ThresholdCommand command);

    //---------------------------------------------------------------------------------------------------
    // "Set Vibration Level" commands

    /// <summary> Sets the amplitude for a specific finger in the buffer. </summary>
    /// <param name="amplitude"></param>
    /// <param name="finger"></param>
    void AddVibrationLevel(int32_t finger, float amplitude);

    /// <summary> Copy a set of amplitudes into the 'previous command', which will be used as a fallback value in case
    /// no change is made to a specific finger. </summary>
    /// <param name="levels"></param>
    void StoreLastVibro(const std::vector<float>& levels);

    //---------------------------------------------------------------------------------------------------
    // "Set Wrist Level" commands

    /// <summary> Sets the Latest Wrist Level to a desired level </summary>
    /// <param name="amplitude"></param>
    void AddWristCommand(float amplitude);

    /// <summary> Copy an amplitude into the 'previous command', which will be used as a fallback value in case no
    /// change is made to the wrist. </summary>
    /// <param name="wrist"></param>
    void StoreLastWrist(float wrist);

    /// <summary> Clear the wrist command </summary>
    void ClearWristCommands();

public:
    //---------------------------------------------------------------------------------------------------
    // Command Compilation

    /// <summary> Compile the commands into a set of traditional Nova Commands. </summary>
    /// <returns></returns>
    void CompileTraditionalCommands(std::vector<float>& out_forceFeedbackLevels, std::vector<float>& out_buzzLevels,
                                    float& out_wristLvl);

    /// <summary> Clears any active command(s) on the Nova Glove, completely resetting the stream. </summary>
    void ClearAllCommands();

    /// <summary> Removes all non-active or elapsed Nova effects from the stream, ready for the next frame. </summary>
    void ResetBuffer();

};
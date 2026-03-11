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
 *
 */


#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Haptics
    {
        class BuzzCommand;
        class ForceFeedbackCommand;
        class TimedBuzzCommand;
        class ThumperCommand;
        class TimedThumpCommand;

        class SGCORE_API HapticGloveCommandBuffer;
    }// namespace Haptics
}// namespace SGCore

class SGCORE_API SGCore::Haptics::HapticGloveCommandBuffer
{
public:
    /// <summary> The base maximum amount of Force-Feedback Commands that can be in a queue. </summary>
    [[nodiscard]] static int32_t GetMaxForceFeedbackCommands();

    /// <summary> The base maximum amount of Vibrotactile Commands that can be in a queue. </summary>
    [[nodiscard]] static int32_t GetMaxBuzzCommands();

    /// <summary> The base maximum amount of Thumper Commands that can be in a queue. </summary>
    [[nodiscard]] static int32_t GetMaxThumpCommands();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new HapticsStream for a Haptic Glove. </summary>
    HapticGloveCommandBuffer();

    /**
     * The copy constructor.
     */
    HapticGloveCommandBuffer(const HapticGloveCommandBuffer& rhs);

    /**
     * The move constructor.
     */
    HapticGloveCommandBuffer(HapticGloveCommandBuffer&& rhs) noexcept;

    virtual ~HapticGloveCommandBuffer();

public:
    /**
     * The copy assignment operator.
     */
    HapticGloveCommandBuffer& operator=(const HapticGloveCommandBuffer& rhs);

    /**
     * The move assignment operator.
     */
    HapticGloveCommandBuffer& operator=(HapticGloveCommandBuffer&& rhs) noexcept;

public:
    /// <summary> All Force Feedback Commands that have been received this 'frame'. Will be flattened into a single command during FlushHapitcs. </summary>
    [[nodiscard]] const std::vector<ForceFeedbackCommand>& GetForceFeedbackCommandsQueue() const;

    /// <summary> All Timed Buzz Commands that have been received this 'frame'. Will be flattened into a single command during FlushHapitcs. </summary>
    [[nodiscard]] const std::vector<TimedBuzzCommand>& GetBuzzCommandsQueue() const;

    /// <summary> All Timed Thump Commands that have been received this 'frame'. Will be flattened into a single command during FlushHapitcs. </summary>
    [[nodiscard]] const std::vector<TimedThumpCommand>& GetThumperCommandsQueue() const;

public:
    //---------------------------------------------------------------------------------------------------------------------
    // Queue Functions

    /// <summary> Clears only the Force-Feedback Queue. </summary>
    void ClearForceFeedbackCommandsQueue();

    /// <summary> Clears all vibrations in the queue(s). </summary>
    void ClearVibrations();

    /// <summary> Clear all ongoing effects to this stream. </summary>
    void Clear();

    /// <summary> Add a new Force-Feedback command to the queue. Does not actually send it. </summary>
    /// <param name="forceFeedbackCommand"></param>
    void AddCommand(const ForceFeedbackCommand& forceFeedbackCommand);

    /// <summary> Add a new vibrotactile command to the queue. Does not actually send it. </summary>
    /// <param name="buzzCommand"></param>
    void AddCommand(const TimedBuzzCommand& buzzCommand);

    /// <summary> Add a new Thumper command to the queue. Does not actually send it. Does not work with SenseGlove, only for Nova's. </summary>
    /// <param name="thumpCommand"></param>
    void AddCommand(const TimedThumpCommand& thumpCommand);

    /// <summary> Update the active commands, using a deltaSeconds since last update, in seconds. Any timedCommands that are elapsed will be removed from the list. </summary>
    /// <param name="deltaSeconds"></param>
    void UpdateTimedCommands(float deltaSeconds);

public:
    //---------------------------------------------------------------------------------------------------------------------
    // Compilation Functions

    /// <summary> Compiles all ForceFeedback Levels in the queue into a single one. Does not clear the queue. Returns lastForceFeedbackCommand if no ForceFeedback commands are given. </summary>
    /// <param name="lastForceFeedbackCommand"></param>
    /// <returns></returns>
    [[nodiscard]] ForceFeedbackCommand GetTotalForceFeedbackLevels(const ForceFeedbackCommand& lastForceFeedbackCommand) const;

    /// <summary> Compiles all ForceFeedback Levels in the queue into a single one. Does not clear the queue. </summary>
    /// <returns></returns>
    [[nodiscard]] ForceFeedbackCommand GetTotalForceFeedbackLevels() const;

    /// <summary> Compiles all active vibrotactile in the queue into a single list of levels. Does not clear the queue. </summary>
    [[nodiscard]] BuzzCommand GetTotalBuzzLevels() const;

    /// <summary> Compiles all active vibrotactile in the queue into a single list of levels. Does not clear the queue. </summary>
    [[nodiscard]] ThumperCommand GetTotalThumperLevels() const;

public:
    // Flushing commands

    /// <summary> Compile all commands in the queue(s) into a single set of commands that can be sent to the glove. Only clears the ForceFeedback queue, and only if you want it to. </summary>
    /// <param name="lastBrakeLevel"></param>
    /// <param name="forceFeedbackCommand"></param>
    /// <param name="buzzCommand"></param>
    /// <param name="thumperCommand"></param>
    /// <param name="bClearForceFeedbackQueue"></param>
    /// <returns></returns>
    void FlushHaptics(const ForceFeedbackCommand& lastBrakeLevel, ForceFeedbackCommand& out_forceFeedbackCommand,
                      BuzzCommand& out_buzzCommand, ThumperCommand& out_thumperCommand,
                      bool bClearForceFeedbackQueue = true);

    /// <summary> Compile all commands in the queue(s) into a single set of commands that can be sent to the glove. Also updates & clears all queues. </summary>
    /// <param name="deltaSeconds"></param>
    /// <param name="lastBrakeLevel"></param>
    /// <param name="forceFeedbackCommand"></param>
    /// <param name="buzzCommand"></param>
    /// <param name="thumperCommand"></param>
    void FlushHaptics(float deltaSeconds, const ForceFeedbackCommand& lastBrakeLevel,
                      ForceFeedbackCommand& out_forceFeedbackCommand, BuzzCommand& out_buzzCommand,
                      ThumperCommand& out_thumperCommand);
};

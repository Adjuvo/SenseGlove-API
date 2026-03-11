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
 * Buzz Motor with timing parameters.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Fingers.hpp"
#include <SenseGlove/Common/Platform.hpp>
#include "BuzzCommand.hpp"

namespace SGCore
{
    namespace Haptics
    {
        /// <summary> Buzz motor commands that is meant to stop after a few milliseconds. </summary>
        /// <remarks> Intended use; this.levels indicates the actual command. </remarks>
        class SGCORE_API TimedBuzzCommand;
    }// namespace Haptics
}// namespace SGCore

/// <summary> Buzz motor commands that is meant to stop after a few milliseconds. </summary>
/// <remarks> Intended use; this.levels indicates the actual command. </remarks>
class SGCORE_API SGCore::Haptics::TimedBuzzCommand : public BuzzCommand
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
protected:
#endif  /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    /// <summary> Empty constructor for inheritance. </summary>
    TimedBuzzCommand();

public:
    /// <summary> Create a new TimeBuzzCommand for a single finger. </summary>
    /// <param name="finger"></param>
    /// <param name="magnitude"></param>
    /// <param name="durationSeconds"></param>
    /// <param name="startTimeSeconds"></param>
    TimedBuzzCommand(EFinger finger, int32_t magnitude, float durationSeconds, float startTimeSeconds = 0.0f);

    /// <summary>
    /// Create a new buzz motor command that expires after timing_ms.
    /// </summary>
    /// <param name="baseCommand"></param>
    /// <param name="durationSeconds"></param>
    /// <param name="startTimeSeconds">Optional, starts the effect at a certain time.</param>
    TimedBuzzCommand(const BuzzCommand& baseCommand, float durationSeconds, float startTimeSeconds = 0.0f);

    /**
     * The copy constructor.
     */
    TimedBuzzCommand(const TimedBuzzCommand& rhs);

    /**
     * The move constructor.
     */
    TimedBuzzCommand(TimedBuzzCommand&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~TimedBuzzCommand() override;

public:
    /**
     * The copy assignment operator.
     */
    TimedBuzzCommand& operator=(const TimedBuzzCommand& rhs);

    /**
     * The move assignment operator.
     */
    TimedBuzzCommand& operator=(TimedBuzzCommand&& rhs) noexcept;

public:
    /// <summary> Copy this Buzz Command's values into a new object. </summary>
    /// <returns></returns>
    [[nodiscard]] virtual BuzzCommand Copy() const override;

    /// <summary> Merges this base command with another command. </summary>
    /// <param name="buzzCommand"></param>
    /// <returns></returns>
    [[nodiscard]] virtual BuzzCommand Merge(const BuzzCommand& buzzCommand) const override;

public:
    /// <summary> Access the base command, which indicates the buzz levels to keep untill time elapses. </summary>
    /// <returns></returns>
    [[nodiscard]] virtual const BuzzCommand& GetBaseCommand() const;

    /// <summary> The total time [milliseconds] each buzz motor should be vibrating for. </summary>
    [[nodiscard]] float GetDuration() const;

    /// <summary> The time elapsed since the command was sent [milliseconds]. </summary>
    [[nodiscard]] float GetElapsedTime() const;

    /// <summary> Check if this timed command's timing has elapsed. </summary>
    /// <returns></returns>
    [[nodiscard]] virtual bool HasTimeElapsed() const;

    /// <summary> Represents how far this effect is in its playtime; [0...1], where 0 means at the start, and 1 means at the end. </summary>
    /// <param name="bClamp01">Optional parameter; ensures this value is always between 0 and 1..</param>
    [[nodiscard]] virtual float NormalizedTime(bool bClamp01 = true) const;

public:
    /// <summary> Reset the timings of this BuzzCommand, allowing us to re-use it. </summary>
    virtual void ResetTiming();

    /// <summary> Update the elapsed time to check if the buzz motors should stop. </summary>
    /// <param name="deltaSeconds"></param>
    virtual void UpdateTiming(float deltaSeconds);

public:
    [[nodiscard]] virtual std::string ToString() const override;
};

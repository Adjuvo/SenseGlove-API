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

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Haptics
    {
        class SGCORE_API TimedThumpCommand;

        class ThumperCommand;
    }// namespace Haptics
}// namespace SGCore

class SGCORE_API SGCore::Haptics::TimedThumpCommand
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
protected:
#endif  /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    /// <summary> Internal, empty, for extended classes. </summary>
    TimedThumpCommand();

public:
    /// <summary> Create a new Timed Thumper Command. </summary>
    /// <param name="magnitude">Value between 0 .. 1 representing the magnitude of the system.</param>
    /// <param name="durationSeconds"></param>
    /// <param name="startTimeSeconds"></param>
    TimedThumpCommand(int32_t magnitude, float durationSeconds, float startTimeSeconds = 0.0f);

    /// <summary> Create a new Timed Thumper Command. </summary>
    /// <param name="baseCommand"></param>
    /// <param name="durationSeconds"></param>
    /// <param name="startTimeSeconds"></param>
    TimedThumpCommand(const ThumperCommand& baseCommand, float durationSeconds, float startTimeSeconds = 0.0f);

    /**
     * The copy constructor.
     */
    TimedThumpCommand(const TimedThumpCommand& rhs);

    /**
     * The move constructor.
     */
    TimedThumpCommand(TimedThumpCommand&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~TimedThumpCommand();

public:
    /**
     * The copy assignment operator.
     */
    TimedThumpCommand& operator=(const TimedThumpCommand& rhs);

    /**
     * The move assignment operator.
     */
    TimedThumpCommand& operator=(TimedThumpCommand&& rhs) noexcept;

public:
    /// <summary> Magnitude in %. </summary>
    [[nodiscard]] int32_t GetMagnitude() const;

    /// <summary> Duration in seconds. </summary>
    [[nodiscard]] float GetDuration() const;

    /// <summary> The elapsed time so far. </summary>
    [[nodiscard]] float GetElapsedTime() const;

    /// <summary> Returns true if the timed command has elapsed. </summary>
    [[nodiscard]] bool HasTimeElapsed() const;

public:
    /// <summary> Copy the parameters of this ThumperCommand into another instance. </summary>
    /// <returns></returns>
    virtual TimedThumpCommand Copy(bool bCopyElapsed = true) const;

    /// <summary> Update the timing on this Thumper Command. </summary>
    /// <param name="deltaSeconds"></param>
    virtual void Update(float deltaSeconds);

    [[nodiscard]] virtual bool Equals(const ThumperCommand& command) const;

public:
    [[nodiscard]] std::string ToString() const;
};

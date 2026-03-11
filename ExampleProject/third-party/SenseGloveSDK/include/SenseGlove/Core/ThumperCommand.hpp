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
 * Thumper command.
 */


#pragma once

#include <cstdint>
#include <memory>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Haptics
    {
        class SGCORE_API ThumperCommand;
    }// namespace Haptics
}// namespace SGCore

class SGCORE_API SGCore::Haptics::ThumperCommand
{
public:
    /// <summary> A command that turns off all force feedback on the Sense Glove. </summary>
    [[nodiscard]] static const ThumperCommand& Off();

protected:
    /// <summary> Minimum Force-Feedback Level. </summary>
    [[nodiscard]] static int32_t GetThumpMin();

    /// <summary> Maximum Force-Feedback Level. </summary>
    [[nodiscard]] static int32_t GetThumpMax();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
private:
#endif  /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    /// <summary> Empty constructor for inheritance. </summary>
    ThumperCommand();

public:
    /// <summary> Create a new Thumper Command. </summary>
    /// <param name="magn"></param>
    /// <returns></returns>
    explicit ThumperCommand(int32_t magnitude);

    /**
     * The copy constructor.
     */
    ThumperCommand(const ThumperCommand& rhs);

    /**
     * The move constructor.
     */
    ThumperCommand(ThumperCommand&& rhs) noexcept;

    virtual ~ThumperCommand();

public:
    /**
     * The copy assignment operator.
     */
    ThumperCommand& operator=(const ThumperCommand& rhs);

    /**
     * The move assignment operator.
     */
    ThumperCommand& operator=(ThumperCommand&& rhs) noexcept;

public:
    /// <summary> Thumper intensity, a level between 0 and 100. </summary>
    [[nodiscard]] int32_t GetMagnitude() const;

    void SetMagnitude(int32_t magnitude);

public:
    /// <summary> Duplicate the Thumper command. </summary>
    /// <returns></returns>
    [[nodiscard]] ThumperCommand Copy() const;

    /// <summary> Merge two ThumperCommands into one. </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    [[nodiscard]] ThumperCommand Merge(const ThumperCommand& thumperCommand) const;

    [[nodiscard]] virtual bool Equals(const ThumperCommand& thumperCommand) const;

protected:
    [[nodiscard]] int32_t Validate(int32_t value) const;
};

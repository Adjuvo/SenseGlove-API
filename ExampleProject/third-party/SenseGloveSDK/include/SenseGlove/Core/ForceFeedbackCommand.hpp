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
 * Force Feedback command specific for the Sense Glove.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Fingers.hpp"
#include <SenseGlove/Common/Platform.hpp>
#include "FingerCommand.hpp"

namespace SGCore
{
    namespace Haptics
    {
        /// <summary> A Force-Feedback command for the Sense Glove, with levels for each finger. </summary>
        class SGCORE_API ForceFeedbackCommand;
    }// namespace Haptics
}// namespace SGCore

/// <summary> A Force-Feedback command for the Sense Glove, with levels for each finger. </summary>
class SGCORE_API SGCore::Haptics::ForceFeedbackCommand : public FingerCommand
{
public:
    /// <summary> A command that turns off all force feedback on the Sense Glove. </summary>
    [[nodiscard]] static const ForceFeedbackCommand& Off();

protected:
    /// <summary> Minimum Force-Feedback Level. </summary>
    [[nodiscard]] static int32_t GetMinForceFeedbackLevel();

    /// <summary> Maximum Force-Feedback Level. </summary>
    [[nodiscard]] static int32_t GetMaxForceFeedbackLevel();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
protected:
#endif  /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    /// <summary> Empty constructor for internal initialization. </summary>
    ForceFeedbackCommand();

public:
    /// <summary> Create a new Force-Feedback Command, with levels for each finger stored in an int[5] array. </summary>
    ForceFeedbackCommand(const std::vector<int32_t>& forceFeedbackLevels);

    ///<summary> Create a new Force-Feedback Command, with levels for each finger. </summary>
    ForceFeedbackCommand(int32_t thumb, int32_t index, int32_t middle, int32_t ring, int32_t pinky);

    /// <summary> Create a new Force-Feedback command, with only one finger being activated. </summary>
    ForceFeedbackCommand(EFinger finger, int32_t buzzLevel);

    /**
     * The copy constructor.
     */
    ForceFeedbackCommand(const ForceFeedbackCommand& rhs);

    /**
     * The move constructor.
     */
    ForceFeedbackCommand(ForceFeedbackCommand&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~ForceFeedbackCommand() override;

public:
    /**
     * The copy assignment operator.
     */
    ForceFeedbackCommand& operator=(const ForceFeedbackCommand& rhs);

    /**
     * The move assignment operator.
     */
    ForceFeedbackCommand& operator=(ForceFeedbackCommand&& rhs) noexcept;

public:
    /// <summary> Copy this ForceFeedback Command into a new object. </summary>
    [[nodiscard]] virtual ForceFeedbackCommand Copy() const;

    /// <summary> Merge this finger command with another, taking the maximum value between the two. </summary>
    [[nodiscard]] virtual ForceFeedbackCommand Merge(const ForceFeedbackCommand& command) const;

protected:
    /// <summary> Ensure that an input values is places in between the minimum and maximum range. </summary>
    [[nodiscard]] virtual int32_t Validate(int32_t value) const override;
};

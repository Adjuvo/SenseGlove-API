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
 * Buzz motor command specific for the Sense Glove.
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
        /// <summary> A vibration command for the Sense Glove, with levels for each finger. </summary>
        class SGCORE_API BuzzCommand;
    }// namespace Haptics
}// namespace SGCore

/// <summary> A vibration command for the Sense Glove, with levels for each finger. </summary>
class SGCORE_API SGCore::Haptics::BuzzCommand : public FingerCommand
{
public:
    /// <summary> A command that turns off all vibration motors of the Sense Glove. </summary>
    [[nodiscard]] static const BuzzCommand& Off();

protected:
    /// <summary> The minimum buzz motor level input. </summary>
    [[nodiscard]] static int32_t GetMinBuzzLevel();

    /// <summary> The maximum buzz motor level input. </summary>
    [[nodiscard]] static int32_t GetMaxBuzzLevel();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The basic constructor. </summary>
    BuzzCommand();

    /// <summary> Create a new buzz motor command, where each finger level is contained inside an array of size 5. </summary>
    explicit BuzzCommand(const std::vector<int32_t>& buzzLevels);

    /// <summary> Create a new Buzz Motor command, indicating the intensity for each finger. </summary>
    BuzzCommand(int32_t thumb, int32_t index, int32_t middle, int32_t ring, int32_t pinky);

    /// <summary> Create a new Buzz Motor command, with only one finger being activated. </summary>
    BuzzCommand(EFinger finger, int32_t buzzLevel);

    /**
     * The copy constructor.
     */
    BuzzCommand(const BuzzCommand& rhs);

    /**
     * The move constructor.
     */
    BuzzCommand(BuzzCommand&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~BuzzCommand() override;

public:
    /**
     * The copy assignment operator.
     */
    BuzzCommand& operator=(const BuzzCommand& rhs);

    /**
     * The move assignment operator.
     */
    BuzzCommand& operator=(BuzzCommand&& rhs) noexcept;

public:
    /// <summary> Copy this Buzz Command into a new object. </summary>
    [[nodiscard]] virtual BuzzCommand Copy() const;

    /// <summary> Merge this command with another, taking the maximum value between the two. </summary>
    [[nodiscard]] virtual BuzzCommand Merge(const BuzzCommand& command) const;

protected:
    /// <summary> Ensure that an input values is places in between the minimum and maximum range. </summary>
    [[nodiscard]] virtual int32_t Validate(int32_t value) const override;
};

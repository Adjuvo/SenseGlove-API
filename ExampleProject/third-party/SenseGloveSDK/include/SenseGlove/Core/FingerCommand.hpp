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
 * A command for five fingers that can be sent to a Sense Glove device.
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
        /// <summary> A command that contains values (levels) for five fingers. </summary>
        class SGCORE_API FingerCommand;
    }// namespace Haptics
}// namespace SGCore

/// <summary> A command that contains values (levels) for five fingers. </summary>
class SGCORE_API SGCore::Haptics::FingerCommand
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
public:
#else   /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
protected:
#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */
    FingerCommand();

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    FingerCommand(const std::vector<int32_t>& levels);
#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */

public:
    /**
     * The copy constructor.
     */
    FingerCommand(const FingerCommand& rhs);

    /**
     * The move constructor.
     */
    FingerCommand(FingerCommand&& rhs) noexcept;

    virtual ~FingerCommand();

public:
    /**
     * The copy assignment operator.
     */
    FingerCommand& operator=(const FingerCommand& rhs);

    /**
     * The move assignment operator.
     */
    FingerCommand& operator=(FingerCommand&& rhs) noexcept;

public:
    [[nodiscard]] virtual const std::vector<int32_t>& GetLevels() const;

protected:
    /// <summary> Input level for specific finger. </summary>
    void SetLevels(const std::vector<int32_t>& levels);

public:
    [[nodiscard]] virtual int32_t GetLevel(int32_t finger) const;
    virtual void SetLevel(int32_t finger, int32_t value);

public:
    /// <summary> Check if this command contains the same values as another. </summary>
    [[nodiscard]] virtual bool Equals(const FingerCommand& fingerCommand) const;

    /// <returns> Create a string representation of this finger command. </returns>
    [[nodiscard]] virtual std::string ToString() const;

protected:
    /// <summary> Ensure that a value is within acceptable range. </summary>
    [[nodiscard]] virtual int32_t Validate(int32_t value) const;
};

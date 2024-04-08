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
 * Internal class to hold 'Threshold Commands' for specific fingers. Can be sent
 * to a Device, or used internally.
 * Threshold Commands tell our device "When your sensor data is higher than this
 * threshold, lock FFB. Otherwise, turn it back off".
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Haptics
    {
        /// <summary> Internal class to hold 'Threshold Commands' for specific fingers. Can be sent to a Device, or
        /// used internally. </summary>
        class SGCORE_API ThresholdCommand;
    }// namespace Haptics
}// namespace SGCore

/// <summary> Internal class to hold 'Threshold Commands' for specific fingers. Can be sent to a Device, or used
/// internally. </summary>
class SGCORE_API SGCore::Haptics::ThresholdCommand
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

public:
    /**
     * The default constructor.
     */
    ThresholdCommand();

    ThresholdCommand(const std::vector<bool>& affectedFingers, const std::vector<float>& thresholdValues);

    /**
     * The copy constructor.
     */
    ThresholdCommand(const ThresholdCommand& rhs);

    /**
     * The move constructor.
     */
    ThresholdCommand(ThresholdCommand&& rhs) noexcept;

    virtual ~ThresholdCommand();

public:
    /**
     * The copy assignment operator.
     */
    ThresholdCommand& operator=(const ThresholdCommand& rhs);

    /**
     * The move assignment operator.
     */
    ThresholdCommand& operator=(ThresholdCommand&& rhs) noexcept;

    //-------------------------------------------------------------------------------------------------------------------------------------
    // Accessor Functions

public:
    /// <summary> Retrieve the threshold of a particular finger. </summary>
    /// <param name="finger"></param>
    /// <returns></returns>
    SG_NODISCARD float GetThreshold(int32_t finger) const;

    /// <summary> Activates the threshold for a finger at a particular value. </summary>
    /// <param name="finger"></param>
    /// <param name="thresholdValue"></param>
    void SetThreshold(int32_t finger, float thresholdValue);

    SG_NODISCARD std::vector<float> GetThresholds() const;

    /// <summary> Activates the threshold for a finger at a particular value. </summary>
    /// <param name="affectedFingers"></param>
    /// <param name="thresholdValues"></param>
    void SetThresholds(const std::vector<bool>& affectedFingers, const std::vector<float>& thresholdValues);

    /// <summary> If true, the threshold on a finger should be active. </summary>
    /// <param name="finger"></param>
    /// <returns></returns>
    SG_NODISCARD bool GetFingerActive(int32_t finger) const;

    SG_NODISCARD std::vector<bool> GetActiveFingers() const;

    /// <summary> Deactivates Threshold Mode for a particular finger. </summary>
    /// <param name="finger"></param>
    void ClearThreshold(int32_t finger);

    /// <summary> Disables Threshold mode for all fingers. Clears the ActiveFingers, but keeps the Thresholds value for
    /// now, in case you want to re-apply them later. </summary>
    void ClearThresholds();

    //-------------------------------------------------------------------------------------------------------------------------------------
    // Utility Functions

public:
    /// <summary> Returns true if both values are exactly equal. </summary>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const ThresholdCommand& thresholdCommand) const;

public:
    /// <summary> Print the contents of this Threshold Command. If inactive, a '-' is shown. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string ToString() const;
};
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
 * Internal class to hold 'Threshold Commands' for specific fingers. Can be sent to a Device, or used internally.
 * Threshold Commands tell our device "When your sensor data is higher than this threshold, lock FFB. Otherwise, turn it back off".
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Haptics
    {
        /// <summary> Internal class to hold 'Threshold Commands' for specific fingers. Can be sent to a Device, or used internally. </summary>
        class SGCORE_API ThresholdCommand;
    }// namespace Haptics
}// namespace SGCore

/// <summary> Internal class to hold 'Threshold Commands' for specific fingers. Can be sent to a Device, or used internally. </summary>
class SGCORE_API SGCore::Haptics::ThresholdCommand
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
    ThresholdCommand(const ThresholdCommand& rhs);

    /**
     * The move constructor.
     */
    ThresholdCommand(ThresholdCommand&& rhs)
    noexcept;

    virtual ~ThresholdCommand();


    /**
     * The copy assignment operator.
     */
    ThresholdCommand& operator=(const ThresholdCommand& rhs);

    /**
     * The move assignment operator.
     */
    ThresholdCommand& operator=(ThresholdCommand&& rhs) noexcept;

public:

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    ThresholdCommand(); 

    ThresholdCommand(const std::vector<bool>& affectedFingers, const std::vector<float>& thresholdValues);

    //-------------------------------------------------------------------------------------------------------------------------------------
    // Accessor Functions

    /// <summary> Activates the threshold for a finger at a particular value. </summary>
    /// <param name="finger"></param>
    /// <param name="thresholdValue"></param>
    void SetThreshold(int32_t finger, float thresholdValue);

    /// <summary> Activates the threshold for a finger at a particular value. </summary>
    /// <param name="finger"></param>
    /// <param name="thresholdValue"></param>
    void SetThresholds(const std::vector<bool>& affectedFingers, const std::vector<float>& thresholdValue);


    /// <summary> Retrieve the threshold of a particular finger </summary>
    /// <param name="finger"></param>
    /// <returns></returns>
    float GetThreshold(int32_t finger);

    /// <summary> If true, the threshold on a finger should be active. </summary>
    /// <param name="finger"></param>
    /// <returns></returns>
    bool GetFingerActive(int32_t finger);

    std::vector<float> GetThresholds();

    std::vector<bool> GetActiveFingers();

    /// <summary> Deactivates Threshold Mode for a particular finger. </summary>
    /// <param name="finger"></param>
    void ClearThreshold(int32_t finger);

    /// <summary> Disables Threshold mode for all fingers. Clears the ActiveFingers, but keeps the Thresholds value for now, in case you want to re-apply them later. </summary>
    void ClearThresholds();




    //-------------------------------------------------------------------------------------------------------------------------------------
    // Utility Functions

    /// <summary> Print the contents of this Threshold Command. If inactive, a '-' is shown. </summary>
    /// <returns></returns>
    std::string ToString();

    /// <summary> Returns true if both values are exactly equal </summary>
    /// <returns></returns>
    bool Equals(const ThresholdCommand& other);

};

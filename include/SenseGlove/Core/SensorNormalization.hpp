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
 * A script to normalize any set of floating point values by looking at their minimum and maximum values. Used for automagical calibration.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Util
    {
        /// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active contact feedback in the front strap. </summary>
        class SGCORE_API SensorNormalization;
    }// namespace Util
}// namespace SGCore

/// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active contact feedback in the front strap. </summary>
class SGCORE_API SGCore::Util::SensorNormalization
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
    SensorNormalization(const SensorNormalization& rhs);

    /**
     * The move constructor.
     */
    SensorNormalization(SensorNormalization&& rhs)
    noexcept;

    virtual ~SensorNormalization();


    /**
     * The copy assignment operator.
     */
    SensorNormalization& operator=(const SensorNormalization& rhs);

    /**
     * The move assignment operator.
     */
    SensorNormalization& operator=(SensorNormalization&& rhs) noexcept;

public:

    SensorNormalization();

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    SensorNormalization(std::vector<float> movementRanges);

    //---------------------------------------------------------------------------------
    // Accessors

public:

    /// <summary> If true, the normalization collection is active. If false, we're no longer collecting min / max values. </summary>
    bool GetCollectNormalization();
    void SetCollectNormalization(bool value);

    //---------------------------------------------------------------------------------
    // Member Functions

public:

    /// <summary> The amount of items in this collector Useful for FOR loops. </summary>
    int32_t GetLength();

    /// <summary> The amount of values that have moved the appropriate amount. </summary>
    int32_t GetMoveCount();

    /// <summary> Returns true if all sensors are allowed to move. </summary>
    bool AllSensorsMoving();

    /// <summary> Reset the normalization of values. </summary>
    void ResetNormalization();

    /// <summary>  </summary>
    /// <param name="index"></param>
    /// <param name="value"></param>
    void UpdateNormalization(float value, int32_t index) const;

    /// <summary> Normalize a value on a specific index, and update Normalization while you're at it. </summary>
    /// <param name="value"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    float NormalizeValue(float value, int32_t index) const;

    /// <summary> Update and Normalize a set of values, provided this is the same length. </summary>
    /// <param name="values"></param>
    /// <returns></returns>
    std::vector<float> NormalizeValues(const std::vector<float>& values) const;

    /// <summary> Returns true if a sensor on this index has moved enough. </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    bool MovedEnough(int32_t index) const;

    /// <summary> Turn a value from 0 .. 1 back into [minValue ... maxValue] range for the Nova Glove. </summary>
    /// <param name="value01"></param>
    /// <param name="index"></param>
    /// <param name="fallbackValue"></param>
    /// <returns></returns>
    float DeNormalize(float value01, int32_t index, float fallbackValue = 1.0f) const;
};

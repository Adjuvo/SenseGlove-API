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
 * A script to normalize any set of floating point values by looking at their
 * minimum and maximum values. Used for automagical calibration.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Util
    {
        /// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module,
        /// and active contact feedback in the front strap. </summary>
        class SGCORE_API SensorNormalization;
    }// namespace Util
}// namespace SGCore

/// <summary> Interface for Nova 2.0 Gloves.  A soft glove with detachable force-feedback and sensor module, and active
/// contact feedback in the front strap. </summary>
class SGCORE_API SGCore::Util::SensorNormalization
{
public:
    //---------------------------------------------------------------------------------
    // Serialize / Deserialize

    SG_NODISCARD static bool Deserialize(const std::string& serialized, SensorNormalization& out_normalizer);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    /**
     * The default constructor.
     */
    SensorNormalization();

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    explicit SensorNormalization(const std::vector<float>& movementRanges);

    //---------------------------------------------------------------------------------
    // Accessors

    /**
     * The copy constructor.
     */
    SensorNormalization(const SensorNormalization& rhs);

    /**
     * The move constructor.
     */
    SensorNormalization(SensorNormalization&& rhs) noexcept;

    virtual ~SensorNormalization();

public:
    /**
     * The copy assignment operator.
     */
    SensorNormalization& operator=(const SensorNormalization& rhs);

    /**
     * The move assignment operator.
     */
    SensorNormalization& operator=(SensorNormalization&& rhs) noexcept;

    //---------------------------------------------------------------------------------
    // Accessors

public:
    /// <summary> If true, the normalization collection is active. If false, we're no longer collecting min / max
    /// values. </summary>
    SG_NODISCARD bool CollectsNormalization() const;

    void SetCollectNormalization(bool bCollectNormalization);

    //---------------------------------------------------------------------------------
    // Member Functions

public:
    /// <summary> The amount of items in this collector Useful for FOR loops. </summary>
    SG_NODISCARD int32_t GetLength() const;

    /// <summary> The amount of values that have moved the appropriate amount. </summary>
    SG_NODISCARD int32_t GetMoveCount() const;

    /// <summary> Returns true if all sensors are allowed to move. </summary>
    SG_NODISCARD bool AllSensorsMoving() const;

    /// <summary> Reset the normalization of values. </summary>
    void ResetNormalization();

    /// <summary>  </summary>
    /// <param name="index"></param>
    /// <param name="value"></param>
    void UpdateNormalization(float value, int32_t index);

    /// <summary> Normalize a value on a specific index, and update Normalization while you're at it. </summary>
    /// <param name="value"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    float NormalizeValue(float value, int32_t index);

    /// <summary> Update and Normalize a set of values, provided this is the same length. </summary>
    /// <param name="values"></param>
    /// <returns></returns>
    std::vector<float> NormalizeValues(const std::vector<float>& values);

    /// <summary> Returns true if a sensor on this index has moved enough. </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    SG_NODISCARD bool MovedEnough(int32_t index) const;

    /// <summary> Turn a value from 0 .. 1 back into [minValue ... maxValue] range for the Nova Glove. </summary>
    /// <param name="value01"></param>
    /// <param name="index"></param>
    /// <param name="fallbackValue"></param>
    /// <returns></returns>
    SG_NODISCARD float Denormalize(float value01, int32_t index, float fallbackValue = 1.0f) const;

    //---------------------------------------------------------------------------------
    // Serialize / Deserialize

    SG_NODISCARD std::string Serialize();
};
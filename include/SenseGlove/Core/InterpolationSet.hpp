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
 * Data class containing all variables to map an input value from one range to
 * another.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        /// <summary> Set of variables to map a value from one range to the next. </summary>
        class SGCORE_API InterpolationSet;
    }// namespace Kinematics
}// namespace SGCore

/// <summary> Set of variables to map a value from one range to the next. </summary>
class SGCORE_API SGCore::Kinematics::InterpolationSet
{
public:
    /// <summary> Convert a string notation of an InterpolationSet into a new class instance. </summary>
    /// <param name="serializedString"></param>
    /// <returns></returns>
    static InterpolationSet Deserialize(const std::string& serializedString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Creates a basic interpolation set, without limits. </summary>
    InterpolationSet();

    /// <summary> Create a new interpolation set without limits. </summary>
    InterpolationSet(float from1, float from2, float to1, float to2);

    /// <summary> Create a new interpolation set with limits. </summary>
    InterpolationSet(float from1, float from2, float to1, float to2, float min, float max);

    /**
     * The copy constructor.
     */
    InterpolationSet(const InterpolationSet& rhs);

    /**
     * The move constructor.
     */
    InterpolationSet(InterpolationSet&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~InterpolationSet();

public:
    /**
     * The copy assignment operator.
     */
    InterpolationSet& operator=(const InterpolationSet& rhs);

    /**
     * The move assignment operator.
     */
    InterpolationSet& operator=(InterpolationSet&& rhs) noexcept;

public:
    /// <summary> First value of input range..</summary>
    SG_NODISCARD float GetX0() const;

    void SetX0(float x0);

    /// <summary> Second value of input range. </summary>
    SG_NODISCARD float GetX1() const;

    void SetX1(float x1);

    /// <summary> First value of output range. </summary>
    SG_NODISCARD float GetY0() const;

    void SetY0(float y0);

    /// <summary> Second value of output range. </summary>
    SG_NODISCARD float GetY1() const;

    void SetY1(float y1);

    /// <summary> Minimum range of the output value. </summary>
    SG_NODISCARD float GetMin() const;

    void SetMin(float min);

    /// <summary> Maximum range of the output value. </summary>
    SG_NODISCARD float GetMax() const;

    void SetMax(float max);

public:
    /// <summary> Calculate an output value in range [x0...x1] to [y0..y1]. </summary>
    SG_NODISCARD float Get(float value, bool bLimit, bool bNormalizeAngle = false) const;

public:
    /// <summary> Returns true if this InterpolationSet has the same values as another set. </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    SG_NODISCARD bool Equals(const InterpolationSet& interpolationSet) const;

public:
    SG_NODISCARD std::string ToString() const;

    SG_NODISCARD std::string ToString(bool bLimits) const;

    /// <summary> Convert this InterpolationSet into a string notation so it can be stored on disk. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string Serialize() const;
};
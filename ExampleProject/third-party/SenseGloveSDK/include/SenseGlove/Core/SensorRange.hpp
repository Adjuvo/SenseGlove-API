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
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Kinematics
    {
        class Vect3D;
    }// namespace Kinematics

    namespace Calibration
    {
        class SGCORE_API SensorRange;
    }// namespace Calibration
}// namespace SGCore

class SGCORE_API SGCore::Calibration::SensorRange
{
public:
    /// <summary> Generates a Sensor Range where minimum values are float.MaxValue and maximum values are float.MinValue. </summary>
    /// <returns></returns>
    [[nodiscard]] static const SensorRange& ForCalibration();

    /// <summary> Convert a serialized SensorRange back into the appropriate class. </summary>
    /// <param name="serializedString"></param>
    /// <returns></returns>
    [[nodiscard]] static SensorRange Deserialize(const std::string& serializedString);

public:
    /// <summary> Evaluate maxValues so that it contains the highest x, y, and z values between currentValues and maxValues. </summary>
    /// <param name="currentValues"></param>
    /// <param name="maxValues"></param>
    static void CheckMax(const Kinematics::Vect3D& currentValues, Kinematics::Vect3D& out_maxValues);

    /// <summary> Evaluate minValues so that it contains the lowest x, y, and z values between currentValues and minValues. </summary>
    /// <param name="currentValues"></param>
    /// <param name="minValues"></param>
    static void CheckMin(const Kinematics::Vect3D& currentValues, Kinematics::Vect3D& out_minValues);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new instance of a SensorRange with values at 0, 0. </summary>
    SensorRange();

    /// <summary> Create a new SensorRange with predefined Min/Max values. </summary>
    /// <param name="minValues"></param>
    /// <param name="maxValues"></param>
    SensorRange(const std::vector<Kinematics::Vect3D>& minValues, const std::vector<Kinematics::Vect3D>& maxValues);

    /**
     * The copy constructor.
     */
    SensorRange(const SensorRange& rhs);

    /**
     * The move constructor.
     */
    SensorRange(SensorRange&& rhs) noexcept;

    virtual ~SensorRange();

public:
    /**
     * The copy assignment operator.
     */
    SensorRange& operator=(const SensorRange& rhs);

    /**
     * The move assignment operator.
     */
    SensorRange& operator=(SensorRange&& rhs) noexcept;

public:
    /// <summary> Access the lowest values values of this range. </summary>
    [[nodiscard]] const std::vector<Kinematics::Vect3D>& GetMinValues() const;

    /// <summary> Set the lowest values values of this range. </summary>
    void SetMinValues(const std::vector<Kinematics::Vect3D>& values);

    /// <summary> Access the highest values values of this range. </summary>
    [[nodiscard]] const std::vector<Kinematics::Vect3D>& GetMaxValues() const;

    /// <summary> Set the highest values values of this range. </summary>
    void SetMaxValues(const std::vector<Kinematics::Vect3D>& values);

    /// <summary> Access the difference between min and max values. </summary>
    [[nodiscard]] const std::vector<Kinematics::Vect3D>& GetRange() const;

public:
    /// <summary> Update the Range based on the current MinValues and MaxValues. </summary>
    void UpdateRange();

    /// <summary> In otherValues are greater/smaller than this current range, update them. </summary>
    /// <param name="otherValues"></param>
    void CheckForExtremes(const std::vector<Kinematics::Vect3D>& otherValues);

public:
    /// <summary> Report the Range value of this SensorRange, separated by a comma. </summary>
    /// <param name="bYOnly"></param>
    /// <returns></returns>
    [[nodiscard]] std::string RangeString(bool bYOnly = true) const;

    /// <summary> Convert this SensorRange into a string rotation [min ... max]. </summary>
    /// <param name="bYOnly"></param>
    /// <returns></returns>
    [[nodiscard]] std::string ToString(bool bYOnly = true) const;

    /// <summary> Serialize this SensorRange into a string representation, that can be deserialized later. </summary>
    /// <returns></returns>
    [[nodiscard]] std::string Serialize() const;
};

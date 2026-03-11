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
    namespace Calibration
    {
        class SGCORE_API CalibrationDataPoint;
    }// namespace Calibration

    namespace Kinematics
    {
        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

class SGCORE_API SGCore::Calibration::CalibrationDataPoint
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    CalibrationDataPoint();
#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */

    /// <summary> Create a new data point. </summary>
    /// <param name="currentStage"></param>
    /// <param name="calibrationValues"></param>
    CalibrationDataPoint(int32_t currentStage, const std::vector<Kinematics::Vect3D>& calibrationValues);

    /**
     * The copy constructor.
     */
    CalibrationDataPoint(const CalibrationDataPoint& rhs);

    /**
     * The move constructor.
     */
    CalibrationDataPoint(CalibrationDataPoint&& rhs) noexcept;

    /// <summary> The basic destructor. </summary>
    virtual ~CalibrationDataPoint();

public:
    /**
     * The copy assignment operator.
     */
    CalibrationDataPoint& operator=(const CalibrationDataPoint& rhs);

    /**
     * The move assignment operator.
     */
    CalibrationDataPoint& operator=(CalibrationDataPoint&& rhs) noexcept;

public:
    /// <summary> Actual calibration values. </summary>
    [[nodiscard]] const std::vector<Kinematics::Vect3D>& GetCalibrationValues() const;

    /// <summary> The Calibration stage this data point belongs to. </summary>
    [[nodiscard]] int32_t GetStage() const;

public:
    /// <summary> Log Calibration values for storing on disk. </summary>
    /// <param name="delimiter"></param>
    /// <returns></returns>
    [[nodiscard]] std::string ToLogData(const std::string& delimiter = "\t") const;
};

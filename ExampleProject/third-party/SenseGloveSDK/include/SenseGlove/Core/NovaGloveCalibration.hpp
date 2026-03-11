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

#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Calibration
    {
        class SGCORE_API NovaGloveCalibration;
    }// namespace Calibration

    namespace Kinematics
    {
        class Vect3D;
    }// namespace Kinematics

    namespace Nova
    {
        class NovaGloveHandProfile;
    }// namespace Nova
}// namespace SGCore

class SGCORE_API SGCore::Calibration::NovaGloveCalibration
{
public:
    /// <summary> Apply a glove's default interpolation values to a profile, using the 'default' hand angles from calibration. </summary>
    static void ApplyDefaultCalibrationInterpolationValues(
            const std::vector<Kinematics::Vect3D>& retractedValues,
            const std::vector<Kinematics::Vect3D>& extendedValues,
            const Nova::NovaGloveHandProfile& profile);

    /// <summary> Apply a set of sensor-to-joint-angle interpolations to a nova profile. </summary>
    /// <param name="retractedValues"></param>
    /// <param name="extendedValues"></param>
    /// <param name="retractedAngles"></param>
    /// <param name="extendedAngles"></param>
    /// <param name="profile"></param>
    static void ApplyInterpolationValues(
            const std::vector<Kinematics::Vect3D>& retractedValues,
            const std::vector<Kinematics::Vect3D>& extendedValues,
            const std::vector<std::vector<Kinematics::Vect3D>>& retractedAngles,
            const std::vector<std::vector<Kinematics::Vect3D>>& extendedAngles,
            const Nova::NovaGloveHandProfile& profile);

public:
    NovaGloveCalibration() = delete;
    virtual ~NovaGloveCalibration() = delete;
};

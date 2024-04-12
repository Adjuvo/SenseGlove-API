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
 * Contains kinematic formulae and wrappers for Sense Glove mathematics.
 */


#pragma once

#include <vector>

#include "Fingers.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class BasicHandModel;

        class SGCORE_API JointKinematics;

        class Quat;

        class Vect3D;
    }// namespace Kinematics
}// namespace SGCore

class SGCORE_API SGCore::Kinematics::JointKinematics
{
public:
    /// <summary>
    /// Perform forward Kinematics on a set of joints, defined by a start position- and rotation,
    /// joint angles and the lengths in between. Outputs the calculated positions and rotations.
    /// </summary>
    static bool ForwardKinematics(const Vect3D& startPosition, const Quat& startRotation,
                                  const std::vector<Vect3D>& jointLengths, const std::vector<Vect3D>& jointAngles,
                                  std::vector<Vect3D>& out_newPositions, std::vector<Quat>& out_newRotations);

    /// <summary> Calculate positions and rotations of a finger based on input angles and profile. </summary>
    static bool ForwardKinematics(
            const BasicHandModel& profile, EFinger finger, const std::vector<Vect3D>& jointAngles,
            std::vector<Vect3D>& out_newPositions, std::vector<Quat>& out_newRotations);

public:
    JointKinematics() = delete;
    virtual ~JointKinematics() = delete;
};
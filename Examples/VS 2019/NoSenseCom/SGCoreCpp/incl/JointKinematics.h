// ----------------------------------------------------------------------------------
// Contains kinematic formulae and wrappers for Sense Glove mathematics.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <vector>
#include "Vect3D.h"
#include "Quat.h"
#include "Fingers.h"

#include "BasicHandModel.h"

namespace SGCore
{
	namespace Kinematics
	{
		class SGCORE_API JointKinematics
		{
		public:

			/// <summary> 
			/// Perform foward Kinematics on a set of joints, defined by a start position- and rotation, 
			/// joint angles and the lenghts in between. Outputs the calculated positions and rotations.
			/// </summary>
			static bool ForwardKinematics(Vect3D startPosition, Quat startRotation,
				const std::vector<Vect3D>& jointLengths, const std::vector<Vect3D>& jointAngles,
				std::vector<Vect3D>& newPositions, std::vector<Quat>& newRotations);

			/// <summary> Calculate positions and rotations of a finger based on input angles and profile. </summary>
			static bool ForwardKinematics(BasicHandModel& profile, Finger finger, const std::vector<Vect3D>& jointAngles,
				std::vector<Vect3D>& newPositions, std::vector<Quat>& newRotations);
		};
	}
}
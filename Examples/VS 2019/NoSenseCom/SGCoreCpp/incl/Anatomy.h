// ----------------------------------------------------------------------------
// Hard-Coded Database that is used in calibration and hand solving.
// Values herein are used to limit user variables within 'natural' ranges.
// @author: Max Lammers
// ----------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <vector>

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> "Database" of anatomical values, such as joint limits. </summary>
		class SGCORE_API Anatomy
		{

		private:

			/// <summary> Index of minimum value </summary>
			const static int LIMIT_MIN;
			/// <summary> Index of maximum value </summary>
			const static int LIMIT_MAX;

			/// <summary> Hard Coded thumb limits, in radians </summary>
			const static std::vector <  std::vector < std::vector<float> > > thumbLimits;
			/// <summary> Hard Coded finger limits, in radians </summary>
			const static std::vector <  std::vector < std::vector<float> > > fingerLimits;

		public:

			/// <summary> Retrieve one of the limits of a finger joint's movement. </summary>
			static float GetFingerJointLimit(bool right, int joint, int movement, bool max);

			/// <summary> Retrieve one of the limits of a thumb joint's movement. </summary>
			static float GetThumbJointLimit(bool right, int joint, int movement, bool max);

		};

	}
}
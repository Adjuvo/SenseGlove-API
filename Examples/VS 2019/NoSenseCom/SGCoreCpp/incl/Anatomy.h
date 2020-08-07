// ----------------------------------------------------------------------------
// Hard-Coded Database that is used in calibration and in solving.
// Values herein are used to limit outputs within 'natural' ranges.
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

			/// <summary> Total sum of all finger flexion that would be considered "total flexion" </summary>
			const static float totalFingerFlexion;
			/// <summary> Total sum of all finger flexion that would be considered "total extension" </summary>
			const static float totalFingerExtension;

			/// <summary> Total sum of all thumb flexion that would be considered "total flexion" </summary>
			const static float totalThumbFlexion;
			/// <summary> Total sum of all thumb flexion that would be considered "total extension" </summary>
			const static float totalThumbExtension;


			/// <summary> Retrieve one of the limits of a finger joint's movement. </summary>
			static float GetFingerJointLimit(bool right, int joint, int movement, bool max);

			/// <summary> Retrieve one of the limits of a thumb joint's movement. </summary>
			static float GetThumbJointLimit(bool right, int joint, int movement, bool max);

		};

	}
}
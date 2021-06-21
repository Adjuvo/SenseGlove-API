// ----------------------------------------------------------------------------
// Hard-Coded Database that is used in calibration and in solving.
// Values herein are used to limit outputs within 'natural' ranges.
// @author: Max Lammers
// ----------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <vector>
#include "Vect3D.h"

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


            /// <summary> Convert a total finger flexion in radians into a 0..1 representation. </summary>
            /// <param name="flexionInRad"></param>
            /// <returns></returns>
            static float NormalizeFingerFlex(float flexionInRad);

            /// <summary> Convert a total finger flexion in radians into a 0..1 representation. </summary>
            /// <param name="flexionInRad"></param>
            /// <returns></returns>
            static float NormalizeThumbFlex(float flexionInRad);


            //-----------------------------------------------------------------------------------------------------------------------------------------
            // Hand Angles for Poses Etc

            /// <summary> Get Hand Angles that would make a Default (Idle) Pose </summary>
			static std::vector < std::vector < Vect3D > > HandAngles_Default(bool rightHand);

            /// <summary> Get Hand Angles that would make a flat hand </summary>
			static std::vector < std::vector < Vect3D > > HandAngles_Flat(bool rightHand);

            /// <summary> Get Hand Angles that would make a thumbs up </summary>
            static std::vector < std::vector < Vect3D > > HandAngles_ThumbsUp(bool rightHand);

            /// <summary> Get Hand Angles that would make a fist </summary>
            static std::vector < std::vector < Vect3D > > HandAngles_Fist(bool rightHand);
			
		};

	}
}
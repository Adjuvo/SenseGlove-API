// ----------------------------------------------------------------------------------
// Utility class to process and convert values in different formats.
// @author: Max Lammers
// ---------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "Vect3D.h"
#include "Quat.h"
#include <vector>

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> Utility class to convert values into various formats. </summary>
		class SGCORE_API Values
		{
		public:

			//--------------------------------------------------------------------------------------
			// Properties

			 /// <summary> Converts radians into degrees </summary>
			static const float Rad2Deg;

			/// <summary> Converts degrees into radians </summary>
			static const float Deg2Rad;

			/// <summary> 2*PI is used frequently in angle normalization </summary>
			static const float _2PI;


			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Convert a vector of degrees angles into radians. </summary>
			static Vect3D Radians(Vect3D degrees);

			/// <summary> Convert a vector of radian angles into degrees. </summary>
			static Vect3D Degrees(Vect3D radians);


			/// <summary> Ensure that a single angle is within the [-Pi...Pi] range. </summary>
			static float NormalizeAngle(float angle, float minAngle, float maxAngle);

			/// <summary> Normalize and angle between a variable range. </summary>
			static float NormalizeAngle(float angle);

			/// <summary> Normalize a set of angles in radians. </summary>
			static Vect3D NormalizeAngles(Vect3D angles);


			/// <summary> Ensure that a value remains within the [min...max] range. </summary>
			static float Clamp(float value, float min, float max);

			/// <summary> Ensure that an integer value remains within the [min...max] range. </summary>
			static int Clamp(int value, int min, int max);


			/// <summary> Map a value from one range [from1...from2] to another range [to1 .. to2] </summary>
			static float Map(float value, float from1, float from2, float to1, float to2);

			/// <summary> Map a value from one range [from1...from2] to another range [to1 .. to2],
			/// while ensuring it stays within the [min...max] range. </summary>
			static float Map(float value, float from1, float from2, float to1, float to2, float min, float max);

			/// <summary> Check if two floating points are roughly equal, taking into account the minor differences. </summary>
			static bool FloatEquals(float value1, float value2);


			///<summary> Check if two arrays contain equal values. </summary>
			static bool Equal(std::vector<Vect3D>& array1, std::vector<Vect3D>& array2);

			///<summary> Check if two arrays contain equal values. </summary>
			static bool Equal(std::vector<std::vector<Vect3D>>& array1, std::vector<std::vector<Vect3D>>& array2);

			///<summary> Check if two arrays contain equal values. </summary>
			static bool Equal(std::vector<Quat>& array1, std::vector<Quat>& array2);

			///<summary> Check if two arrays contain equal values. </summary>
			static bool Equal(std::vector<std::vector<Quat>>& array1, std::vector<std::vector<Quat>>& array2);

		};
	}
}
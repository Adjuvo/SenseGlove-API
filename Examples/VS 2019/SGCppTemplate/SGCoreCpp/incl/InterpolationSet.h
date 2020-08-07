// ----------------------------------------------------------------------------------
// Data class containing all variables to map an input value from one range to another.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> Set of variables to map a value from one range to the next. </summary>
		class SGCORE_API InterpolationSet
		{

		public:

			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> First value of input range.</summary>
			float x0;
			/// <summary> Second value of input range. </summary>
			float x1;

			/// <summary> First value of output range. </summary>
			float y0;
			/// <summary> Second value of output range. </summary>
			float y1;

			/// <summary> Minumum range of the output value. </summary>
			float min;
			/// <summary> Maximum range of the output value. </summary>
			float max;


			//--------------------------------------------------------------------------------------
			// Construction

			/// <summary> Creates a basic interpolation set, without limits. </summary>
			InterpolationSet();

			/// <summary> Create a new interpolation set without limits. </summary>
			InterpolationSet(float from1, float from2, float to1, float to2);

			/// <summary> Create a new interpolation set with limits. </summary>
			InterpolationSet(float from1, float from2, float to1, float to2, float min, float max);

			/// <summary> Basic Destructor. </summary>
			~InterpolationSet();


			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Calculate an output value in range [x0...x1] to [y0..y1] </summary>
			float Get(float value, bool limit, bool normalizeAngle = false);


            /// <summary> Returns true if this InterpolationSet has the same values as another set. </summary>
            /// <param name="other"></param>
            /// <returns></returns>
            bool Equals(InterpolationSet other);



            //--------------------------------------------------------------------------------------
            // Serialization

			/// <summary> Convert this InterpolationSet into a string notation so it can be stored on disk. </summary>
			/// <returns></returns>
			std::string Serialize();

			/// <summary> Convert a string notation of an InterpolationSet into a new class instance. </summary>
			/// <param name="serializedString"></param>
			/// <returns></returns>
			static InterpolationSet Deserialize(std::string serializedString);



		};

	}
}
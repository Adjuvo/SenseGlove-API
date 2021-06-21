#pragma once

#include "SGCore.h"
#include "Vect3D.h"
#include <vector>


namespace SGCore
{
	namespace Calibration
	{
		class SGCORE_API SensorRange
		{
		private:
			//--------------------------------------------------------------------------------------------------------------------------
			// Member Variables

			/// <summary> The minimum sensor values of this sensor range </summary>
			std::vector<Kinematics::Vect3D> minVals;
			/// <summary> The maximum sensor values of this sensor range </summary>
			std::vector<Kinematics::Vect3D> maxVals;
			/// <summary> The difference between min and max values in this Sensor Range. </summary>
			std::vector<Kinematics::Vect3D> range;

		public:

			//--------------------------------------------------------------------------------------------------------------------------
			// Construction

			/// <summary> Create a new instance of a SensorRange with values at 0, 0 </summary>
			SensorRange();

			/// <summary> Create a new SensorRange with predefined Min/Max values. </summary>
			/// <param name="min"></param>
			/// <param name="max"></param>
			SensorRange(std::vector<Kinematics::Vect3D> min, std::vector<Kinematics::Vect3D> max);


			/// <summary> Generates a Sensor Range where minumum values are float.MaxValue and maximum values are float.MinValue. </summary>
			/// <returns></returns>
			static SensorRange ForCalibration();

			//--------------------------------------------------------------------------------------------------------------------------
			// Accessors

			/// <summary> Access the lowest values values of this range. </summary>
			std::vector<Kinematics::Vect3D> GetMinValues();
			/// <summary> Access the lowest values values of this range. </summary>
			void SetMinValues(std::vector<Kinematics::Vect3D> value);

			/// <summary> Access the lowest values values of this range. </summary>
			std::vector<Kinematics::Vect3D> GetMaxValues();
			/// <summary> Access the lowest values values of this range. </summary>
			void SetMaxValues(std::vector<Kinematics::Vect3D> value);

			/// <summary> Access the difference between min and max values. </summary>
			std::vector<Kinematics::Vect3D> GetRange();

			//--------------------------------------------------------------------------------------------------------------------------
			// Functions

			/// <summary> Update the Range based on the current minVals and MaxVals. </summary>
			void UpdateRange();

			/// <summary> In otherValues are greater/smaller than this current range, update them </summary>
			/// <param name="otherValues"></param>
			void CheckForExtremes(std::vector<Kinematics::Vect3D>& otherValues);

			/// <summary> Convert this SensorRange into a string rotation [min ... max] </summary>
			/// <param name="yOnly"></param>
			/// <returns></returns>
			std::string ToString(bool yOnly = true);

			/// <summary> Report the Range value of this SensorRange, separated by a comma </summary>
			/// <param name="yOnly"></param>
			/// <returns></returns>
			std::string RangeString(bool yOnly = true);


			/// <summary> Evaluate maxVals so that it contains the highest x, y, and z values between currVals and maxVals. </summary>
			/// <param name="currVals"></param>
			/// <param name="maxVals"></param>
			static void CheckMax(Kinematics::Vect3D& currVals, Kinematics::Vect3D& maxVals);

			/// <summary> Evaluate minVals so that it contains the lowest x, y, and z values between currVals and minVals. </summary>
			/// <param name="currVals"></param>
			/// <param name="minVals"></param>
			static void CheckMin(Kinematics::Vect3D& currVals, Kinematics::Vect3D& minVals);


			//--------------------------------------------------------------------------------------------------------------------------
			// Serialization / Deserialization

			/// <summary> Serialize this SensorRange into a string representation, that can be deserialized later. </summary>
			/// <returns></returns>
			std::string Serialize();

			/// <summary> Convert a serialized SensorRange back into the appropriate class. </summary>
			/// <param name="serializedString"></param>
			/// <returns></returns>
			static SensorRange Deserialize(std::string& serializedString);


		};
	}
}
// ----------------------------------------------------------------------------------
// Parsed sensor data coming form a Sense Glove.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>
#include <vector>
#include "Quat.h"
#include "Fingers.h"

namespace SGCore
{
	namespace SG
	{
		/// <summary> Sense Glove Sensor Data, parsed from a sensor string. </summary>
		struct SGCORE_API SG_SensorData
		{

		protected:

			//--------------------------------------------------------------------------------
			// Properties

			/// <summary> The total amount of sensor values that were parsed in the string (used to check for validity / sensor placement). </summary>
			int parsedValues;

			/// <summary> If true, all data has been properly received. </summary>
			bool dataComplete;


		public:

			/// <summary> Glove angles in radians, sorted by finger, from proximal to distal </summary>
			std::vector< std::vector<float> > sensorAngles;

			/// <summary> Quaternion rotation of the IMU within the Sense Glove. </summary>
			Kinematics::Quat imuValues;

			//--------------------------------------------------------------------------------
			// Construction

			/// <summary> Basic Constructor. </summary>
			SG_SensorData();

			/// <summary> Create a new instance of a Sense Glove Sensor Data class. </summary>
			SG_SensorData(std::vector<std::vector<float>>angles, Kinematics::Quat imu, int sNumber, bool complete = false);

			/// <summary> Basic Destructor. </summary>
			~SG_SensorData() { }


			///<summary> Returns sensor data with no values. </summary>
			static SG_SensorData Empty();


			//--------------------------------------------------------------------------------
			// Accessors

			///<summary> Get the glove angles of a specific finger segment </summary>
			std::vector<float> GetAngles(Finger finger);

			///<summary> Returns all glove angles in a sequence, without splitting them per finger. </summary>
			std::vector<float> GetAngleSequence();

			///<summary> Check how many values have been parsed from the Sensor String. </summary>
			int ParsedValues() { return parsedValues; }

			///<summary> True if all expected values have been received. </summary>
			bool IsComplete() { return dataComplete; }


			//--------------------------------------------------------------------------------
			// Class Methods

			///<summary> Retrieve a simple representaton of this sensor data for debugging purposes. </summary>
			std::string ToString();


			//--------------------------------------------------------------------------------
			// Serialization

			///<summary> Deserialize Sense Glove sensor data from a raw char[] recieved through IPC. </summary>
			static SG_SensorData Parse(std::string rawData, float fwVer, Kinematics::Quat imuCorr = Kinematics::Quat::identity);

		};
	}
}
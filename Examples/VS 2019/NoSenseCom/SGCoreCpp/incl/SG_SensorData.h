// ----------------------------------------------------------------------------------
// Parsed sensor data coming form a Sense Glove.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "SG_GloveInfo.h"

#include <string>
#include <vector>
#include "Quat.h"
#include "Fingers.h"


namespace SGCore
{
	namespace SG
	{
		/// <summary> Sense Glove Sensor Data, parsed from a sensor string. </summary>
		class SGCORE_API SG_SensorData
		{

		protected:

			//--------------------------------------------------------------------------------
			// Properties

			/// <summary> The total amount of sensor values that were parsed in the string (used to check for validity / sensor placement). </summary>
			int parsedValues;

			/// <summary> Whether or not the IMU was properly parsed. </summary>
			bool imuParsed;


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
			SG_SensorData(std::vector<std::vector<float>>angles, Kinematics::Quat imu, int sNumber, bool imuComplete);

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

			///<summary> Check if the IMU was properly parsed. </summary>
			bool IMUParsed() { return imuParsed; }

			//--------------------------------------------------------------------------------
			// Class Methods

			///<summary> Retrieve a simple representaton of this sensor data for debugging purposes. </summary>
			std::string ToString();

			///<summary> Returns true if the values of both data are equal </summary>
			bool Equals(SG_SensorData other);

			//---------------------------------------------------------------------------------------------------------------------
			// Serialization

			///<summary> Serialize this HandProfile into a string representation </summary>
			std::string Serialize();

			///<summary> Deserialize a HandProfile back into useable values. </summary>
			static SG_SensorData Deserialize(std::string serializedString);

			///<summary> Deserialize Sense Glove sensor data from a raw char[] recieved through IPC. </summary>
			static SG_SensorData Parse(std::string rawData, SG_GloveInfo& gloveInfo);

		};
	}
}
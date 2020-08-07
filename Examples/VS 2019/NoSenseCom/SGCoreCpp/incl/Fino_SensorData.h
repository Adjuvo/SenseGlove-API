// ----------------------------------------------------------------------------------
// Fino SensorData, parsed from rae string representations
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include <vector>
#include "Quat.h"
#include "Vect3D.h"
#include "Fino_GloveInfo.h"

namespace SGCore
{
    namespace Fino
    {
        /// <summary> Sensor Data coming from a Fino, converted into useful values. </summary>
        class SGCORE_API Fino_SensorData
        {

        protected:

            /// <summary> Set to true if the IMU has been properly parsed. </summary>
            bool imuParsed;

        public:

            //--------------------------------------------------------------------------------------
            // Properties

            /// <summary> Pronation/Supination, Flexion/Extension and Abduction/Adduction values for each finger. </summary>
            std::vector<Kinematics::Vect3D> sensorValues;

            /// <summary> Quaternion rotation relative to magnetic north. </summary>
            Kinematics::Quat IMURotation;

            /// <summary> The number of values that were parsed from the sensor string. </summary>
            int parsedValues;

            //--------------------------------------------------------------------------------------
            // Construction

            /// <summary> Default constructor for Fino_SensorData </summary>
            /// <returns></returns>
            Fino_SensorData();

            /// <summary> Create a new instance of a Fino_SensorData</summary>
            /// <param name="values"></param>
            /// <param name="numberOfVals"></param>
            /// <param name="imuRot"></param>
            /// <returns></returns>
            Fino_SensorData(std::vector<Kinematics::Vect3D> values, int numberOfVals, Kinematics::Quat imuRot, bool imuComplete);

            /// <summary> Returns a Fino_SensorData without any values. </summary>
            /// <returns></returns>
            static Fino_SensorData Empty();

            //--------------------------------------------------------------------------------------
            // Class Methods

            /// <summary> Create a readable string representation of this Sensor Data </summary>
            /// <returns></returns>
            std::string ToString();

            /// <summary> Returns true if this sensor data contains the same values as another. </summary>
            /// <param name="other"></param>
            /// <returns></returns>
            bool Equals(Fino_SensorData other);

            /// <summary> Returns true if the IMU was properly parsed. </summary>
            /// <returns></returns>
            bool IMUParsed() { return imuParsed; }

            //--------------------------------------------------------------------------------------
            // Serialization

            /// <summary> Parse the bytes as they come in from the device into useable values. </summary>
            /// <param name="rawData"></param>
            /// <param name="gloveInfo"></param>
            /// <returns></returns>
            static Fino_SensorData Parse(std::string rawData, Fino_GloveInfo gloveInfo);

            /// <summary> Convert this sensor data into a string so it can be stored on disk. </summary>
            /// <returns></returns>
            std::string Serialize();

            /// <summary> Convert this sensor data into ta string representation.  </summary>
            /// <param name="serializedString"></param>
            /// <returns></returns>
            static Fino_SensorData Deserialize(std::string serializedString);

        };

    }
}


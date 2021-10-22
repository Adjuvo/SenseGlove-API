// ----------------------------------------------------------------------------------
// Nova SensorData, parsed from rae string representations
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include <vector>
#include "Quat.h"
#include "Vect3D.h"
#include "Nova_GloveInfo.h"

namespace SGCore
{
    namespace Nova
    {

        /// <summary> Enumerators for Nova Data position in the parseable string. </summary>
        enum NovaData
        {
            Sensors,
            IMU,
            Battery,
            All
        };


        /// <summary> Sensor Data coming from a Nova, converted into useful values. </summary>
        class SGCORE_API Nova_SensorData
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

            /// <summary> Whether or not the IMU values were all succesfully parsed. </summary>
            bool IMUParsed;

            /// <summary> Returns true if this NovaGlove is connected to a power source </summary>
            float batteryLevel;

            /// <summary> A value between 0..1 that represents the battery level of this Nova Glove (0 .. 100%). Returns -1 if the value wasn't received. </summary>
            bool isCharging;

            //--------------------------------------------------------------------------------------
            // Construction

            /// <summary> Default constructor for Nova_SensorData </summary>
            /// <returns></returns>
            Nova_SensorData();

            /// <summary> Create a new instance of a Nova_SensorData</summary>
            /// <param name="values"></param>
            /// <param name="numberOfVals"></param>
            /// <param name="imuRot"></param>
            /// <param name="battLvl"></param>
            /// <param name="charging"></param>
            /// <returns></returns>
            Nova_SensorData(std::vector<Kinematics::Vect3D> values, int numberOfVals, Kinematics::Quat imuRot, bool imuComplete, float battLvl, bool charging);

            /// <summary> Returns a Nova_SensorData without any values. </summary>
            /// <returns></returns>
            static Nova_SensorData Empty();

            //--------------------------------------------------------------------------------------
            // Class Methods

            /// <summary> Create a readable string representation of this Sensor Data </summary>
            /// <returns></returns>
            std::string ToString();

            /// <summary> Returns true if this sensor data contains the same values as another. </summary>
            /// <param name="other"></param>
            /// <returns></returns>
            bool Equals(Nova_SensorData& other);


            //--------------------------------------------------------------------------------------
            // Serialization

            /// <summary> Parse the bytes as they come in from the device into useable values. </summary>
            /// <param name="rawData"></param>
            /// <param name="gloveInfo"></param>
            /// <returns></returns>
            static Nova_SensorData Parse(std::string& rawData, SGCore::Nova::Nova_GloveInfo& gloveInfo);

            /// <summary> Convert this sensor data into a string so it can be stored on disk. </summary>
            /// <returns></returns>
            std::string Serialize();

            /// <summary> Convert this sensor data into ta string representation.  </summary>
            /// <param name="serializedString"></param>
            /// <returns></returns>
            static Nova_SensorData Deserialize(std::string serializedString);

        };

    }
}


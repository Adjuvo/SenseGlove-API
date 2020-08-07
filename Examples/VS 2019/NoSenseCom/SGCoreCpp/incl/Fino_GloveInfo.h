// ----------------------------------------------------------------------------------
// Contains information on Fino's hardware, extracted from the device.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include "Quat.h"

namespace SGCore
{
    namespace Fino
    {
        /// <summary> Device information extracted from a Fino glove. </summary>
        class SGCORE_API Fino_GloveInfo
        {

        public:

            //--------------------------------------------------------------------------------------
            // Properties

            /// <summary> Unique identifier of this device. </summary>
            std::string deviceID;

            /// <summary> Hardware (sub) version of this Sense Glove Device. </summary>
            std::string hardwareVer;

            /// <summary> Firmware version running on the device's MicroController. (as v4.12, this is the 4) </summary>
            int firmwareVer;

            /// <summary> Sub firmware version runnning on the device's microcontroller (as v4.12, this is the .12) </summary>
            int subFirmwareVer;

            /// <summary> Determines if this is a right-handed Fino. </summary>
            bool isRight;

            ///<summary> The IMU correction of this Fino. </summary>
            Kinematics::Quat imuCorrection;

            ///<summary> The number of sensors in this device. </summary>
            int numberOfSensors;

            //--------------------------------------------------------------------------------------
            // Constructor

            /// <summary> Default Constructor </summary>
            /// <returns></returns>
            Fino_GloveInfo();

            /// <summary> Create a new instance of a Fino_GloveInfo </summary>
            /// <param name="ID"></param>
            /// <param name="hwVer"></param>
            /// <param name="fwMain"></param>
            /// <param name="fwSub"></param>
            /// <param name="rightHand"></param>
            /// <param name="imuCorr"></param>
            /// <param name="nSensors"></param>
            /// <returns></returns>
            Fino_GloveInfo(std::string ID, std::string hwVer, int fwMain, int fwSub, bool rightHand,
                Kinematics::Quat imuCorr, int nSensors);

            //--------------------------------------------------------------------------------------
            // Class Methods

            /// <summary> Create a string representation of this Glove Info </summary>
            /// <returns></returns>
            std::string ToString();

            /// <summary> Returns true if this GloveInfo contains the same information as another. </summary>
            /// <param name="other"></param>
            /// <returns></returns>
            bool Equals(Fino_GloveInfo other);


            //--------------------------------------------------------------------------------------
            // Serialization

            /// <summary> Parse an constants string into a Fino_GloveInfo class. </summary>
            /// <param name="cString"></param>
            /// <param name="model"></param>
            /// <returns></returns>
            static bool Parse(std::string cString, Fino_GloveInfo& model);


            /// <summary> Convert this class into a string representation so it can be unpacked later </summary>
            /// <returns></returns>
            std::string Serialize();

            /// <summary> Convert a string representation back into a Fino_GloveInfo class. </summary>
            /// <param name="serializedString"></param>
            /// <returns></returns>
            static Fino_GloveInfo Deserialize(std::string serializedString);


        };

    }
}
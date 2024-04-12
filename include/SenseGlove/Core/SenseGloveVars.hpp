/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Contains enumerators and classes to aid in Sense Glove Deserialization.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Kinematics
    {
        class Quat;

        class Vect3D;
    }// namespace Kinematics

    namespace Parsing
    {
        /// <summary> Sense Glove C string Variables, enumerated for our convenience. </summary>
        enum class ESenseGloveCVar : uint8_t
        {
            ConstOpen = 0,
            Id,
            GloveVersion,
            FirmwareVersion,
            LeftRight,
            Functions,
            GlovePosition,
            GloveLengths,// all gloves have functionality up to this point.
            NumberOfSensors,
            ImuCorrection,

            /// <summary> Utility value used in iteration / checking lengths. </summary>
            AllC,
        };

        /// <summary> Sense Glove sensor string Variables, enumerated for our convenience. </summary>
        enum class ESenseGloveSVar : uint8_t
        {
            RealtimeError = 0,// real-time error
            FingerSensors,
            ImuData,
            WatchdogError, // watchdog-error
            SemaphoreError,// semaphore-error

            /// <summary> Utility value used in iteration / checking lengths. </summary>
            AllS,
        };
    }// namespace Parsing

    namespace SG
    {
        /// <summary> "Database" class containing Sense Glove internal variables. </summary>
        class SGCORE_API SenseGloveVars;

        class SenseGloveInfo;
    }// namespace SG
}// namespace SGCore

/// <summary> "Database" class containing Sense Glove internal variables. </summary>
class SGCORE_API SGCore::SG::SenseGloveVars
{
public:
    /// <summary> Retrieve a basic ConstantsString for a Sense Glove of a specific Hardware Version. Used for debugging
    /// / unit tests. </summary>
    /// <returns> Returns an empty string when an invalid glove version is requested. </returns>
    static std::string GetStandardConstantsString(const std::string& hardwareVersion,
                                                  float firmwareVersion, bool bRightHanded);

    /// <summary> Retrieve an example sensor string of a Sense Glove with a particular hardware- and firmware version.
    /// </summary>
    static std::string GetSensorString(const std::string& hardwareVersion, float firmwareVersion);

    /// <summary> Retrieve the starting positions of a particular Sense Glove. </summary>
    static std::vector<Kinematics::Vect3D> GetStartPositions(const std::string& hardwareVersion, bool bRightHanded);

    /// <summary> Retrieve the starting rotations of a particular Sense Glove. </summary>
    static std::vector<Kinematics::Quat> GetStartRotations(const std::string& hardwareVersion, bool bRightHanded);

    /// <summary> Retrieve the glove finger lengths of a particular Sense Glove. </summary>
    static std::vector<std::vector<Kinematics::Vect3D>> GetGloveLengths(const std::string& hardwareVersion);

    /// <summary> Get the number of sensors of a SenseGlove. </summary>
    /// <param name="hardwareVersion"></param>
    /// <returns></returns>
    static int32_t GetSensors(const std::string& hardwareVersion);

    /// <summary> Get the default IMUCorrection for the SenseGlove. </summary>
    /// <param name="hardwareVersion"></param>
    /// <param name="firmwareVersion"></param>
    /// <param name="subFirmwareVersion"></param>
    /// <returns></returns>
    static Kinematics::Quat GetImuCorrection(const std::string& hardwareVersion,
                                             int32_t firmwareVersion, int32_t subFirmwareVersion);

    /// <summary> Check all functionality of a SenseGlove. </summary>
    /// <param name="hardwareVersion"></param>
    /// <param name="firmwareVersion"></param>
    /// <param name="subFirmwareVersion"></param>
    /// <returns></returns>
    static std::vector<bool> GetFunctions(const std::string& hardwareVersion,
                                          int32_t firmwareVersion, int32_t subFirmwareVersion);

    /// <summary> Generate a custom glove info. </summary>
    /// <param name="hardwareVersion"></param>
    /// <param name="firmwareVersion"></param>
    /// <param name="subFirmwareVersion"></param>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static SenseGloveInfo GenerateGloveModel(const std::string& hardwareVersion,
                                             int32_t firmwareVersion, int32_t subFirmwareVersion, bool bRightHanded);

    /// <summary> Generate a custom glove info. </summary>
    /// <param name="hardwareVersion"></param>
    /// <param name="firmwareVersion"></param>
    /// <param name="subFirmwareVersion"></param>
    /// <param name="bRightHanded"></param>
    /// <param name="customId"></param>
    /// <returns></returns>
    static SenseGloveInfo GenerateGloveModel(const std::string& hardwareVersion,
                                             int32_t firmwareVersion, int32_t subFirmwareVersion,
                                             bool bRightHanded, const std::string& customId);

public:
    SenseGloveVars() = delete;
    virtual ~SenseGloveVars() = delete;
};
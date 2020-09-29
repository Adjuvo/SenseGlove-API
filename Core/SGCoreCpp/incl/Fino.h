// ----------------------------------------------------------------------------------
// An interface for the "Fino" - a soft glove.
// Contains methods for Kinematics, Haptics and Serialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "HapticGlove.h"
#include "Fino_GloveInfo.h"
#include "Fino_Profile.h"
#include "Fino_SensorData.h"


namespace SGCore
{
	namespace Fino
	{
		/// <summary> A soft glove with Force- and Vibrotactile Feedback and limited tracking. </summary>
		class SGCORE_API Fino : public HapticGlove
		{
		protected:

            //---------------------------------------------------------------------------------------------------------------------
            // Properties

			/// <summary> Byte indicating a new Fino haptic command. </summary>
			const static char hapticsByte;

			/// <summary> Device information about this fino (L/R, FWversion, etc). </summary>
			Fino_GloveInfo gloveInfo;

            /// <summary> Converts a thumper command into bytes that the Fino can understand. </summary>
            static std::string ToBytes(Haptics::ThumperCmd thumper);

            /// <summary> Converts a force-feedback command into bytes that the Fino can understand. </summary>
            static std::string ToBytes(Haptics::SG_FFBCmd cmd);

            /// <summary> Converts a buzz-motor command into bytes that the Fino can understand. </summary>
            static std::string ToBytes(Haptics::SG_BuzzCmd cmd);

            /// <summary> Minumum calibration value distance until we apply the range. </summary>
            static Kinematics::Vect3D minCalRange;

		public:

            //---------------------------------------------------------------------------------------------------------------------
            // Construction

            /// <summary> Default Constructor </summary>
            /// <returns></returns>
            Fino();

            /// <summary> Creates a new instance of a Fino Glove. </summary>
            /// <param name="deviceInfo"></param>
            /// <returns></returns>
            Fino(Fino_GloveInfo deviceInfo);


            //---------------------------------------------------------------------------------------------------------------------
            // Class Methods

            /// <summary> Access all softs of device info specific to this Fino. </summary>
            /// <returns></returns>
            Fino_GloveInfo GetGloveModel();

            /// <summary> Create a string representation of this device for reporting purposes. </summary>
            std::string ToString() override { return "Fino " + GetDeviceID(); };


            /// <summary> Returns true if this glove is meant for right hands. </summary>
            /// <returns></returns>
            bool IsRight() override;

			/// <summary> Returns this device's unique identifier. </summary>
			/// <returns></returns>
			std::string GetDeviceID() override { return gloveInfo.deviceID; }

			/// <summary> Access this device's main firmare version. (ex: v3.2 -> 3) </summary>
			/// <returns></returns>
			int GetFirmwareVersion() override  { return gloveInfo.firmwareVer; }

			/// <summary> Access this device's sub-firmare version. (ex: v3.2 -> 2) </summary>
			/// <returns></returns>
			int GetSubFirmwareVersion() override { return gloveInfo.subFirmwareVer; }

			/// <summary> Access this device's hardware designation. </summary>
			/// <returns></returns>
			std::string GetHardwareVersion() override { return gloveInfo.hardwareVer; }

			/// <summary> Return the DeviceType of this Fino. </summary>
			/// <returns></returns>
			DeviceType GetDeviceType() override { return DeviceType::FINO; }


            //---------------------------------------------------------------------------------------------------------------------
            // Device Data

            /// <summary> Get the latest Sensor Data from this Sense Glove. </summary>
            /// <returns></returns>
            bool GetSensorData(Fino_SensorData& sensorData);


            /// <summary> Retrieve Fino rotation </summary>
            /// <param name="IMU"></param>
            /// <returns></returns>
            bool GetIMURotation(Kinematics::Quat& IMU) override;


            /// <summary> Retrieve a new hand pose using this glove, based on (calibrated) user data. </summary>
            /// <param name="profile"></param>
            /// <param name="solver"></param>
            /// <param name="handPose"></param>
            /// <returns></returns>
            bool GetHandPose(Kinematics::BasicHandModel& handModel, Fino_Profile& profile, HandPose& handPose);


            /// <summary> Retrieve a new hand pose using this glove, based on (calibrated) user data. </summary>
            /// <param name="handGeometry"></param>
            /// <param name="handProfile"></param>
            /// <param name="handPose"></param>
            /// <returns></returns>
            bool GetHandPose(Kinematics::BasicHandModel& handGeometry, HandProfile& handProfile, HandPose& handPose) override;
            

            /// <summary> Calculate the HandPose of this Device, taking into account user values, but not hand geometry. </summary>
            bool GetHandPose(HandProfile& handProfile, HandPose& handPose) override;


            /// <summary> Calculate a Hand Pose based on a HandMode; sensor data from a fino, and a UserProfile. </summary>
            /// <param name="handModel"></param>
            /// <param name="finoData"></param>
            /// <param name="profile"></param>
            /// <returns></returns>
            static HandPose CalculateHandPose(Kinematics::BasicHandModel& handModel, Fino_SensorData& finoData, Fino_Profile& profile);


            //--------------------------------------------------------------------------------------
            // Haptics

            /// <summary> Send all available haptics to a Fino. </summary>
            /// <param name="ffb"></param>
            /// <param name="buzz"></param>
            /// <param name="thumper"></param>
            void SendHaptics(Haptics::SG_FFBCmd ffb, Haptics::SG_BuzzCmd buzz, Haptics::ThumperCmd thumper) override;


            /// <summary> Send Haptic Commands to this Glove. </summary>
            void SendHaptics(Haptics::SG_FFBCmd ffb) override
            {
                SendHaptics(ffb, lastBuzzCmd, lastThumper);
            }

            /// <summary> Send Haptic Commands to this Glove. </summary>
            void SendHaptics(Haptics::SG_BuzzCmd buzz) override
            {
                SendHaptics(lastFFBCmd, buzz, lastThumper);
            }

            /// <summary> Send Haptic Commands to this Glove. </summary>
            void SendHaptics(Haptics::ThumperCmd thumper) override
            {
                SendHaptics(lastFFBCmd, lastBuzzCmd, thumper);
            }

            //--------------------------------------------------------------------------------------
            // Devicelist Integration

            ///<summary> Deserializes a Fino from its CString. Returns a nullptr if unsuccesful. </summary>
            /// <param name="cString"></param>
            /// <returns></returns>
            static std::shared_ptr<SGDevice> Parse(std::string cString);


            /// <summary> Retrieve all Fino's. </summary>
            static std::vector<Fino> GetFinos();

            /// <summary> Retrieve the first connected Fino there is. </summary>
            static bool GetFino(Fino& glove);

            /// <summary> Retrieve the first (connected) right- or left handed fino. </summary>
            static bool GetFino(bool rightHanded, Fino& glove);



            //--------------------------------------------------------------------------------------
            // Calibration Methods


            /// <summary>  Retrieve calibration values of this glove, as an array of size 5, containing x (roll), y (flexion), z (abduction) values. </summary>
            /// <param name="values"></param>
            /// <returns></returns>
            bool GetCalibrationValues(std::vector<SGCore::Kinematics::Vect3D>& values) override;

            /// <summary> Convert a SenseGlove GlovePose into calibrationValues. </summary>
            /// <param name="sData"></param>
            /// <returns></returns>
            static std::vector<Kinematics::Vect3D> GetCalibrationValues(Fino_SensorData sData);
            

            /// <summary> Applies the calibration range of this Fino a HandProfile </summary>
            /// <param name="profile"></param>
            void ApplyCalibration(HandProfile& profile) override;
            

            /// <summary> Applies the calibration range of this SenseGlove to a Fino_Profile </summary>
            /// <param name="profile"></param>
            void ApplyCalibration(Fino_Profile& profile);

		};
	}
}


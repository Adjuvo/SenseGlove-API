// ----------------------------------------------------------------------------------
// An interface for the "Nova" - a soft glove.
// Contains methods for Kinematics, Haptics and Serialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "HapticGlove.h"
#include "Nova_GloveInfo.h"
#include "Nova_Profile.h"
#include "Nova_SensorData.h"
#include "Nova_Calibration.h"

namespace SGCore
{
	namespace Nova
	{
		/// <summary> A soft glove with Force- and Vibrotactile Feedback and limited tracking. </summary>
		class SGCORE_API NovaGlove : public HapticGlove
		{
		protected:

            //---------------------------------------------------------------------------------------------------------------------
            // Properties

			/// <summary> Byte indicating a new Nova haptic command. </summary>
			const static char hapticsByte;

			/// <summary> Device information about this Nova (L/R, FWversion, etc). </summary>
			Nova_GloveInfo gloveInfo;

            /// <summary> Converts a thumper command into bytes that the Nova can understand. </summary>
            static std::string ToBytes(Haptics::ThumperCmd thumper);

            /// <summary> Converts a force-feedback command into bytes that the Nova can understand. </summary>
            static std::string ToBytes(Haptics::SG_FFBCmd cmd);

            /// <summary> Converts a buzz-motor command into bytes that the Nova can understand. </summary>
            static std::string ToBytes(Haptics::SG_BuzzCmd cmd);

            /// <summary> Minumum calibration value distance until we apply the range. </summary>
            static Kinematics::Vect3D minCalRange;

		public:

            //---------------------------------------------------------------------------------------------------------------------
            // Construction

            /// <summary> Default Constructor </summary>
            /// <returns></returns>
            NovaGlove();

            /// <summary> Creates a new instance of a Nova Glove. </summary>
            /// <param name="deviceInfo"></param>
            /// <returns></returns>
            NovaGlove(Nova_GloveInfo deviceInfo);


            //---------------------------------------------------------------------------------------------------------------------
            // Class Methods

            /// <summary> Access all softs of device info specific to this Nova. </summary>
            /// <returns></returns>
            Nova_GloveInfo GetGloveModel();

            /// <summary> Create a string representation of this device for reporting purposes. </summary>
            std::string ToString() override { return "Nova " + GetDeviceID(); };


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

			/// <summary> Return the DeviceType of this Nova. </summary>
			/// <returns></returns>
			DeviceType GetDeviceType() override { return DeviceType::NOVA; }

            /// <summary> Returns true if this device operates on a battery </summary>
            /// <returns></returns>
            bool HasBattery() override;

            /// <summary> Returns true if this device is currently charging </summary>
            /// <returns></returns>
            bool IsCharging() override;

            /// <summary> Returns the device's battery level, as a value between 0 (empty) and 1 (full). </summary>
            /// <param name="battLvl"></param>
            /// <returns></returns>
            bool GetBatteryLevel(float& battLvl) override;


            //---------------------------------------------------------------------------------------------------------------------
            // Device Data

            /// <summary> Get the latest Sensor Data from this Sense Glove. </summary>
            /// <returns></returns>
            bool GetSensorData(Nova_SensorData& sensorData);


            /// <summary> Retrieve Nova rotation </summary>
            /// <param name="IMU"></param>
            /// <returns></returns>
            bool GetIMURotation(Kinematics::Quat& IMU) override;


            /// <summary> Retrieve a new hand pose using this glove, based on (calibrated) user data. </summary>
            /// <param name="profile"></param>
            /// <param name="solver"></param>
            /// <param name="handPose"></param>
            /// <returns></returns>
            bool GetHandPose(Kinematics::BasicHandModel& handModel, Nova_Profile& profile, HandPose& handPose);


            /// <summary> Retrieve a new hand pose using this glove, based on (calibrated) user data. </summary>
            /// <param name="handGeometry"></param>
            /// <param name="handProfile"></param>
            /// <param name="handPose"></param>
            /// <returns></returns>
            bool GetHandPose(Kinematics::BasicHandModel& handGeometry, HandProfile& handProfile, HandPose& handPose) override;
            

            /// <summary> Calculate the HandPose of this Device, taking into account user values, but not hand geometry. </summary>
            bool GetHandPose(HandProfile& handProfile, HandPose& handPose) override;


            /// <summary> Calculate a Hand Pose based on a HandMode; sensor data from a Nova, and a UserProfile. </summary>
            /// <param name="handModel"></param>
            /// <param name="NovaData"></param>
            /// <param name="profile"></param>
            /// <returns></returns>
            static HandPose CalculateHandPose(Kinematics::BasicHandModel& handModel, Nova_SensorData& novaData, Nova_Profile& profile);


            //--------------------------------------------------------------------------------------
            // Haptics

            /// <summary> Send all available haptics to a Nova. </summary>
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

            ///<summary> Deserializes a Nova from its CString. Returns a nullptr if unsuccesful. </summary>
            /// <param name="cString"></param>
            /// <returns></returns>
            static std::shared_ptr<SGDevice> Parse(std::string cString);


            /// <summary> Retrieve all Nova's. </summary>
            static std::vector<NovaGlove> GetNovaGloves();

            /// <summary> Retrieve the first connected Nova there is. </summary>
            static bool GetNovaGlove(NovaGlove& glove);

            /// <summary> Retrieve the first (connected) right- or left handed Nova. </summary>
            static bool GetNovaGlove(bool rightHanded, NovaGlove& glove);



            //--------------------------------------------------------------------------------------
            // Calibration Methods


            /// <summary>  Retrieve calibration values of this glove, as an array of size 5, containing x (roll), y (flexion), z (abduction) values. </summary>
            /// <param name="values"></param>
            /// <returns></returns>
            bool GetCalibrationValues(std::vector<SGCore::Kinematics::Vect3D>& values) override;

            /// <summary> Convert a SenseGlove GlovePose into calibrationValues. </summary>
            /// <param name="sData"></param>
            /// <returns></returns>
            static std::vector<Kinematics::Vect3D> GetCalibrationValues(Nova_SensorData sData);
            

            /// <summary> Applies the calibration range of this Nova a HandProfile </summary>
            /// <param name="profile"></param>
            void ApplyCalibration(HandProfile& profile) override;
            

            /// <summary> Applies the calibration range of this SenseGlove to a Nova_Profile </summary>
            /// <param name="profile"></param>
            void ApplyCalibration(Nova_Profile& profile);

            static void CalibrateInterpolation(std::vector<Kinematics::Vect3D>& minValues, std::vector<Kinematics::Vect3D>& maxValues, Nova_Profile& profile);


            //--------------------------------------------------------------------------------------
            // 6DoF Position Tracking


            /// <summary> Retrieve the location of the glove origin, based on a reference location. </summary>
            /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
            /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
            /// <param name="trackingHardware">The hardware mounted on the Nova.</param>
            /// <param name="glovePos">The 3D Position of the glove, in mm, relative to your origin</param>
            /// <param name="gloveRot">The 3D Rotation of the glove, relative to your origin</param> 
            void GetGloveLocation(Kinematics::Vect3D& refPosition, Kinematics::Quat& refRotation, PosTrackingHardware trackingHardware,
                Kinematics::Vect3D& glovePos, Kinematics::Quat& gloveRot) override;

            /// <summary> Retrieve the location of the glove origin, based on a reference location without requiring an object reference.. </summary>
            /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
            /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
            /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
            /// <param name="rightHand">Whether or not this is a left or right handed glove.</param>
            /// <param name="glovePos">The 3D Position of the glove, in mm, relative to your origin</param>
            /// <param name="gloveRot">The 3D Rotation of the glove, relative to your origin</param>
            static void CalculateGloveLocation(Kinematics::Vect3D& refPosition, Kinematics::Quat& refRotation, PosTrackingHardware trackingHardware, bool rightHand,
                Kinematics::Vect3D& glovePos, Kinematics::Quat& gloveRot);



            /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets. </summary>
            /// <remarks> The simplest interface, using default offsets </remarks>
            /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
            /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
            /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
            /// <param name="wristPos">The 3D Position of the wrist, in mm, relative to your origin</param>
            /// <param name="wristRot">The 3D Rotation of the wrist, relative to your origin</param>
            void GetWristLocation(Kinematics::Vect3D& refPosition, Kinematics::Quat& refRotation, PosTrackingHardware trackingHardware,
                Kinematics::Vect3D& wristPos, Kinematics::Quat& wristRot) override;


            /// <summary> Retrieve the location of the wrist, based on a reference location and default glove-hand offsets, without needing an object reference. </summary>
            /// <remarks> The simplest interface, using default offsets </remarks>
            /// <param name="refPosition">Position of the tracked object, in mm, relative to your origin</param>
            /// <param name="refRotation">Rotation of the tracked object relative to your origin</param>
            /// <param name="trackingHardware">The hardware mounted on the SenseGlove.</param>
            /// <param name="rightHand">Whether this is right or left hand</param>
            /// <param name="wristPos">The 3D Position of the wrist, in mm, relative to your origin</param>
            /// <param name="wristRot">The 3D Rotation of the wrist, relative to your origin</param>
            static void CalculateWristLocation(Kinematics::Vect3D& refPosition, Kinematics::Quat& refRotation, PosTrackingHardware trackingHardware, bool rightHand,
                Kinematics::Vect3D& wristPos, Kinematics::Quat& wristRot);


		};
	}
}


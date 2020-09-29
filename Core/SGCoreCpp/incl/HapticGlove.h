// ----------------------------------------------------------------------------------
// An interface for any of our gloves that can track hand motion and/or send force / vibrotectile feedback.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include "SGDevice.h"

#include "SG_FFBCmd.h"
#include "SG_BuzzCmd.h"
#include "ThumperCmd.h"
#include "Quat.h"
#include "BasicHandModel.h"
#include "HandPose.h"
#include "HandProfile.h"
#include "DeviceList.h"

#include "Vect3D.h"

#include <vector>

namespace SGCore
{
	/// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality. </summary>
	class SGCORE_API HapticGlove : public SGDevice
	{

	protected:

		//--------------------------------------------------------------------------------------
		// Properties

		/// <summary> The last Force-Feedback command sent by this glove. </summary>
		SGCore::Haptics::SG_FFBCmd lastFFBCmd = SGCore::Haptics::SG_FFBCmd::off;
		/// <summary> The Vibromotor command sent by this glove. </summary>
		SGCore::Haptics::SG_BuzzCmd lastBuzzCmd = SGCore::Haptics::SG_BuzzCmd::off;
		/// <summary> The thumper command sent by this glove. </summary>
		SGCore::Haptics::ThumperCmd lastThumper = SGCore::Haptics::ThumperCmd::off;

        /// <summary> The minimum calibration values measured by this glove. </summary>
        std::vector<Kinematics::Vect3D> minValues = {};
        /// <summary> The maximum calibration values measured by this glove.  </summary>
        std::vector<Kinematics::Vect3D> maxValues = {};


	public:

        //--------------------------------------------------------------------------------------
        // SGDevice Methods

		///<summary> Get the DeviceType enumerator of this device; used to check if its a SenseGlove/Fino/etc. </summary>
		DeviceType GetDeviceType() override { return DeviceType::UNKNOWN; }

		/// <summary> Retrieve this glove's unique identifier. </summary>
		std::string GetDeviceID() override { return "N\\A"; };

		/// <summary> Retrieve this glove's hardware (sub) version. "DK1", "DK2", etc </summary>
		std::string GetHardwareVersion() override { return "N\\A"; };

		/// <summary> Retrieve this device's firmware version. </summary>
		int GetFirmwareVersion() override { return -1; };

        //--------------------------------------------------------------------------------------
        // Tracking Methods

        /// <summary> Returns true if this glove is made for a left- ro right hand. </summary>
        /// <returns></returns>
        virtual bool IsRight() = 0;

        /// <summary>  </summary>
        /// <param name="IMU"></param>
        /// <returns></returns>
        virtual bool GetIMURotation(Kinematics::Quat& IMU)
        {
            IMU = Kinematics::Quat::identity;
            return false;
        }

        /// <summary> Calculate the Hand Pose of this device, provided it has Hand Tracking available  </summary>
        /// <param name="profile"></param>
        /// <param name="handPose"></param>
        /// <returns></returns>
        virtual bool GetHandPose(Kinematics::BasicHandModel& handGeometry, HandProfile& handProfile, HandPose& handPose)
        {
            handPose = HandPose::DefaultIdle(handProfile.isRight);
            return false;
        }

        /// <summary> Calculate the HandPose of this Device, taking into account user values, but not hand geometry. </summary>
        /// <param name="handProfile"></param>
        /// <param name="handPose"></param>
        /// <returns></returns>
        virtual bool GetHandPose(HandProfile& handProfile, HandPose& handPose)
        {
            handPose = HandPose::DefaultIdle(handProfile.isRight);
            return false;
        }


        //--------------------------------------------------------------------------------------
        // Haptics Methods.


        /// <summary> Stops all Haptic effects if any are currently playing. Useful at the end of simulations or when resetting. </summary>
        virtual void StopHaptics()
        {
            SendHaptics(Haptics::SG_FFBCmd::off, Haptics::SG_BuzzCmd::off, Haptics::ThumperCmd::off);
        }


        //other -generic- force-feedback methods (?)

        /// <summary> Send Haptic Commands to this Glove. </summary>
        /// <param name="ffb"></param>
        virtual void SendHaptics(Haptics::SG_FFBCmd ffb)
        {
            SendHaptics(ffb, lastBuzzCmd, lastThumper);
        }

        /// <summary> Send Haptic Commands to this Glove. </summary>
        /// <param name="buzz"></param>
        virtual void SendHaptics(Haptics::SG_BuzzCmd buzz)
        {
            SendHaptics(lastFFBCmd, buzz, lastThumper);
        }

        /// <summary> Send Haptic Commands to this Glove. </summary>
        /// <param name="thumper"></param>
        virtual void SendHaptics(Haptics::ThumperCmd thumper)
        {
            SendHaptics(lastFFBCmd, lastBuzzCmd, thumper);
        }

        /// <summary> Send Haptic Commands to this Glove. </summary>
        /// <param name="ffb"></param>
        /// <param name="buzz"></param>
        virtual void SendHaptics(Haptics::SG_FFBCmd ffb, Haptics::SG_BuzzCmd buzz)
        {
            SendHaptics(ffb, buzz, lastThumper);
        }

        /// <summary> Send Haptic Commands to this Glove. </summary>
        /// <param name="ffb"></param>
        /// <param name="buzz"></param>
        /// <param name="thumper"></param>
        virtual void SendHaptics(Haptics::SG_FFBCmd ffb, Haptics::SG_BuzzCmd buzz, Haptics::ThumperCmd thumper) { }


        //--------------------------------------------------------------------------------------
        // Device Detection / enumeration

        /// <summary> Get all Haptic Gloves detected on this system.</summary>
        /// <returns></returns>
        static std::vector<std::shared_ptr<HapticGlove>> GetHapticGloves();


        /// <summary> Get the first Haptic Glove detected on this System </summary>
        /// <param name="glove"></param>
        /// <returns></returns>
        static bool GetGlove(std::shared_ptr<HapticGlove>& glove);


        /// <summary> Get the first left/right Haptic Glove detected on this System </summary>
        /// <param name="glove"></param>
        /// <returns></returns>
        static bool GetGlove(bool rightHanded, std::shared_ptr<HapticGlove>& glove);

        //--------------------------------------------------------------------------------------
        // Calibration Methods

        /// <summary> Retrieve calibration values of this glove, as an array of size 5, containing x (roll), y (flexion), z (abduction) values. </summary>
        virtual bool GetCalibrationValues(std::vector<SGCore::Kinematics::Vect3D>& values);


        /// <summary> Reset Calbratrion range for this Device. </summary>
        virtual void ResetCalibrationRange();


        /// <summary> Updates calibration values only  </summary>
        virtual void UpdateCalibrationRange();


        /// <summary> Updates calibration values only </summary>
        virtual void UpdateCalibrationRange(std::vector<Kinematics::Vect3D> calibrationValues);

        /// <summary> Access the minumum- and maximum sensor values measured by this Haptic Glove, in this session. </summary>
        /// <param name="minimumVals"></param>
        /// <param name="maximumVals"></param>
        virtual void GetCalibrationRange(std::vector<Kinematics::Vect3D>& minimumVals, std::vector<Kinematics::Vect3D>& maximumVals);


        /// <summary> Updates Calibration values and applies it to the Profile. </summary>
        /// <param name="profile"></param>
        virtual void UpdateCalibration(HandProfile& profile);


        /// <summary> Apply this glove's calibration range to a handProfile. </summary>
        /// <param name="profile"></param>
        virtual void ApplyCalibration(HandProfile& profile) { }

	};
}

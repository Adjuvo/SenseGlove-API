// ----------------------------------------------------------------------------------
// A profile containing all the information required for HapticGloves.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "SG_HandProfile.h"
#include "Nova_Profile.h"

namespace SGCore
{
	/// <summary> Interpolation profiles for a user's hand, compatible with all HapticGloves. </summary>
	class SGCORE_API HandProfile
	{

	public:

		//--------------------------------------------------------------------------------------
	    // Properties

		/// <summary> Whether this profile was created for a lef- or right hand. </summary>
		bool isRight;

		/// <summary> Profile for SenseGlove's </summary>
		SG::SG_HandProfile senseGloveProfile;

		/// <summary> User profile for Nova </summary>
		Nova::Nova_Profile novaProfile;
	
		/// <summary> Filename for right hand profile. </summary>
		static std::string rhFileName;
		/// <summary> Filename for left hand profile. </summary>
		static std::string lhFileName;


		//--------------------------------------------------------------------------------------
		// Construction

		/// <summary> Default Constructor </summary>
		/// <returns></returns>
		HandProfile() { isRight = true; }

		/// <summary> Creates a new instance of a HandProfile. </summary>
		/// <param name="rightHand"></param>
		/// <param name="sgProfile"></param>
		/// <param name="fnProfile"></param>
		/// <returns></returns>
		HandProfile(bool rightHand, SG::SG_HandProfile sgProfile, Nova::Nova_Profile nvProfile)
		{
			isRight = rightHand;
			senseGloveProfile = sgProfile;
			novaProfile = nvProfile;
		}

		/// <summary> Generate a new handProfile for either a left or right hand. </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static HandProfile Default(bool rightHand);


		//--------------------------------------------------------------------------------------
		// Class Methods

		bool Equals(HandProfile other);

		/// <summary> Reset this profile back to it's default values. </summary>
		void Reset();

		//--------------------------------------------------------------------------------------
		// Serialization

		/// <summary> Convert this Nova_Profile into a string notation so it can be stored on disk. </summary>
		/// <returns></returns>
		std::string Serialize();

		/// <summary> Convert a string notation of a Nova_Profile into a new instance. </summary>
		/// <param name="serializedString"></param>
		/// <returns></returns>
		static HandProfile Deserialize(std::string serializedString);


		//--------------------------------------------------------------------------------------
		// Global Accessing and Saving

		/// <summary> Returns the directory where HandProfiles are being stored. Does not include a '\\' at teh end. </summary>
		/// <returns></returns>
		static std::string GetProfileDir();

		/// <summary> Returns the fileName of the left or right hand profiles. </summary>
		/// <param name="isRight"></param>
		/// <returns></returns>
		static std::string GetProfileFileName(bool isRight);

		/// <summary> Retireves the latest HandProfile from disk. If this function returns false, latestProfils is equal to SGCOre::HandProfile::Default(rightHand). </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static bool GetLatestProfile(bool rightHand, HandProfile& latestProfile);


		/// <summary> Stores a HandProfile on disk for other programs to access. Call this function only if your software handles calibration functions. </summary>
		/// <param name="profileToStore"></param>
		/// <returns></returns>
		static bool StoreProfile(HandProfile& profileToStore);


		/// <summary> Resets the Calibration of a specific back to default values. </summary>
		/// <param name="onDisk"></param>
		/// <param name="rightHand">  </param>
		/// <returns></returns>
		static bool ResetCalibration(bool rightHand, bool onDisk = true);

		/// <summary> Resets the Calibration of both hands back to default values. </summary>
		/// <param name="onDisk"></param>
		/// <returns></returns>
		static void ResetCalibration(bool onDisk = true)
		{
			ResetCalibration(true,  onDisk);
			ResetCalibration(false, onDisk);
		}

	};

}

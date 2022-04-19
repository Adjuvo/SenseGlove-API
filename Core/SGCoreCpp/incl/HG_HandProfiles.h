// ----------------------------------------------------------------------------------
// An interface to get calibration to / from disk.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "HandProfile.h"
#include "SensorRange.h"
#include "HapticGlove.h"

namespace SGCore
{
	/// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality. </summary>
	class SGCORE_API HG_HandProfiles
	{

	private:

		//-------------------------------------------------------------------------------------------------------------------------
		// Member Variables

		/// <summary> Profile for the left hand </summary>
		static SGCore::HandProfile leftProfile;
		/// <summary> Profile for the right hand </summary>
		static SGCore::HandProfile rightProfile;

		/// <summary> The location on disk where the profiles are stoed and retrieved from. Differs in Windows and Android. </summary>
		static std::string profileDir;
		/// <summary> Determines if we hava tried to load a profile from disk yet. If yes, and it still doesn't exist, we generate one. </summary>
		static bool dirLoaded;

		/// <summary> Name of the file containing the left-hand profile in ProfileDirectory </summary>
		static std::string leftHandFile;
		/// <summary> Name of the file containing the right-hand profile in ProfileDirectory </summary>
		static std::string rightHandFile;

		/// <summary> A SubDirectory of ProfileDirectory to store the last calibration ranges used for a device. </summary>
		static std::string rangeDir;

		/// <summary> Determines if we hava tried to load a profile from disk yet. If yes, and it still doesn't exist, we generate one. </summary>
		static bool triedLoading;

		/// <summary> Load a profile form a file, return true if it was succesfully deserialized. </summary>
		/// <param name="filePath"></param>
		/// <param name="currProfile"></param>
		/// <returns></returns>
		static bool LoadProfile(std::string filePath, SGCore::HandProfile& currProfile);

	public:

		//-------------------------------------------------------------------------------------------------------------------------
		// Accessors

		/// <summary> Returns the directory where our HandProfiles are stored. </summary>
		static std::string GetProfileDirectory();
		/// <summary> Set the directory where our HandProfiles are stored. </summary>
		static void SetProfileDirectory(std::string value);

		/// <summary> Access the latest Left Hand Profile from disk </summary>
		static void GetRightHandProfile(SGCore::HandProfile& profile);
		/// <summary> Sets the newest Left Hand Profile - aslo stores it on disk </summary>
		static void SetRightHandProfile(SGCore::HandProfile);

		/// <summary> Access the latest Left Hand Profile from disk </summary>
		static void GetLeftHandProfile(SGCore::HandProfile& profile);
		/// <summary> Sets the newest Left Hand Profile - aslo stores it on disk </summary>
		static void SetLeftHandProfile(SGCore::HandProfile);


		//-------------------------------------------------------------------------------------------------------------------------
		// Profile Accessing Functions

		/// <summary> Retrieve a left- or right handed profile. </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static void GetProfile(bool rightHand, SGCore::HandProfile& profile);

		/// <summary> Store a profile in the global variables and on disk. The profile determines if this is a left- or right hand. </summary>
		/// <param name="profile"></param>
		static void SetProfile(SGCore::HandProfile profile);

		/// <summary> Store a profile in the global variables and on disk. You determine if this is a left- or right hand. </summary>
		/// <param name="profile"></param>
		/// <param name="rightHand"></param>
		static void SetProfile(SGCore::HandProfile profile, bool rightHand);

		/// <summary> Restore both profiles back to their default values. </summary>
		static void RestoreDefaults();
		/// <summary> Restore the left- or right hand profiles back to their default values. </summary>
		/// <param name="rightHand"></param>
		static void RestoreDefaults(bool rightHand);

		//-------------------------------------------------------------------------------------------------------------------------
		// Store / Load functions

		/// <summary> Load the latest profiles from disk. Automatically called when you first try to access a profile.
		/// Exposed so you can force-reload profiles. </summary>
		static void TryLoadFromDisk();

		/// <summary> Stores the last sensor range of a glove. </summary>
		/// <param name="currentRange"></param>
		/// <param name="forGlove"></param>
		/// <returns></returns>
		static bool SaveLastRange(SGCore::Calibration::SensorRange currentRange, std::shared_ptr<SGCore::HapticGlove> forGlove);

		/// <summary> Loads the last sensor range of a glove. </summary>
		/// <param name="forGlove"></param>
		/// <param name="lastRange"></param>
		/// <returns></returns>
		static bool LoadLastRange(std::shared_ptr<SGCore::HapticGlove> forGlove, SGCore::Calibration::SensorRange& lastRange);

	};
}
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

		/// <summary> User profile for Fino </summary>
		Nova::Nova_Profile novaProfile;
	
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

		/// <summary> Convert this Fino_Profile into a string notation so it can be stored on disk. </summary>
		/// <returns></returns>
		std::string Serialize();

		/// <summary> Convert a string notation of a Fino_Profile into a new instance. </summary>
		/// <param name="serializedString"></param>
		/// <returns></returns>
		static HandProfile Deserialize(std::string serializedString);



	};

}

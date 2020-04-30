// ----------------------------------------------------------------------------------
// Data class containing all variables to draw or analyze a virtual hand 
// in different formats.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <vector>
#include <string>
#include "Vect3D.h"
#include "Quat.h"

namespace SGCore
{
	/// <summary> Contains all variables required to draw or analyze a virtual hand. </summary>
	struct SGCORE_API HandPose
	{

	public:

		//---------------------------------------------------------------------------------------------------------------------
		// Properties

		///<summary> Whether or not this HandPose was created for be a right- or left hand. </summary>
		bool isRight;

		///<summary> Positions of all hand joints relative to the Sense Glove origin. From thumb to pinky, proximal to distal. </summary>
		std::vector< std::vector<Kinematics::Vect3D> > jointPositions;

		///<summary> Quaternion rotations of all hand joints. From thumb to pinky, proximal to distal. </summary>
		std::vector< std::vector<Kinematics::Quat> > jointRotations;

		///<summary> Euler representations of all possible hand angles. From thumb to pinky, proximal to distal. </summary>
		std::vector< std::vector<Kinematics::Vect3D> > handAngles;


		//---------------------------------------------------------------------------------------------------------------------
		// Construction

		/// <summary> Default Constructor. </summary>
		HandPose();

		/// <summary> Default Destructor. </summary>
		~HandPose();

		/// <summary> Create a new instance of HandPose. </summary>
		HandPose(bool right, std::vector< std::vector<Kinematics::Vect3D> > jointPos,
			std::vector< std::vector<Kinematics::Quat> > jointRot,
			std::vector< std::vector<Kinematics::Vect3D> > hAngles);

		/// <summary> Create a new instance of a left or right handed Pose that is "idle"; in a neutral position. </summary>
		/// <param name="right"></param>
		/// <returns></returns>
		static HandPose DefaultIdle(bool right);

		/// <summary> Returns true of these two handposes are roughly equal. </summary>
		bool Equals(HandPose other);

		//---------------------------------------------------------------------------------------------------------------------
		// Serialization

		///<summary> Serialize this HandProfile into a string representation </summary>
		std::string Serialize();

		///<summary> Deserialize a HandProfile back into useable values. </summary>
		static HandPose Deserialize(std::string serializedString);

		//---------------------------------------------------------------------------------------------------------------------
		// Formats

		//GetFormat (animator), GetFormat (MoCap), etc?



	};
}

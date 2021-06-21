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
#include "Fingers.h"
#include "BasicHandModel.h"

namespace SGCore
{
	/// <summary> Contains all variables required to draw or analyze a virtual hand. </summary>
	class SGCORE_API HandPose
	{
	protected:

		///<summary> Returns the total flexion of a specific finger as a value between 0 (fully extended) and 1 (fully flexed). </summary>
		///<remarks> Separate function because we use it multiple times, protected because we don't want indexOutOfRange exceptions. </remarks>
		float GetNormalizedFlexion(int finger, bool clamp01 = true);


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

		/// <summary> Returns true of these two handposes are roughly equal. </summary>
		bool Equals(HandPose other);

		//---------------------------------------------------------------------------------------------------------------------
		// Serialization

		std::string ToString(bool shortFormat = false);

		///<summary> Serialize this HandProfile into a string representation </summary>
		std::string Serialize();

		///<summary> Deserialize a HandProfile back into useable values. </summary>
		static HandPose Deserialize(std::string serializedString);

		//---------------------------------------------------------------------------------------------------------------------
		// Formats

		//GetFormat (animator), GetFormat (MoCap), etc?

		///<summary> Returns the total flexion of a specific finger as a value between 0 (fully extended) and 1 (fully flexed). </summary>
		///<remarks> Useful for animation or for detecting gestures </remarks>
		float GetNormalizedFlexion(Finger finger, bool clamp01 = true);

		///<summary> Returns the total flexion the fingers as a value between 0 (fully extended) and 1 (fully flexed). </summary>
		///<remarks> Useful for animation or for detecting gestures </remarks>
		std::vector<float> GetNormalizedFlexion(bool clamp01 = true);


        //---------------------------------------------------------------------------------------------------------------------
        // Generating Poses

        /// <summary> Generate a HandPose based on articulation angles (handAngles). </summary>
        /// <param name="handAngles"></param>
        /// <param name="rightHanded"></param>
        /// <param name="handDimensions"></param>
        /// <returns></returns>
		static HandPose FromHandAngles(std::vector<std::vector<Kinematics::Vect3D>>& handAngles, bool rightHanded, Kinematics::BasicHandModel& handDimensions);

		/// <summary> Generate a HandPose based on articulation angles (handAngles), with a default HandModel. </summary>
		/// <param name="handAngles"></param>
		/// <param name="rightHanded"></param>
		/// <returns></returns>
		static HandPose FromHandAngles(std::vector<std::vector<Kinematics::Vect3D>>& handAngles, bool rightHanded);



        /// <summary> Create a new instance of a left or right handed Pose that is "idle"; in a neutral position. </summary>
        /// <param name="rightHand"></param>
        /// <param name="handDimensions"></param>
        /// <returns></returns>
		static HandPose DefaultIdle(bool rightHand, Kinematics::BasicHandModel& handDimensions);

		/// <summary> Create a new instance of a left or right handed Pose that is "idle"; in a neutral position. </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static HandPose DefaultIdle(bool rightHand);

        /// <summary> Generates a HandPose representing an 'open hand', used in calibration to determine finger extension. </summary>
        /// <param name="rightHand"></param>
        /// <param name="handDimensions"></param>
        /// <returns></returns>
		static HandPose FlatHand(bool rightHand, Kinematics::BasicHandModel& handDimensions);

		/// <summary> Generates a HandPose representing an 'open hand', used in calibration to determine finger extension. </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static HandPose FlatHand(bool rightHand);

        /// <summary> Generates a HandPose representing a 'thumbs up', used in calibration to determine finger flexion, thumb extension and adduction. </summary>
        /// <param name="rightHand"></param>
        /// <param name="handDimensions"></param>
        /// <returns></returns>
		static HandPose ThumbsUp(bool rightHand, Kinematics::BasicHandModel& handDimensions);

		/// <summary> Generates a HandPose representing a 'thumbs up', used in calibration to determine finger flexion, thumb extension and adduction. </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static HandPose ThumbsUp(bool rightHand);

        /// <summary> Generates a HandPose representing a 'fist', used in calibration to determine, thumb flexion and abduction. </summary>
        /// <param name="rightHand"></param>
        /// <param name="handDimensions"></param>
        /// <returns></returns>
		static HandPose Fist(bool rightHand, Kinematics::BasicHandModel& handDimensions);

		/// <summary> Generates a HandPose representing a 'fist', used in calibration to determine, thumb flexion and abduction. </summary>
		/// <param name="rightHand"></param>
		/// <returns></returns>
		static HandPose Fist(bool rightHand);


	};
}

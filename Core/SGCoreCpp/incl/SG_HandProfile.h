// ----------------------------------------------------------------------------------
// Input for Sense Glove kinematics to calculate a HandPose.
// Output of calibration algorithms.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <vector>
#include <string>
#include "Vect3D.h"
#include "BasicHandModel.h"
#include "HandInterpolator.h"

namespace SGCore
{
	namespace SG
	{
		//--------------------------------------------------------------------------------------
		// Solver

		///<summary> How this Sense Glove converts sensor data into a HandPose. </summary>
		enum class SGCORE_API SG_Solver
		{
			/// <summary> Hand angles are interpolated based on the total flexion / abduction of the exoskeleton </summary>
			Interpolation = 0 //default.
		};


		/// <summary> Contains everything a Sense Glove needs to calculate a HandPose. </summary>
		class SGCORE_API SG_HandProfile
		{

		protected:

			//---------------------------------------------------------------------------------------------------------------------
			// Properties

			///<summary> Whether this profile had been created for a left- or right hand. </summary>
			bool isRight;

		public:

			/// <summary> Interpolation set to estimate joint angles. </summary>
			Kinematics::HandInterpolator interpolationSet;

			/// <summary> Offset from thimble to fingertip, used for Inverse Kinematics. </summary>
			std::vector<Kinematics::Vect3D> fingerThimbleOffset;

			/// <summary> The method with which to solve the HandPose </summary>
			SG_Solver solver;

			/// <summary> Default offset from thimble to fingertip. </summary>
			static const Kinematics::Vect3D dThimbleOffset;

			//---------------------------------------------------------------------------------------------------------------------
			// Construction

			///<summary> Basic Constructor </summary>
			SG_HandProfile();

			/// <summary> Create a new Hand Profile for the Sense Glove. </summary>
			SG_HandProfile(bool right, Kinematics::HandInterpolator interpolator,
				SG_Solver solvr, std::vector<Kinematics::Vect3D> TfingerThimble);

			///<summary> Basic Destructor </summary>
			~SG_HandProfile() { }

			///<summary> Retrieve a 'new' profile, for either a left or right hand. </summary>
			static SG_HandProfile Default(bool right);

			//---------------------------------------------------------------------------------------------------------------------
			// Accessors

			/// <summary> Check whether this profile has been created for a right hand (true) or left hand (false). </summary>
			bool IsRight() { return isRight; }

			bool Equals(SG_HandProfile other);

			//---------------------------------------------------------------------------------------------------------------------
			// Serialization

			///<summary> Serialize this HandProfile into a string representation </summary>
			std::string Serialize();

			///<summary> Deserialize a HandProfile back into useable values. </summary>
			static SG_HandProfile Deserialize(std::string serializedString);
			

		};
	}
}
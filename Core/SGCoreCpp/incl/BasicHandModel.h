// ----------------------------------------------------------------------------------
// A data class containing the minimum required data for a hand's forward kinematics.
// Used in both kinematics and calibratrion.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <vector>
#include "Vect3D.h"
#include "Quat.h"
#include "Fingers.h"

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> Represents data of a user's hand required for forward kinematics. </summary>
		struct SGCORE_API BasicHandModel
		{

		protected:

			/// <summary> Test if the input has enough values. if not, add the appropriate values to compensate. </summary>
			virtual void Validate(bool right);

			/// <summary> Default finger lengths (based on right hand). </summary>
			/// <remarks> Any missing fingers are replaced with their respective value. </remarks>
			const static std::vector<std::vector<float>> baseFingerLengths;

			/// <summary> Default joint positions (based on right hand). </summary>
			/// <remarks> Any missing positions are replaced with their respective value. </remarks>
			const static std::vector<Vect3D> baseJointPositions;

			/// <summary> Default joint rotations (based on right hand). </summary>
			/// <remarks> Any missing rotation are replaced with their respective value. </remarks>
			const static std::vector<Vect3D> baseJointRotations;

		public:


			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> The length of individual finger phalangers in mm, soted per finger. Generally 5x3 </summary>
			std::vector< std::vector<float> > fingerLengths;

			/// <summary> Starting joint positions relative to the device Origin </summary>
			std::vector<Vect3D> startJointPositions;

			/// <summary> Starting joint rotations relative to the device Origin </summary>
			std::vector<Quat> startJointRotations;


			//--------------------------------------------------------------------------------------
			// Construction

			/// <summary> Basic class Constructor. </summary>
			BasicHandModel();

			/// <summary> Create a new basicHandModel with no starting rotations. </summary>
			BasicHandModel(bool right, std::vector<std::vector<float>> lengths, std::vector<Vect3D> startPositions);

			/// <summary> Create a new basicHandModel </summary>
			BasicHandModel(bool right, std::vector<std::vector<float>> lengths, std::vector<Vect3D> startPositions,
				std::vector<Quat> startRotations);

			/// <summary> Retrieve a default left or right hand model. </summary>
			static BasicHandModel Default(bool right);

			/// <summary> Basic class Destructor. </summary>
			~BasicHandModel();

			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Retrieve the finger lengths of a specific finger. </summary>
			std::vector<float> GetFingerLengths(Finger finger);

			/// <summary> Set the finger lengths of a specific finger. </summary>
			void SetFingerLengths(std::vector<float>, Finger finger);

			/// <summary> Retrieve the start position of a specific finger. </summary>
			Vect3D GetJointPosition(Finger finger);

			/// <summary> Set the start position of a specific finger </summary>
			void SetJointPosition(Vect3D newPosition, Finger finger);

			/// <summary> Retrieve the start rotation of a specific finger. </summary>
			Quat GetJointRotation(Finger finger);

			/// <summary> Set the start rotation of a specific finger </summary>
			void SetJointRotation(Quat newRotation, Finger finger);


			/// <summary> Retrieve the lengths of a specific finger, as Vect3D representation (L, 0, 0). </summary>
			/// <remarks> Used for forwards kinematics. </remarks>
			std::vector<Vect3D> Get3DLengths(Finger finger);

		};

	}
}
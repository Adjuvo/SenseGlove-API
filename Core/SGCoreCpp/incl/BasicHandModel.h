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
		class SGCORE_API BasicHandModel
		{

		protected:

			/// <summary> Test if the input has enough values. if not, add the appropriate values to compensate. </summary>
			virtual void Validate();

			/// <summary> Calculate hand variables (finger lengths, ratioes) based on current values. </summary>
			void CalculateVariables();



            /// <summary> Calculated Total finger lengths </summary>
            std::vector<float> totalLengths;

            /// <summary> Calculated Finger ratios [0..1] </summary>
            std::vector< std::vector<float> > fingerRatios;


		public:


			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> The length of individual finger phalangers in mm, soted per finger. Generally 5x3 </summary>
			std::vector< std::vector<float> > fingerLengths;

			/// <summary> Starting joint positions relative to the device Origin </summary>
			std::vector<Vect3D> startJointPositions;

			/// <summary> Starting joint rotations relative to the device Origin </summary>
			std::vector<Quat> startJointRotations;

			/// <summary> Whether or not this BasicHandModel was created for a left- or right hand. Used for validation. </summary>
			bool isRight;


			// Default values

			/// <summary> Default finger lengths (based on right hand). </summary>
			/// <remarks> Any missing fingers are replaced with their respective value. </remarks>
			const static std::vector<std::vector<float>> baseFingerLengths;

			/// <summary> Default joint positions (based on right hand). </summary>
			/// <remarks> Any missing positions are replaced with their respective value. </remarks>
			const static std::vector<Vect3D> baseJointPositions;

			/// <summary> Default joint rotations (based on right hand). </summary>
			/// <remarks> Any missing rotation are replaced with their respective value. </remarks>
			const static std::vector<Vect3D> baseJointRotations;



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


			/// <summary> Get the total length of a specific finger, in mm </summary>
			float GetTotalLength(Finger finger);
			/// <summary> Get the total lengths of a fingers, in mm </summary>
			std::vector<float> GetTotalLengths();


			/// <summary> Get the finger ratioes of a specific finger.  </summary>
			std::vector<float> GetFingerRatioes(Finger finger);
			/// <summary> Get the finger ratioes of all fingers. </summary>
			std::vector<std::vector<float>> GetFingerRatioes();


			/// <summary> Retrieve the lengths of a specific finger, as Vect3D representation (L, 0, 0). </summary>
			/// <remarks> Used for forwards kinematics. </remarks>
			std::vector<Vect3D> Get3DLengths(Finger finger);

			/// <summary> Check if this BasicHandModel has the same values as another BasicHandModel. </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool Equals(BasicHandModel other);

            /// <summary> Convert this handModel into a string notation, readable for humans. Does not include starting positions / rotations. </summary>
            /// <returns></returns>
            std::string ToString();

			/// <summary> Convert this handModel into a string notation, readable for humans. Optionally includes starting positions / rotations. </summary>
			/// <param name="lengthsOnly"></param>
			/// <returns></returns>
			std::string ToString(bool lengthsOnly);


			//--------------------------------------------------------------------------------------
			// Serialization

			/// <summary> Serialize this HandModel into a string representation. </summary>
			/// <returns></returns>
			std::string Serialize();
            
			///<summary> Convert a serialized HandModel back into its class representation. </summary>
			static BasicHandModel Deserialize(std::string serializedString);

		};

	}
}
// ----------------------------------------------------------------------------------
// Contains interpolation sets for all hand joint movements that can be 
// calculated using the Sense Glove.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <vector>

#include "Fingers.h"
#include "Quat.h"
#include "Vect3D.h"
#include "InterpolationSet.h"
#include "Serializer.h"

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> Contains interpolation sets of all joint movements that can be caluclated into a handPose. </summary>
		class SGCORE_API HandInterpolator
		{

		public:

			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> Starting rotation of the thumb cmc joint. </summary>
			Quat cmcStartRot;

			///<summary> Interpolation sets for each finger. First index indicates which finger, Second index indicates the joint movement. </summary>
			std::vector< std::vector< InterpolationSet > > jointInterpolations;

			//--------------------------------------------------------------------------------------
			// Construction

			/// <summary> Basic Constructor </summary>
			HandInterpolator();

			/// <summary> Basic Destructor </summary>
			~HandInterpolator();

			/// <summary> Create a new basic HandInterpolator without a starting rotation. </summary>
			HandInterpolator(std::vector< std::vector< InterpolationSet > > interpolations);

			/// <summary> Create a new basic HandInterpolator with a starting rotation. </summary>
			HandInterpolator(std::vector< std::vector< InterpolationSet > > interpolations, Quat cmcStart);


			/// <summary> Create a default instance of a left- or right handed interpolator. </summary>
			static HandInterpolator Default(bool rightHand);


			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Calculate any finger's movement rotation, using an input value. </summary>
			float CalculateAngle(Finger finger, int movement, float value);

			/// <summary> Calculate a finger movement's rotation, using an input value. </summary>
			float CalculateAngle(Finger finger, FingerMovement movement, float value);

			/// <summary> Calculate a thumb movement's rotation, using an input value. </summary>
			float CalculateAngle(Finger finger, ThumbMovement movement, float value);


			bool Equals(HandInterpolator other);



			//--------------------------------------------------------------------------------------
			// Hand Interpolation Methods

			/// <summary> Calculate all angles of a specific finger based on an Interpolator and input angles. </summary>
			static std::vector<Vect3D> InterpolateFingerAngles(Finger finger, HandInterpolator& interpolator,
				Vect3D totalGloveAngles);

			/// <summary> Calculate all angles of the Thumb based on an Interpolator and input angles. </summary>
			static std::vector<Vect3D> InterpolateThumbAngles(HandInterpolator& interpolator,
				Vect3D totalGloveAngles);

			/// <summary> Calculate all hand angles based on an interpolator and total xyz angles. </summary>
			static std::vector<std::vector<Vect3D>> InterpolateHandAngles(HandInterpolator& profile,
				std::vector<Vect3D> totalAngles);


			//--------------------------------------------------------------------------------------
			// Serialization

			/// <summary> Serialize this HandInterpolator into a string representation. </summary>
			/// <returns></returns>
			std::string Serialize();

			/// <summary> Convert a serialized HandInterpolator back into a class representation. </summary>
			/// <param name="serializedString"></param>
			/// <returns></returns>
			static HandInterpolator Deserialize(std::string serializedString);


		};
	}
}
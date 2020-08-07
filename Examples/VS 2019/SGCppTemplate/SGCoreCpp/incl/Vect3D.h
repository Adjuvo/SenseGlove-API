// ----------------------------------------------------------------------------------
// Represents a position or rotation in 3D Space.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> Represents a vector with x,y,z coordinates. </summary>
		class SGCORE_API Vect3D
		{

		public:

			//--------------------------------------------------------------------------------------
			// Properties

			///<summary> x-component of the 3D vector. </summary>
			float x;
			///<summary> y-component of the 3D vector. </summary>
			float y;
			///<summary> z-component of the 3D vector. </summary>
			float z;

			/// <summary> Represents a vector with coordinates (0, 0, 0). </summary>
			static const Vect3D zero;

			//--------------------------------------------------------------------------------------
			// Construction

			/// <summary> Creates an empty vector (0, 0, 0) for internal use </summary>
			Vect3D();

			/// <summary> Create a new instance of a 3D vector. </summary>
			Vect3D(float X, float Y, float Z);

			/// <summary> Basic Destructor </summary>
			~Vect3D();


			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Calculate the magnitude or 'length' of this Vector </summary>
			float Magnitude();

			/// <summary> Returns this vector normalized to have a Magnitude on 1. </summary>
			void Normalize();

			/// <summary> Scale all elements of this vector by a certain factor. </summary>
			void Scale(float s);

			/// <summary> Calculate the distance between this Vector and another one. </summary>
			float DistTo(Vect3D other);

			/// <summary> Check if this Vector is roughly equal to another. </summary>
			bool Equals(Vect3D that);

			/// <summary> Create a string representation of this Vector. </summary>
			std::string ToString();


			//--------------------------------------------------------------------------------------
			// Mathematic Operations

			// Overload + operator to add two Vect3 objects.
			Vect3D operator+(const Vect3D& that);

			// Overload - operator to subtract two Vect3 objects.
			Vect3D operator-(const Vect3D& that);

			// Overload - operator to scale a vector3 by a float
			Vect3D operator*(const float& s);

			//--------------------------------------------------------------------------------------
			// Serialization

			/// <summary> Serialize a Vect3D into a string representation </summary>
			static bool Deserialize(std::string str, Vect3D& result, const char delim);

			/// <summary> Convert a serialized Vect3D back into its class representation. </summary>
			/// <param name="delim"></param>
			/// <returns></returns>
			std::string Serialize(const char delim);

		};
	}
}

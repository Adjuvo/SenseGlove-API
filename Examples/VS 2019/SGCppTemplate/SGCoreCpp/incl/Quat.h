// ----------------------------------------------------------------------------------
// A Quaternion is a representation of a rotation in 3D space without the problem
// of Gimball Lock that exists in Euler representations.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include "Vect3D.h"

namespace SGCore
{
	namespace Kinematics
	{
		/// <summary> A rotation in 3D space that can be applied to a 3D vector or converted into Euler Angles. </summary>
		class SGCORE_API Quat
		{

		public:

			//--------------------------------------------------------------------------------------
			// Properties

			/// <summary> Quaternion element. Not directly related to a rotation or position. </summary>
			float x, y, z, w;

			/// <summary> Represents 'no rotation' in quaternion space. </summary>
			static const Quat identity;

			//--------------------------------------------------------------------------------------
			// Construction

			/// <summary> Create a new Quaternion rotation of 0, 0, 0, 1. </summary>
			Quat();

			/// <summary> Create a new Quaternion rotation. </summary>
			Quat(float X, float Y, float Z, float W);

			/// <summary> Default Destructor. </summary>
			~Quat() { }


			// Alt. Constructors 

			///<summary> Create a new Quaternion Rotation from its euler angle representation. </summary>
			static Quat FromEuler(float xAngle, float yAngle, float zAngle);

			///<summary> Create a new Quaternion Rotation from its euler angle representation. </summary>
			static Quat FromEuler(Vect3D euler) { return FromEuler(euler.x, euler.y, euler.z); }

			///<summary> Create a new Quaternion Rotation from an angle-axis representation. </summary>
			static Quat FromAngleAxis(float angle, float axisX, float axisY, float axisZ);

			///<summary> Create a new Quaternion Rotation from an angle-axis representation. </summary>
			static Quat FromAngleAxis(float angle, Vect3D axis) { return FromAngleAxis(angle, axis.x, axis.y, axis.z); }

			//--------------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Create a string representation of the Quaternion rotation. </summary>
			std::string ToString();

			/// <summary> Retrieve this Quaternion's euler angle notation. </summary>
			Vect3D ToEuler();

			/// <summary> Rotate myVect by this quaternion rotation. </summary>
			Vect3D Rotate(Vect3D myVect);

			/// <summary> Check if two quaternions have equal values. </summary>
			bool Equals(Quat that);

			///<summary> Check if this Quaternion is the identity quaternion (meaning it does not rotate anything.) </summary>
			bool IsIdentity();


			/// <summary> Returns the inverse if q (a.k.a. a rotation in the other direction) </summary>
			static Quat Invert(Quat q); //-x-y-z w


			//--------------------------------------------------------------------------------------
			// Serialization

			///<summary> Parse a Quaternion from a string. </summary>
			static bool Deserialize(std::string str, Quat& result, const char delim = ',');

			std::string Serialize(const char delim = ',');


			//--------------------------------------------------------------------------------------
			// Operators

			//multiply this quaternion by another (that) - by quaternion law, that is the first rotation, followed by this.
			Quat operator*(const Quat& that);

			//multiply this quaternion with a vect3, a.k.a. rotate it.
			Vect3D operator*(const Vect3D& that);

		};
	}
}
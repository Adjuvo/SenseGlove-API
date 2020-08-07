// ----------------------------------------------------------------------------------
// Utility class to Serialize / Deserialize various variables. Re-used throughout methods.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include <vector>

#include "Quat.h"
#include "Vect3D.h"

namespace SGCore
{
	namespace Util
	{
		///<summary> Utility class to serialize / deserialize classes. </summary>
		class SGCORE_API Serializer
		{
		public:

			/// <summary> Character opening a new block of data. </summary>
			static const char openChar = '{';
			/// <summary> Character closing a block of data. </summary>
			static const char closeChar = '}';
			/// <summary> Character to separate values. </summary>
			static const char valueDelim = ';';

			///<summary> Filters spaces from a a string. </summary>
			static std::string FilterSpaces(std::string input);

			/// <summary> Filter opening / closing charaters at the beginning and end of a string, if they exist. </summary>
			/// <param name="serialized"></param>
			static void FilterBrackets(std::string& serialized);

			///<summary> Split a serialized string by its top level blocks </summary>
			static std::vector<std::string> SplitBlocks(std::string fullSerialized, bool filterSpaces = false);

			/// <summary> Enclose a string with our opening / closing characters. </summary>
			/// <param name="str"></param>
			/// <returns></returns>
			static std::string Enclose(std::string str);

			/// <summary> Serialize a floating point array/vector </summary>
			static std::string Serialize(std::vector<float> floatArray, bool enclosed = true);
			/// <summary> Serialize a 2D floating point array/vector </summary>
			static std::string Serialize(std::vector<std::vector<float>> floatArray, bool enclosed = true);
			/// <summary> Serialize a Quaternion </summary>
			static std::string Serialize(Kinematics::Quat quat, bool enclosed = true);
			/// <summary> Serialize a Quaternion array/vector </summary>
			static std::string Serialize(std::vector<Kinematics::Quat> quatArray, bool enclosed = true);
			/// <summary> Serialize a 2D Quaternion array/vector </summary>
			static std::string Serialize(std::vector<std::vector<Kinematics::Quat>> quatArray, bool enclosed = true);
			/// <summary> Serialize a Vector </summary>
			static std::string Serialize(Kinematics::Vect3D vect, bool enclosed = true);
			/// <summary> Serialize a Vector array/vector </summary>
			static std::string Serialize(std::vector<Kinematics::Vect3D> vectArray, bool enclosed = true);
			/// <summary> Serialize a 2d Vector array/vector </summary>
			static std::string Serialize(std::vector<std::vector<Kinematics::Vect3D>> vectArray, bool enclosed = true);
			/// <summary> Serialize a boolean array/vector </summary>
			static std::string Serialize(std::vector<bool> boolArray, bool enclosed = true);

			/// <summary> Convert a serialized string back into an array of floating points  </summary>
			static std::vector<float> DeserializeFloats(std::string serialized);
			/// <summary> Convert a serialized string back into a 2D array of floating points  </summary>
			static std::vector<std::vector<float>> DeserializeFloats2D(std::string serialized);
			
			/// <summary> Convert a serialized string back into a Quaternion  </summary>
			static Kinematics::Quat DeserializeQuat(std::string serialized);
			/// <summary> Convert a serialized string back into an array of Quaternions  </summary>
			static std::vector<Kinematics::Quat> DeserializeQuats(std::string serialized);
			/// <summary> Convert a serialized string back into a 2D array of Quaternions </summary>
			static std::vector<std::vector<Kinematics::Quat>> DeserializeQuats2D(std::string serialized);

			/// <summary> Convert a serialized string back into a Vector  </summary>
			static Kinematics::Vect3D DeserializeVect(std::string serialized);			
			/// <summary> Convert a serialized string back into an array of Vectors </summary>
			static std::vector<Kinematics::Vect3D> DeserializeVects(std::string serialized);
			/// <summary> Convert a serialized string back into a 2D array of Vectors </summary>
			static std::vector<std::vector<Kinematics::Vect3D>> DeserializeVects2D(std::string serialized);

			/// <summary> Convert a serialized string back into an array of booleans </summary>
			static std::vector<bool> DeserializeBools(std::string serialized);
		};

	}
}
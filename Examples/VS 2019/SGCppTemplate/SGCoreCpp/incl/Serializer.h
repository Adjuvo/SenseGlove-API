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
		///<summary>  </summary>
		class SGCORE_API Serializer
		{
		public:

			static const char openChar = '{';
			static const char closeChar = '}';
			static const char valueDelim = ';';

			///<summary> Filters spaces from a a string. </summary>
			static std::string FilterSpaces(std::string input);

			static void FilterBrackets(std::string& serialized);

			///<summary> Split a serialized string by its top level blocks </summary>
			static std::vector<std::string> SplitBlocks(std::string fullSerialized, bool filterSpaces = false);

			static std::string Enclose(std::string str);


			static std::string Serialize(std::vector<float> floatArray, bool enclosed = true);
			static std::string Serialize(std::vector<std::vector<float>> floatArray, bool enclosed = true);
			static std::string Serialize(Kinematics::Quat quat, bool enclosed = true);
			static std::string Serialize(std::vector<Kinematics::Quat> quatArray, bool enclosed = true);
			static std::string Serialize(std::vector<std::vector<Kinematics::Quat>> quatArray, bool enclosed = true);
			static std::string Serialize(Kinematics::Vect3D vect, bool enclosed = true);
			static std::string Serialize(std::vector<Kinematics::Vect3D> vectArray, bool enclosed = true);
			static std::string Serialize(std::vector<std::vector<Kinematics::Vect3D>> vectArray, bool enclosed = true);
			static std::string Serialize(std::vector<bool> boolArray, bool enclosed = true);

			static std::vector<float> DeserializeFloats(std::string serialized);
			static std::vector<std::vector<float>> DeserializeFloats2D(std::string serialized);
			
			static Kinematics::Quat DeserializeQuat(std::string serialized);
			static std::vector<Kinematics::Quat> DeserializeQuats(std::string serialized);
			static std::vector<std::vector<Kinematics::Quat>> DeserializeQuats2D(std::string serialized);

			static Kinematics::Vect3D DeserializeVect(std::string serialized);			
			static std::vector<Kinematics::Vect3D> DeserializeVects(std::string serialized);
			static std::vector<std::vector<Kinematics::Vect3D>> DeserializeVects2D(std::string serialized);

			static std::vector<bool> DeserializeBools(std::string serialized);
		};

	}
}
// ----------------------------------------------------------------------------------
// String conversion, parsing and other utility stuff. Much more prominent in C++.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>
#include <vector>
#include "Fingers.h"
#include "Vect3D.h"
#include "Quat.h"

namespace SGCore
{
	namespace Util
	{
		/// <summary> Utility class to convert strings into useable values. </summary>
		class SGCORE_API StrStuff
		{

		public:

			///<summary> Split a std::string into a vector of std::strings by a delimiter </summary>
			static std::vector<std::string> Split(std::string s, const char delimiter);

			static std::string QuickSplit(std::string& input, char delim, int getIndex);

			/// <summary> Convert a string into an integer value. </summary>
			static int ToInt(std::string str, int fallback = 0);

			/// <summary> Convert a string into a decimal value. </summary>
			static float ToFloat(std::string str, float fallback = 0);

			/// <summary> Convert a finger into a string notation. </summary>
			static std::string ToString(SGCore::Finger finger);

			/// <summary> Replace all occurences of a character with another one. </summary>
			static std::string ReplaceChars(std::string str, char from, char to);

			/// <summary> Convert a value in radians into a rounded integer, as a string. e.g. 4.999999999999999 -> 5. </summary>
			static std::string RoundedDegrees(float valInRad);

			static bool Contains(std::string haystack, std::string needle);

			/// <summary> Print the different sizes within a 2D array </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="vect"></param>
			/// <returns></returns>
			template <class T> static std::string PrintSize(std::vector<std::vector<T>>& vect)
			{
				int size = vect.size();
				std::string res = "(" + std::to_string(size) + ")[";
				for (int i = 0; i < size; i++)
				{
					res += std::to_string(vect[i].size());
					if (i < size - 1) { res += ", "; }
				}
				return res + "]";
			}

		};
	}
}


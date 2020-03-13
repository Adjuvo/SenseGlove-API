// ----------------------------------------------------------------------------------
// A command for five fingers that can be sent to a Sense Glove device.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include <string>
#include <vector>
#include "MathDefines.h"

namespace SGCore
{
	namespace Haptics
	{
		/// <summary> A command that contains values (levels) for five fingers. </summary>
		class SGCORE_API SG_FingerCmd
		{

		protected:

			//--------------------------------------------------------------------------------
			// Properties

			/// <summary> Input level for specific finger. </summary>
			std::vector<int> levels;

			/// <summary> Ensure that a value is within acceptable range. </summary>
			virtual int Validate(int value);

			//--------------------------------------------------------------------------------
			// Construction

			SG_FingerCmd();

		public:

			~SG_FingerCmd();

			//--------------------------------------------------------------------------------
			// Accessors

			virtual std::vector<int> GetLevels() { return levels; }
			virtual int GetLevel(int finger) { return levels[finger]; }
			virtual void SetLevel(int finger, int value) { levels[finger] = Validate(value); }

			//--------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Check if this command contains the same values as another. </summary>
			virtual bool Equals(SG_FingerCmd other);

			/// <returns> Create a string representation of this finger command. </returns>
			virtual std::string ToString();

		};
	}
}
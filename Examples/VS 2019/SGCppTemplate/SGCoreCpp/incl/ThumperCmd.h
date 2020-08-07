// ----------------------------------------------------------------------------------
// Thumper command
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

namespace SGCore
{
	namespace Haptics
	{
		class SGCORE_API ThumperCmd
		{
		protected:

			int Validate(int value);

			/// <summary> Minimum Force-Feedback Level </summary>
			static int thmpMin;
			/// <summary> Maximum Force-Feedback Level </summary>
			static int thmpMax;

		public:

			/// <summary> Thumper intensity, a level between 0 and 100. </summary>
			int magnitude;

			/// <summary> Create a new Thumper Command </summary>
			/// <param name="magn"></param>
			/// <returns></returns>
			ThumperCmd(int magn);

			/// <summary> Duplicate Thumper command </summary>
			/// <returns></returns>
			ThumperCmd Copy();

			/// <summary> A command that turns off all force feedback on the Sense Glove. </summary>
			static const ThumperCmd off;


		};
	}
}
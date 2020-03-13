// ----------------------------------------------------------------------------------
// Buzz motor command specific for the Sense Glove.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

#include "SG_FingerCmd.h"
#include "Fingers.h"

namespace SGCore
{
	namespace Haptics
	{
		/// <summary> A vibration command for the Sense Glove, with levels for each finger.  </summary>
		class SGCORE_API SG_BuzzCmd : public SG_FingerCmd
		{
		protected:

			//--------------------------------------------------------------------------------
			// Properties

			/// <summary> The minimum buzz motor level input </summary>
			static int buzzMin;
			/// <summary> The maximum buzz motor level input </summary>
			static int buzzMax;

			/// <summary> Ensure that an input values is places in between the minimum and maximum range. </summary>
			int Validate(int value) override;

		public:

			//--------------------------------------------------------------------------------
			// Construction

			/// <summary> Basic Constructor </summary>
			SG_BuzzCmd();

			/// <summary> Create a new buzz motor command, where each finger level is contained inside an array of size 5. </summary>
			SG_BuzzCmd(std::vector<int> buzzLevels);

			/// <summary> Create a new Buzz Motor command, indicating the intensity for each finger. </summary>
			SG_BuzzCmd(int thumb, int index, int middle, int ring, int pinky);

			/// <summary> Create a new Buzz Motor command, with only one finger being activated. </summary>
			SG_BuzzCmd(Finger finger, int buzzLevel);

			/// <summary> Basic Destructor </summary>
			~SG_BuzzCmd();

			//--------------------------------------------------------------------------------
			// Class Methods

			/// <summary> A command that turns off all vibration motors of the Sense Glove. </summary>
			static const SG_BuzzCmd off;

			/// <summary> Merge this command with another, taking the maximum value between the two. </summary>
			virtual SG_BuzzCmd Merge(SG_BuzzCmd other);

			/// <summary> Copy this Buzz Command into a new object. </summary>
			virtual SG_BuzzCmd Copy();

		};
	}
}

// ----------------------------------------------------------------------------------
// Force Feedback command specific for the Sense Glove.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include "Fingers.h"
#include "SG_FingerCmd.h"

namespace SGCore
{
	namespace Haptics
	{
		/// <summary> A Force-Feedback command for the Sense Glove, with levels for each finger. </summary>
		class SGCORE_API SG_FFBCmd : public SG_FingerCmd
		{

		protected:

			//--------------------------------------------------------------------------------
			// Properties

			/// <summary> Minimum Force-Feedback Level </summary>
			static int ffbMin;
			/// <summary> Maximum Force-Feedback Level </summary>
			static int ffbMax;

			/// <summary> Ensure that an input values is places in between the minimum and maximum range. </summary>
			int Validate(int value) override;


			//--------------------------------------------------------------------------------
			// Construction

			/// <summary> Empty constructor for internal initialization. </summary>
			SG_FFBCmd();

		public:

			/// <summary> Create a new Force-Feedback Command, with levels for each finger stored in an int[5] array. </summary>
			SG_FFBCmd(std::vector<int> ffbLevels);

			///<summary> Create a new Force-Feedback Command, with levels for each finger </summary>
			SG_FFBCmd(int thumb, int index, int middle, int ring, int pinky);

			/// <summary> Create a new Force-Feedback command, with only one finger being activated. </summary>
			SG_FFBCmd(Finger finger, int level);

			/// <summary> Basic Destructor </summary>
			~SG_FFBCmd();


			//--------------------------------------------------------------------------------
			// Class Methods

			/// <summary> Merge this finger command with another, taking the maximum value between the two. </summary>
			SG_FFBCmd Merge(SG_FFBCmd other);

			virtual SG_FFBCmd Copy();

			/// <summary> A command that turns off all force feedback on the Sense Glove. </summary>
			static const SG_FFBCmd off;

		};
	}
}
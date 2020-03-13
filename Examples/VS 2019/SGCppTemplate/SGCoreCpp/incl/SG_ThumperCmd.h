// ----------------------------------------------------------------------------------
// Enum indicating effects that can be played by the thumper, and its corresponding byte.
// @author: Max Lammers, effect selected by Michelle Corten
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

namespace SGCore
{
	namespace Haptics
	{
		/// <summary> A command to activate the Sense Glove Thumper Module, which is responsible for wrist feedback. </summary>
		enum SGCORE_API SG_ThumperCmd
		{
			None = 126,

			/// <summary> Turn off the thumper effects. </summary>
			TurnOff = 124,

			/// <summary> A 5-second long, constant vibration. </summary>
			Cue_Game_Over = 118,

			/// <summary> A double-click at 100% intensity. </summary>
			Button_Double_100 = 10,
			/// <summary> A double click at 60% intensity. </summary>
			Button_Double_60 = 11,

			/// <summary> Simulates an impact of the hand at 100% intensity. </summary>
			Impact_Thump_100 = 1,
			/// <summary> Simulates an impact of the hand at 30% intensity. </summary>
			Impact_Thump_30 = 3,
			/// <summary> Simulates an sharp impact of the hand at 40% intensity. </summary>
			Impact_Thump_10 = 6,

			/// <summary> A light vibration to cue the user that an object it picked up. 100% intensity. </summary>
			Object_Grasp_100 = 7,
			/// <summary> A light vibration to cue the user that an object it picked up. 60% intensity. </summary>
			Object_Grasp_60 = 8,
			/// <summary> A light vibration to cue the user that an object it picked up. 30% intensity. </summary>
			Object_Grasp_30 = 9
		};
	}
}

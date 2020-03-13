// ----------------------------------------------------------------------------------
// Enumerators to allow access to specific anatomical joints or movements of the 
// finger through the right index.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

namespace SGCore
{
	//--------------------------------------------------------------------------------------
	// Appendages

	/// <summary> One of the fingers on the hand </summary>
	enum SGCORE_API Finger
	{
		/// <summary> Responsible for our evolutionary success! </summary>
		Thumb,
		/// <summary> Used to point at what you want </summary>
		Index,
		/// <summary> On its own, this one is used to indicate frustration. </summary>
		Middle,
		/// <summary> If you like it then you should have put a ___ on it </summary>
		Ring,
		/// <summary> The little finger. </summary>
		Pinky
	};


	namespace Kinematics //One layer down since it will be mostly used in this namespace.
	{
		//--------------------------------------------------------------------------------------
		// Movements

		/// <summary> Anatomical movements of the thumb joints. </summary>
		enum SGCORE_API ThumbMovement
		{
			/// <summary> Pronation/Supination of the first finger joint. </summary>
			T_CMC_Twist = 0,
			/// <summary> Flexion of the first finger joint. </summary>
			T_CMC_Flex,
			/// <summary> Abduction of the first finger joint. </summary>
			T_CMC_Abd,
			/// <summary> Flexion of the second thumb joint. </summary>
			T_MCP_Flex,
			/// <summary> Flexion of the third thumb joint. </summary>
			T_IP_Flex
		};

		/// <summary> Anatomical movements of the finger joints. </summary>
		enum SGCORE_API FingerMovement
		{
			/// <summary> Flexion of the first finger joint. </summary>
			F_MCP_Flex = 0,
			/// <summary> Abduction of the first finger joint. </summary>
			F_MCP_Abd,
			/// <summary> Flexion of the second finger joint. </summary>
			F_PIP_Flex,
			/// <summary> Flexion of the third finger joint. </summary>
			F_DIP_Flex
		};
	}
}
// ----------------------------------------------------------------------------------
// Contains enumerators and classes to aid in Fino Deserialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"


namespace SGCore
{
	namespace Fino
	{
		namespace Parsing
		{

			/// <summary> Order of values as they come in from the Fino. </summary>
			enum Fino_CVar
			{
				ConstOpen = 0,
				ID,
				gloveVersion,
				FirmwareVersion,
				LeftRight,
				Functions,
				IMUCorrection,
				/// <summary> Utility value used in iteration / checking lengths </summary>
				AllC
			};

			/// <summary> Sensor data blocks </summary>
			enum FinoData
			{
				Sensors,
				IMU,
				All
			};
		}
	}
}
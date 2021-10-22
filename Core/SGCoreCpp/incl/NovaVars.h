// ----------------------------------------------------------------------------------
// Contains enumerators and classes to aid in Nova Deserialization.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"


namespace SGCore
{
	namespace Nova
	{
		namespace Parsing
		{

			/// <summary> Order of values as they come in from the Nova. </summary>
			enum Nova_CVar
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
			enum NovaData
			{
				Sensors,
				IMU,
				All
			};
		}
	}
}
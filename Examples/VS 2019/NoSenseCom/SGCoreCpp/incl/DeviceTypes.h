// ----------------------------------------------------------------------------------
// List of DeviceTypes that is included in multiple classes.
// Adding new Devices here will allow them to be detected by DeviceList, provided
// they have a class interface and Parse function in DeviceList.Deserialize.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

namespace SGCore
{
	/// <summary> Specific devices within the SGCore library </summary>
	enum struct SGCORE_API DeviceType
	{
		/// <summary> This device is not recognized by the Sense Glove API. </summary>
		UNKNOWN = -2,

		/// <summary> A Device that is in development, with direct access to sensor data and commands. </summary>
		BETADEVICE = -1,

		/// <summary> An exoskeleton glove that provides force- and haptic feedback. </summary>
		SENSEGLOVE = 0,

		/// <summary> A soft glove with basic tracking, as well as force- and Haptic Feedback. </summary>
		FINO = 2

	};
}
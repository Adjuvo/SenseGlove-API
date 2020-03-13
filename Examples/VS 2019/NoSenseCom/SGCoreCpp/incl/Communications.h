// ----------------------------------------------------------------------------------
// Contains internal enumerators and classes for raw byte communications
// with Sense Glove Devices.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"

namespace SGCore
{
	namespace Util
	{
		//--------------------------------------------------------------------------------------
		// Enumerators

		/// <summary> Indices to access DeviceList data in Shared Memory </summary>
		enum ListFormat
		{
			LF_Connected = 0,
			LF_PPS,
			LF_DeviceType,
			LF_cString,
			LF_Address,
			LF_ConnectType,
			LF_All
		};

		/// <summary> Indices to access Sensor Data in Shared Memory </summary>
		enum SensorFormat
		{
			SF_Sensors
		};


		//--------------------------------------------------------------------------------------
		// Bytes

		/// <summary> "Database" containing communications bytes and conversions. </summary>
		class Communications
		{

		public:

			/// <summary> Byte indicating the start of a new command. </summary>
			static const char cmdOpen;
			/// <summary> Byte indicating the end of a command. </summary>
			static const char cmdClose;

			/// <summary> Byte indicating the start of a new sensor data package. </summary>
			static const char senseOpen;
			/// <summary> Byte indicating the end of a sensor data package. </summary>
			static const char senseClose;

			///<summary> Denotes a block section of a DeviceList section. </summary>
			static const char listDelimiter;

			/// <summary> ':' - Used to split a set of different contant values into individual groups. </summary>
			static const char sectionDelimiter;
			/// <summary> ';' - Used to separate individual values </summary>
			static const char colDelimiter;
			/// <summary> '|' - Used to group a set of values, for example per finger. </summary>
			static const char rowDelimiter;

			/// <summary> Convert a value between 0..100 to a Sense Glove char/byte </summary>
			static char ToSGByte(int lvl);

		};
	}
}
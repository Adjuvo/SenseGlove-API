// ----------------------------------------------------------------------------------
// Diagnostics class used to send messages to developers from the Sense Glove API.
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>
#include <iostream>

namespace SGCore
{
	namespace Diagnostics
	{
		//--------------------------------------------------------------------------------------
		// Debug Utility

		/// <summary> Used to manage incoming debug levels </summary>
		enum struct SGCORE_API DebugLevel
		{
			/// <summary> No debug messages will be sent. </summary>
			DISABLED = 0,
			/// <summary> Send only messages if errors are caught. </summary>
			ERRORSONLY,
			/// <summary> Send messages from device Parsing. </summary>
			DEVICEPARSING,
			/// <summary> For those we have no place for yet. </summary>
			ALL
		};

		//--------------------------------------------------------------------------------------
		// Debug Class

		/// <summary> Used to send Debug Messages to the developer (and user) </summary>
		class SGCORE_API Debugger
		{

		public:

			/// <summary> The Default debug level for any application </summary>
			static const DebugLevel defaultLevel; //defined separately so we can say debugLevel = default

			/// <summary> The current debug level of the Debugger. </summary>
			static DebugLevel debugLevel;

			///<summary> Print a single message with an endline to the console. </summary>
			static void Log(const std::string msg, DebugLevel level);

		};
	}
}

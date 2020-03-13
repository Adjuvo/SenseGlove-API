// ----------------------------------------------------------------------------------
// Interface for SenseCom as a program
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"


namespace SGCore
{
	/// <summary> Interface for SenseCom the program. </summary>
	class SenseCom
	{
	public:
		static bool ProgramRunning() { return false; }
	};
}
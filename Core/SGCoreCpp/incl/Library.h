// ----------------------------------------------------------------------------
// Information about the SGCore C++ Library
// @author: Max Lammers
// ----------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>

namespace SGCore
{
	/// <summary> Provides information about this C++ Library </summary>
	class SGCORE_API Library
	{

	public:

		/// <summary> The version of this C++ Library in string representation </summary>
		/// <returns></returns>
		static std::string Version();

	};
}

// ----------------------------------------------------------------------------
// Information about the SGCore C++ Library
// @author: Max Lammers
// ----------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>

namespace SGCore
{
	enum SGCORE_API BackEndType
	{
		/// <summary> Back-end info comes from shared memory on the device. </summary>
		SharedMemory
	};


	/// <summary> Provides information about this C++ Library. </summary>
	class SGCORE_API Library
	{

	public:

		/// <summary> The version of this C++ Library in string representation </summary>
		/// <returns></returns>
		static std::string Version();

		/// <summary> Check wwhat back-end connections are used for this version of SGConnect  </summary>
		/// <returns></returns>
		static BackEndType GetBackEndType();

		/// <summary> Back-End version in string notation </summary>
		/// <returns></returns>
		static std::string BackEndVersion();

		/// <summary> If possible, check what version of SGConnect is paired with this API. </summary>
		/// <returns></returns>
		static std::string SGConnectVersion();

	};
}

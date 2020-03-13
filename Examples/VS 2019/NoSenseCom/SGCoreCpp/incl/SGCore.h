#pragma once

/*
Contains global defines, such as the import / export API

Should therefore be included in every class that is exported.
Perhaps global variables, like PI or 2PI, can be stored here..

@author Max Lammers
*/

#ifdef _WIN32

	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	// Windows Header Files:
	#define NOMINMAX
	//#include <windows.h> //removed since it may cause issues down the line.

	//also has guards against redeclaring SENSEGLOVE_API
	#ifdef SGCORE_EXPORTS  
		#ifndef SGCORE_API
			#define SGCORE_API __declspec(dllexport)   
		#endif
	#else  
		#ifndef SGCORE_API
			#define SGCORE_API __declspec(dllimport)   
		#endif
	#endif
#else
	#define SGCORE_API
#endif


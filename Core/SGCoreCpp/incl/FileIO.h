// ----------------------------------------------------------------------------------
// File Input/output handling
// @author: Max Lammers
// ----------------------------------------------------------------------------------

#pragma once

#include "SGCore.h"
#include <string>
#include <vector>

namespace SGCore
{
	namespace Util
	{
		class SGCORE_API FileIO
		{

        public:

            /// <summary> Attempt to read all lines from a file and place them in the string[]. Returns true if succesful. If unable to open the file, the string[] will be empty.</summary>
            /// <param name="filePath"></param>
            /// <param name="lines"></param>
            /// <returns></returns>
			static bool ReadTxtFile(std::string& filePath, std::vector<std::string>& lines);

            /// <summary> Attempt to save a string[] to a filename within a desired directory. Returns true if succesful. </summary>
            /// <remarks> Directory is added as a separate variable so we can more easily check for its existence. </remarks>
            /// <param name="directory"></param>
            /// <param name="fileName"></param>
            /// <param name="contents"></param>
            /// <param name="append"></param>
            /// <returns></returns>
			static bool SaveTxtFile(std::string& directory, std::string& fileName, std::vector<std::string>& contents, bool append = false);

            /// <summary> Creates a new directory. Returns  false if it already existed. </summary>
            /// <param name="dir"></param>
            /// <returns></returns>
            static bool CreateFullDirectory(std::string& dir);

            /// <summary> Returns true if the directory exists </summary>
            /// <param name="dir"></param>
            /// <returns></returns>
            static bool DirectoryExists(std::string& dir);

            /// <summary> Returns true if this file exists </summary>
            /// <param name="filePath"></param>
            /// <returns></returns>
            static bool FileExists(std::string& filePath);

            /// <summary> STUB - Gets the working directory of the current process. </summary>
            /// <returns></returns>
            static std::string GetWorkingDirectory();

            /// <summary> Get the Path to MyDocuments, but without '\\' at the nnd </summary>
            /// <returns></returns>
            static std::string GetMyDocumentsPath();
		};

	}
}

#pragma once
#include "SGCore.h"
#include <string>

namespace SGCore
{
	class SGCORE_API SenseCom
	{
    private:

        static const std::string iniFile;

        static std::string GetIniDir();

    public:

        /// <summary> Registers current process as the latest SenseCom build. </summary>
        /// <returns></returns>
        static bool RegisterExe();

        /// <summary> Register a particular path as the SenseGlove executable location </summary>
        /// <param name="exePath"></param>
        /// <returns></returns>
        static bool RegisterExe(std::string exePath);

        /// <summary> Retrieve the location of SenseGlove executable </summary>
        /// <param name="exePath"></param>
        /// <returns></returns>
        static bool GetExePath(std::string exePath);

        /// <summary> Retruns true if SenseCom scanning is active. </summary>
        /// <returns></returns>
        static bool ScanningActive();

        /// <summary> Returns the directory of the current process </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        static bool GetCurrentExeDir(std::string& path);

        /// <summary> Force-starts the SenseCom application if it is active on the system </summary>
        /// <returns></returns>
        static bool StartupSenseCom();
	};
}

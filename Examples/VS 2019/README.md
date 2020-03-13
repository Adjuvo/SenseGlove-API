# Visual Studio Instructions
How to add Sense Glove Core to your VS C++ project on Windows:

Refer to the directory where the Windows Cpp API for Sense Glove is located as *[SG_C++Dir]*

navigate to your project properties. Set your Configuration to "All Configurations" and your Platform to "All Platforms"

C++ > General > Additional Include Directories: "*[SG_C++Dir]*\incl"
Should point to the "incl" folder of the Sense Glove C++ folder.

Linker > General > Additional Library Directories > "*[SG_C++Dir]*\lib\Win\$(PlatformTarget)\$(ConfigurationName)"

Linker > Input > Additional Dependencies > "SGCore.lib"

Build Events > Post Build Events > "xcopy /y /d "*[SG_C++Dir]*\lib\Win\$(PlatformTarget)\$(ConfigurationName)\SGCore.dll" "$(OutDir)""
Copies Sense Glove DLL to build folder automatically.

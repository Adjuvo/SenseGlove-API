// Application demonstrating the main funtion(s) of the SGConnect library.

#include <iostream>		//output to console
#include "SGConnect.h"	//Access SGConnect functions.

int main()
{
	std::cout << "Testing " << SGConnect::GetLibraryVersion() << std::endl;
	std::cout << "=========================================" << std::endl;

	SGConnect::SetDebugLevel(0);
	bool scanActive = SGConnect::ScanningActive();
	if (!scanActive)
	{
		std::cout << "We call SGConnect::Init() to startup a background process, which will begin scanning for SenseGlove devices." << std::endl;
		int initCode = SGConnect::Init();
		if (initCode > 0)
		{
			std::cout << "Succesfully initialized background process: (InitCode = " << std::to_string(initCode) << ")" << std::endl;
			std::cout << "This process will begin connecting to ports that should belong to SenseGlove devices." << std::endl;
			std::cout << "It will take a few seconds before the devices appear to the SenseGlove API, especially when using Bluetooth devices." << std::endl;
			std::cout << "Below, you will see debug messages appear from the background process. Press return when you are ready to finish" << std::endl;
			std::cout << "" << std::endl;
			while (std::cin.get() != '\n') {} //Wait for the user to confirm before exiting.
			std::cout << "" << std::endl;


			std::cout << "Showing the list at the end:" << std::endl;
			std::cout << SGConnect::GetConnectionStates() << std::endl << std::endl;

			//If you have access to SGCoreCpp or SGCoreCs, you can interface with SenseGlove devices

			int disposeCode = SGConnect::Dispose();
			if (disposeCode > 0)
			{
				std::cout << "Succesfully cleaned up SGConnect resources: (DisposeCode = " << std::to_string(disposeCode) << ")" << std::endl;
			}
			else
			{
				std::cout << "Unable to properly dispose of SGConnect resources: (DisposeCode = " << std::to_string(disposeCode) << ")." << std::endl;
				std::cout << "Fortunately, closing this process will cause them to go out of scope and be destroyed either way." << std::endl;
			}
		}
		else
		{
			std::cout << "Oddly enough, we could not initialize the SGConnect library. (InitCode = " << std::to_string(initCode) << ")" << std::endl;
			std::cout << "Please close this program, and try again." << std::endl;
		}
	}
	else
	{
		std::cout << "A SenseGlove scanning process is already running (ScanState " << std::to_string(SGConnect::ScanningState()) << " > 0)." << std::endl;
		std::cout << "Seeing as we've just started up, it can't possibly be this process that did it." << std::endl;
		std::cout << "It is safe to call SGConnect::Init() even if this is the case, but no new process will be started." << std::endl;
		int initCode = SGConnect::Init();
		std::cout << "The SGConnect::Init() will return 0, to let us know no Initialization was done: " << std::to_string(initCode) << std::endl;
		std::cout << std::endl;
		std::cout << "We can call SGConnect::Dispose() safely, but this will not stop the original process." << std::endl;
		int disposeVal = SGConnect::Dispose();
		std::cout << "The SGConnect::Dispose() will return 0, to let us know nothing was Disposed of: " << std::to_string(disposeVal) << std::endl;
		std::cout << "If you wish to dispose of the already running process, you should call SGConnect::Dispose() from the program that originally called SGConnect::Init()" << std::endl;
	}

	std::cout << "=========================================" << std::endl;
	std::cout << "Done. Press Return to exit." << std::endl;
	while (std::cin.get() != '\n') {} //Wait for the user to confirm before exiting.
}
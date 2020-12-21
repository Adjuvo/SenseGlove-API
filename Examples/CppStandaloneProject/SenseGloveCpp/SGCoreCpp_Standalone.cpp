// SGCoreCpp_Standalone.cpp : Example to show how to build a SenseGlove project that's independent of the SenseCom program.
//

#include <iostream>
#include "SGConnect.h"
#include "DeviceList.h"
#include "SenseGlove.h"
#include "Library.h"

#include <thread>
#include <chrono> //wait untill we find SenseGloves

int main()
{
	std::cout << "Standalone Communications using " << SGConnect::GetLibraryVersion() << " and " << SGCore::Library::Version() << std::endl;
	std::cout << "============================================================================================" << std::endl << std::endl;

	std::cout << "The SGConnect library allows us to initialize and detect SenseGloves and other SenseGlove Devices" << std::endl;

	//---------------------------------------------------------------------------
	// SGConnect Initalization - Parts taken from the SGConnect example code.

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
			std::cout << "Below, you will see debug messages appear from the background process. Press return when you see one appear, or when you're ready to end." << std::endl;
			std::cout << "" << std::endl;
			while (std::cin.get() != '\n') {} //Wait for the user to confirm before continuing.
			std::cout << "" << std::endl;
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
		std::cout << "The SGConnect::Init() will return 0, to let us know no Initialization was done: " << std::to_string(initCode) << std::endl << std::endl;
		std::cout << std::endl;
		
	}


	//---------------------------------------------------------------------------
	// SGCoreCpp  - Parts taken from the SGCoreCpp example code.


	SGCore::SG::SenseGlove testGlove;
	if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
	{
		std::cout << "Found " << testGlove.ToString() << "!" << std::endl;

		testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd(0, 80, 0, 0, 0)); //vibrate the index fingerat 80% intensity.
		std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //vibrating for for 1s.

		testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd::off); //turn off all Buzz Motors.
		testGlove.StopHaptics();
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); //wait for 10ms.

		SGCore::SG::SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
		std::cout << std::endl;
		std::cout << model.ToString(true) << std::endl; //Log some basic information to the user. (true indicates a short notation is desired)
	}
	else
	{
		std::cout << "No sense gloves connected to the system. Ensure the USB connection is secure, then try again." << std::endl;
	}

	//---------------------------------------------------------------------------
	// SGConnect Cleanup - Parts taken from the SGConnect example code.
	
	std::cout << std::endl;
	if (!scanActive)
	{
		int disposeCode = SGConnect::Dispose();
		if (disposeCode > 0)
		{
			std::cout << "Succesfully cleaned up SGConnect resources: (DisposeCode = " << std::to_string(disposeCode) << ")" << std::endl;
			std::cout << "It's now safe to exit the program. Press return to end." << std::endl;
		}
		else
		{
			std::cout << "Unable to properly dispose of SGConnect resources: (DisposeCode = " << std::to_string(disposeCode) << ")." << std::endl;
			std::cout << "Fortunately, closing this process will cause them to go out of scope and be destroyed either way." << std::endl;
		}
	}
	else
	{
		std::cout << "Since this process did not start SGConnect, we don't need to clean anything up." << std::endl;
		std::cout << "We can call SGConnect::Dispose() safely, but this will not stop the original process." << std::endl;
		int disposeVal = SGConnect::Dispose();
		std::cout << "The SGConnect::Dispose() will return 0, to let us know nothing was Disposed of: " << std::to_string(disposeVal) << std::endl;
		std::cout << "If you wish to dispose of the already running process, you should call SGConnect::Dispose() from the program that originally called SGConnect::Init()" << std::endl;
	}

	while (std::cin.get() != '\n') {} //Wait for the user to confirm before exiting.


	//// SGConnect Initialization
	//bool alreadyRunning = SGConnect::ScanningActive(); //this function tells us if there is already a scanner active.
	//if (alreadyRunning)
	//{
	//	std::cout << "Another program is already scanning, so we will skip the init method right now." << std::endl;
	//}
	//else
	//{
	//	std::cout << "Initializing SenseGlove Communications." << std::endl;
	//	SGConnect::Init();
	//	std::cout << "Done!" << std::endl;
	//}

	//std::cout << "Now that we have scanning up and running, we should wait for the Sense Glove to connect." << std::endl;
	//system("pause");
	//std::cout << std::endl;
	//int attempts = 0;
	//SGCore::SG::SenseGlove testGlove;
	//bool gloveFound = false;

	//do
	//{
	//	gloveFound = SGCore::SG::SenseGlove::GetSenseGlove(testGlove);
	//	attempts++;
	//	if (!gloveFound)
	//	{
	//		std::cout << "Checking for SenseGloves..." << std::endl;
	//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//	}
	//} while (!gloveFound && attempts < 10);

	//if (gloveFound)
	//{
	//	std::cout << "Found a Device! Lets begin" << std::endl;

	//	//Begin Section of SGCPP
	//	std::cout << "Activating " << testGlove.ToString() << std::endl;

	//	testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd(0, 80, 0, 0, 0)); //vibrate the index fingerat 80% intensity.
	//	std::this_thread::sleep_for(std::chrono::milliseconds(200)); //vibrating for for 200ms.

	//	testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd::off); //turn off all Buzz Motors.
	//	std::this_thread::sleep_for(std::chrono::milliseconds(10)); //wait for 10ms.

	//	SGCore::SG::SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
	//	std::cout << std::endl;
	//	std::cout << model.ToString(true) << std::endl; //Log some basic information to the user. (true indicates a short notation is desired)

	//	//Retrieving Sensor Data (raw). The lowest level data available
	//	SGCore::SG::SG_SensorData sensorData;
	//	if (testGlove.GetSensorData(sensorData)) //if GetSensorData is true, we have sucesfully recieved data
	//	{
	//		std::cout << std::endl;
	//		std::cout << sensorData.ToString() << std::endl;
	//	}

	//	//Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
	//	SGCore::SG::SG_GlovePose glovePose;
	//	if (testGlove.GetGlovePose(glovePose))
	//	{
	//		//As an example, lets calculate fingertip positions.

	//		//If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
	//		SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
	//		std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

	//		std::cout << std::endl;
	//		for (int f = 0; f < tipPositions.size(); f++)
	//			std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.

	//		float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
	//		std::cout << "The distance between thumb and index finger is " << std::to_string(dThumbIndex) << "mm." << std::endl;
	//	}

	//	//End Section of SGCPP

	//}
	//else
	//{
	//	std::cout << "Still no SenseGloves found. Please try again" << std::endl;
	//}

	//std::cout << std::endl << "Press any key to end. While SGConnect's resources are disposed of during GC, "
	//	<< "it is good practice to dispose of them ouselves if we started them up." << std::endl;
	//system("pause");

	//// SGConnect Dispose
	//if (!alreadyRunning)
	//{
	//	std::cout << std::endl << "This program initialized the SenseGlove Communications, so we should properly end them." << std::endl;
	//	std::cout << "Disposing..." << std::endl;
	//	SGConnect::Dispose();
	//	std::cout << "Done!" << std::endl;
	//}
}
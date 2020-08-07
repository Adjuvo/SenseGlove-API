// NoSenseCom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SGConnect.h"
#include "DeviceList.h"
#include "SenseGlove.h"

#include <thread>
#include <chrono> //wait untill we find SenseGloves

int main()
{
	std::cout << "SGConnect allows us to initialize and detect SenseGloves and other SenseGlove Devices" << std::endl << std::endl;
	
	// SGConnect Initialization
	bool alreadyRunning = SGConnect::ScanningActive(); //this function tells us if there is already a scanner active.
	if (alreadyRunning)
	{
		std::cout << "Another program is already scanning, so we will skip the init method right now." << std::endl;
	}
	else
	{
		std::cout << "Initializing SenseGlove Communications." << std::endl;
		SGConnect::Init();
		std::cout << "Done!" << std::endl;
	}

	std::cout << "Now that we have scanning up and running, we should wait for the Sense Glove to connect." << std::endl;
	system("pause");
	std::cout << std::endl;
	int attempts = 0;
	SGCore::SG::SenseGlove testGlove;
	bool gloveFound = false;

	do
	{
		gloveFound = SGCore::SG::SenseGlove::GetSenseGlove(testGlove);
		attempts++;
		if (!gloveFound)
		{
			std::cout << "Checking for SenseGloves..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	} while (!gloveFound && attempts < 10);

	if (gloveFound)
	{
		std::cout << "Found a Device! Lets begin" << std::endl;

		//Begin Section of SGCPP
		std::cout << "Activating " << testGlove.ToString() << std::endl;

		testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd(0, 80, 0, 0, 0)); //vibrate the index fingerat 80% intensity.
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); //vibrating for for 200ms.

		testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd::off); //turn off all Buzz Motors.
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); //wait for 10ms.

		SGCore::SG::SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
		std::cout << std::endl;
		std::cout << model.ToString(true) << std::endl; //Log some basic information to the user. (true indicates a short notation is desired)

		//Retrieving Sensor Data (raw). The lowest level data available
		SGCore::SG::SG_SensorData sensorData;
		if (testGlove.GetSensorData(sensorData)) //if GetSensorData is true, we have sucesfully recieved data
		{
			std::cout << std::endl;
			std::cout << sensorData.ToString() << std::endl;
		}

		//Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
		SGCore::SG::SG_GlovePose glovePose;
		if (testGlove.GetGlovePose(glovePose))
		{
			//As an example, lets calculate fingertip positions.

			//If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
			SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
			std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

			std::cout << std::endl;
			for (int f = 0; f < tipPositions.size(); f++)
				std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.

			float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
			std::cout << "The distance between thumb and index finger is " << std::to_string(dThumbIndex) << "mm." << std::endl;
		}

		//End Section of SGCPP

	}
	else
	{
		std::cout << "Still no SenseGloves found. Please try again" << std::endl;
	}

	std::cout << std::endl << "Press any key to end. While SGConnect's resources are disposed of during GC, "
		<< "it is good practice to dispose of them ouselves if we started them up." << std::endl;
	system("pause");

	// SGConnect Dispose
	if (!alreadyRunning)
	{
		std::cout << std::endl << "This program initialized the SenseGlove Communications, so we should properly end them." << std::endl;
		std::cout << "Disposing..." << std::endl;
		SGConnect::Dispose();
		std::cout << "Done!" << std::endl;
	}
}

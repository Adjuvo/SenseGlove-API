// WinCppTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>         // std::chrono::seconds

#include "DeviceList.h"
#include "SenseGlove.h"

int main()
{
	std::cout << "SGCore.dll internal test program" << std::endl;
	std::cout << "=======================================" << std::endl;

	if (SGCore::DeviceList::SenseCommRunning()) //Returns true if SenseComm is running.
	{
		SGCore::SG::SenseGlove testGlove;
		//GetSenseGlove retrieves the first (connected) Sense Glove it can find. Returns true if one can be found. Additional search parameters can be used.
		if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) 
		{
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
				SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.
				std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

				std::cout << std::endl;
				for (int f = 0; f < tipPositions.size(); f++)
					std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.

				float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
				std::cout << "The distance between thumb and index finger is " << std::to_string(dThumbIndex) << "mm." << std::endl;

				//HandPose Example

				SGCore::HandPose handPose;
				if (testGlove.GetHandPose(handModel, handProfile, handPose))
				{
					std::cout << std::endl;
					std::cout << "Calculated Hand Pose: " << std::endl << handPose.ToString() << std::endl;
				}
				else
				{
					std::cout << "Could not retrieve a hand pose" << std::endl;
				}
			}

			//Serialization example
			std::cout << std::endl;
			std::cout << "-------------------------------------------" << std::endl;
			std::cout << std::endl;
			std::cout << "Serialization Example: " << std::endl;

			//we take a default hand pose.
			bool isRight = true;
			SGCore::HandPose testPose = SGCore::HandPose::DefaultIdle(isRight);
			std::string serialized = testPose.Serialize();
			std::cout << "Serializing & Deserializing default HandPose for the " << (isRight ? "right" : "left") << " hand:" << std::endl << testPose.ToString() << std::endl;

			//std::cout << std::endl << serialized << std::endl; //prints a big string
			SGCore::HandPose deserialPose = SGCore::HandPose::Deserialize(serialized);
			if (!testPose.Equals(deserialPose))
			{
				std::cout << "The Deserialized pose does not match. There might be an error somewhere!" << std::endl;
			}
		}
		else
			std::cout << "No sense gloves connected to the system. Ensure the USB connection is secure, then try again." << std::endl;
	}
	else
	{
		std::cout << "SenseComm is not running. Please run SenseComm, then try again." << std::endl;
	}


	std::cout << "=======================================" << std::endl;
	std::cout << "Program Finished." << std::endl;
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

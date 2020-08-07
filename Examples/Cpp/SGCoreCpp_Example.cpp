// CoreClient.cpp : Defines the entry point for the console application.
#include <iostream>

#include <thread>
#include <chrono>         // std::chrono::seconds

#include "DeviceList.h"
#include "SenseGlove.h"
#include "SG_SensorData.h"
#include "BasicHandModel.h"
#include "HandPose.h"


int main()
{

	//SGCore::Diagnostics::Debugger::debugLevel = SGCore::Diagnostics::DebugLevel::ALL;

	std::cout << "Testing Sense Glove C++ Core Library" << std::endl;
	std::cout << "=======================================" << std::endl;

	if (SGCore::DeviceList::SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
	{
		SGCore::SG::SenseGlove testGlove;
		if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
		{
			std::cout << "Activating " << testGlove.ToString() << " on key press." << std::endl;
			system("pause");

			testGlove.SendHaptics( SGCore::Haptics::SG_BuzzCmd(0, 80, 0, 0, 0) ); //vibrate the index fingerat 80% intensity.
			std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //vibrating for for 200ms.

			testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd::off); //turn off all Buzz Motors.
			testGlove.StopHaptics();
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
		std::cout << "SenseComm is not running. Please start it and try again." << std::endl;

	std::cout << "=======================================" << std::endl;
	std::cout << "Press any key to exit." << std::endl;
	system("pause");
}


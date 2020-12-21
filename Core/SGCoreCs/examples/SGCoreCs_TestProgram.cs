/*
 * Example code on how to interface with the SenseGlove.
 * This is the source code for the program in the SGCore/test folder.
 */


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using SGCore;
using SGCore.SG; //namespace for all things SenseGlove (hardware)
using SGCore.Haptics; //buzzCmds
using SGCore.Kinematics; //buzzCmds


namespace CsCoreClient
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Testing " + SGCore.Library.Version);
			Console.WriteLine("=======================================");

			if (!SGCore.DeviceList.SenseCommRunning())
			{
				SGCore.SenseCom.StartupSenseCom(); //relatively new C# function only; starts up SenseCom if it was launched at least once.
				System.Threading.Thread.Sleep(3000);
			}

			if (SGCore.DeviceList.SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
			{
				SGCore.SG.SenseGlove testGlove;
				if (SGCore.SG.SenseGlove.GetSenseGlove(out testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
				{
					Console.WriteLine("Activating " + testGlove.ToString() + " on key press.");
					Console.ReadKey();

					testGlove.SendHaptics(new SGCore.Haptics.SG_BuzzCmd(0, 80, 0, 0, 0)); //vibrate the index fingerat 80% intensity.

					System.Threading.Thread.Sleep(1000); //vibrating for for 1000ms.

					testGlove.SendHaptics(SGCore.Haptics.SG_BuzzCmd.Off); //turn off all Buzz Motors.
					testGlove.StopHaptics();
					System.Threading.Thread.Sleep(10); //wait for 10ms, just for stabilization

					SGCore.SG.SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
					Console.WriteLine();
					Console.WriteLine(model.ToString(true)); //Log some basic information to the user. (true indicates a short notation is desired)

					//Retrieving Sensor Data (raw). The lowest level data available
					SGCore.SG.SG_SensorData sensorData;
					if (testGlove.GetSensorData(out sensorData)) //if GetSensorData is true, we have sucesfully recieved data
					{
						Console.WriteLine();
						Console.WriteLine(sensorData.ToString());
					}

					//Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
					SGCore.SG.SG_GlovePose glovePose;
					if (testGlove.GetGlovePose(out glovePose))
					{
						//As an example, lets calculate fingertip positions.

						//If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
						SGCore.SG.SG_HandProfile handProfile = SGCore.SG.SG_HandProfile.Default(testGlove.IsRight()); //create a default profile, either left or right.
						SGCore.Kinematics.BasicHandModel handModel = SGCore.Kinematics.BasicHandModel.Default(testGlove.IsRight()); //create a default profile, either left or right.
						SGCore.Kinematics.Vect3D[] tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

						Console.WriteLine();
						for (int f = 0; f < tipPositions.Length; f++)
							Console.WriteLine(((SGCore.Finger)f).ToString() + ": " + tipPositions[f].ToString() ); //writes "thumb: ", "index: " etc.

						float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
						Console.WriteLine("The distance between thumb and index finger is " + dThumbIndex + "mm.");

						//HandPose Example

						SGCore.HandPose handPose;
						if (testGlove.GetHandPose(handModel, handProfile, out handPose))
						{
							Console.WriteLine();
							Console.WriteLine("Calculated Hand Pose: \r\n" + handPose.ToString());
						}
						else
						{
							Console.WriteLine("Could not retrieve a hand pose");
						}
					}

					//Serialization example
					Console.WriteLine();
					Console.WriteLine("-------------------------------------------");
					Console.WriteLine();
					Console.WriteLine("Serialization Example: ");

					//we take a default hand pose.
					bool isRight = true;
					SGCore.HandPose testPose = SGCore.HandPose.DefaultIdle(isRight);
					string serialized = testPose.Serialize();
					Console.WriteLine("Serializing & Deserializing default HandPose for the " + (isRight ? "right" : "left") + " hand:\r\n" + testPose.ToString());

					//Console.WriteLine();+ serialized + std.endl; //prints a big string
					SGCore.HandPose deserialPose = SGCore.HandPose.Deserialize(serialized);
					if (!testPose.Equals(deserialPose))
					{
						Console.WriteLine("The Deserialized pose does not match. There might be an error somewhere!");
					}
				}
				else
				{
					Console.WriteLine("No sense gloves connected to the system. Ensure the USB connection is secure, then try again.");
				}
			}
			else
			{
				Console.WriteLine("SenseComm is not running. Please start it and try again. If trying to launch it via SGCore.SenseCom.StartupSenseCom(), ensure you've stated it manually once before.");
			}

			Console.WriteLine("=======================================");
			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();
		}
	}
}

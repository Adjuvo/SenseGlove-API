#define SOCKET_MODE

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
using SGCore.Util; //buzzCmds
using SGCore.Nova; //buzzCmds


namespace CsCoreClient
{
	class Program
	{
		//static void RunBase()
		static void Main(string[] args)
		{
			Console.Write("Testing " + SGCore.Library.Version + " compiled for " + SGCore.Library.BackEndVersion());
			if (SGCore.Library.GetBackEndType() == SGCore.Library.BackEndType.SharedMemory)
            {
				Console.Write(" using " + SGCore.Library.SGConnectVersion);
            }
			Console.WriteLine("");
			Console.WriteLine("=======================================");

			SGCore.Diagnostics.Debugger.DebugLevel = SGCore.Diagnostics.DebugLevel.ErrorsOnly;

			if (SGCore.SGConnect.ScanningActive())
            {
				Console.WriteLine("Grabbing a glove to test...");
				SGCore.HapticGlove testGlove;
				if (SGCore.HapticGlove.GetGlove(out testGlove)) //if this function returns true, we found a connected glove, and testGlove is assigned.
				{
					bool rightHanded = testGlove.IsRight();
					SGCore.DeviceType deviceType = testGlove.GetDeviceType();

					Console.WriteLine("We've found a " + (rightHanded ? "right" : "left") + "-handed " + (deviceType == DeviceType.NOVA ? "Nova" : "Sense") + " Glove!");
					Console.WriteLine("Press a key to make it vibrate!");
					Console.ReadKey();
					
					Console.WriteLine();
					if (deviceType == DeviceType.NOVA) { testGlove.SendHaptics(new ThumperCmd(80)); } //vibrate wrist at 80%
					else if (deviceType == DeviceType.SENSEGLOVE) { testGlove.SendHaptics(new SG_BuzzCmd(Finger.Index, 100)); } //vibrate index finger at 100%
					System.Threading.Thread.Sleep(500); //vibrate for 500ms
					testGlove.StopHaptics(); //turn off vibratin

					Console.WriteLine("Press a key to access tracking data");
					Console.ReadKey();

					//Generate a default profile for now.
					SGCore.HandProfile defaultProfile = HandProfile.Default(rightHanded);

					if (deviceType == DeviceType.NOVA)
					{
						NovaGlove nova = (NovaGlove)testGlove;
						Console.WriteLine("Since this is a Nova Glove, calibration is required. I'll instead grab some Sensor Data");
						Nova_SensorData novaData;
						if ( nova.GetSensorData(out novaData) )
                        {
							Console.WriteLine(novaData.ToString());
						}
						else { Console.WriteLine("Something went wrong while retrieving data...");  }
					}
					else
                    {
						Console.WriteLine("Since this is a SenseGlove, no calibration is required.");
						HandPose handPose;
						if (testGlove.GetHandPose(defaultProfile, out handPose))
                        {
							Console.WriteLine(handPose.ToString());
                        }
						else { Console.WriteLine("Something went wrong while retrieving data..."); }
					}
					
				}
				else
                {
					Console.WriteLine("There are no Haptic Gloves connected to your system. Please ensure your device is paired or connected via USB.");
                }
            }
			else
            {
				Console.WriteLine("SenseCom process is not running. Please start it and try again!");
            }

			Console.WriteLine("=======================================");
			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();
		}
	}
}

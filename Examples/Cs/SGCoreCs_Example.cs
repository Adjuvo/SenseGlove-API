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
            Console.WriteLine("Testing Sense Glove C# Core Library");
            Console.WriteLine("=======================================");

            if (DeviceList.SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
            {
                SenseGlove testGlove;
                if (SenseGlove.GetSenseGlove(out testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
                {
                    Console.WriteLine("Activating " + testGlove.ToString() + " on key press.");
                    Console.ReadKey();

                    //std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //vibrating for for 200ms.
                    testGlove.SendHaptics(new SG_BuzzCmd(0, 80, 0, 0, 0)); //vibrate the index fingerat 80% intensity.
                    System.Threading.Thread.Sleep(1000);
                    testGlove.SendHaptics(SG_BuzzCmd.Off); //turn off all Buzz Motors.
                    System.Threading.Thread.Sleep(10);

                    SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
                    Console.WriteLine("");
                    Console.WriteLine(model.ToString(true)); //Log some basic information to the user. (true indicates a short notation is desired)

                    //Retrieving Sensor Data (raw). The lowest level data available
                    SG_SensorData sensorData;
                    if (testGlove.GetSensorData(out sensorData)) //if GetSensorData is true, we have sucesfully recieved data
                    {
                        Console.WriteLine("");
                        Console.WriteLine(sensorData.ToString());
                    }

                    //Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
                    SG_GlovePose glovePose;
                    if (testGlove.GetGlovePose(out glovePose))
                    {
                        //As an example, lets calculate fingertip positions.

                        //If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
                        SG_HandProfile handProfile = SG_HandProfile.Default(testGlove.IsRight()); //create a default profile, either left or right.
                        Vect3D[] tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

                        Console.WriteLine("");
                        Console.WriteLine("Fingertip positions relative to Wrist:");
                        for (int f = 0; f < tipPositions.Length; f++)
                            Console.WriteLine(((SGCore.Finger)f).ToString() + ": " + tipPositions[f].ToString()); //writes "thumb: ", "index: " etc.

                        float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
                        Console.WriteLine("The distance between thumb and index finger is " + dThumbIndex + "mm.");
                    }
                }
                else
                    Console.WriteLine("No sense gloves connected to the system. Ensure the USB connection is secure, then try again.");
            }
            else
                Console.WriteLine("SenseComm is not running. Please start it and try again.");

            Console.WriteLine("=======================================");
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}

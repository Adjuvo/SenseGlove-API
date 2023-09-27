/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Management / Node to which all CV Hand Data can be pushed. Other runtimes can access said data through here.
 * Intended use: CV device publishes data, we add it to the list(s) here, where it is processed. It is then accessible to other applications.
 *
 * 
/// <remarks>  I'm going to assume for now that we only use one device subtype at the same time;e.g. 2x Nova 1.1, or 2x Nova 2.0. But never 1.1 & 2.0 at the same time. </remarks>
 */


#pragma once

#include <memory>

#include "Platform.hpp"
#include "DeviceTypes.hpp"

namespace SGCore
{
    namespace CV
    {
        /// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
        class SGCORE_API CVHandTrackingData;

        /// <summary> CV Data processed into joint angles and wrist location. </summary>
        class SGCORE_API CVProcessedHandData;

        /// <summary> An abstract layer with which to interface for CV models, specifically for hand and finger tracking. </summary>
        class SGCORE_API CVHandLayer;
    }
}// namespace SGCore


/// <summary> An abstract layer with which to interface for CV models, specifically for hand and finger tracking. </summary>
class SGCORE_API SGCore::CV::CVHandLayer
{
    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;

public:
    CVHandLayer() = delete;
    virtual ~CVHandLayer() = delete;


    
	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	// Time Management


	/// <summary> Retrieve the current simulation time - used for generating timestamps. </summary>
	/// <returns></returns>
	static float GetSimulationTime();


	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	// Posting Data (From simulations / threads)

protected:

	/// <summary> Returns the index within smoothedData that matches the handednedd / glove / subtype combination of a particular output. </summary>
	/// <param name="cvData"></param>
	/// <returns></returns>
    static int32_t DataIndex(const CVHandTrackingData& cvData);


	/// <summary> Returns the index within smoothedData that matches the handednedd / glove / subtype combination. </summary>
	/// <param name="rightHand"></param>
	/// <param name="devType"></param>
	/// <param name="hwVer"></param>
	/// <returns></returns>
    static int32_t DataIndex(const bool rightHand, const EDeviceType devType, const std::string& hwVer);


public:

	/// <summary> Post new CV output once it becomes available. Will be used to calculate smoothed Data </summary>
	/// <param name="cvData"></param>
    static void PostHandData(CVHandTrackingData& cvData);

	/// <summary> Clear all Data from memory. Useful if you're restarting. </summary>
    static void ClearCVData();

	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	// Data Access - From the simulation

public:

	/// <summary> Returns true if data is available for a hand of a specific handedness / DeviceType / hwVersion </summary>
	/// <param name="rightHand"></param>
	/// <param name="deviceType"></param>
	/// <param name="hwVersion"></param>
	/// <returns></returns>
	static bool PoseAvailable(bool rightHand, SGCore::EDeviceType deviceType, const std::string& hwVersion);


	/// <summary> Returns true if  the data was succesfully gathered. Simulation time is gathered GetSimulationTime(). </summary>
	/// <param name="rightHand"></param>
	/// <param name="deviceType"></param>
	/// <param name="hwVersion"></param>
	/// <param name="handData"></param>
	/// <param name="clampValues"></param>
	/// <returns></returns>
    static bool TryGetPose(bool rightHand, SGCore::EDeviceType deviceType, const std::string& hwVersion, CVProcessedHandData& out_handData, bool clampValues = true);


	/// <summary> Returns true if  the data was succesfully grathered for a custom timeStamp. </summary>
	/// <param name="currentTime"></param>
	/// <param name="rightHand"></param>
	/// <param name="deviceType"></param>
	/// <param name="hwVersion"></param>
	/// <param name="handData"></param>
	/// <param name="clampValues"></param>
	/// <returns></returns>
    static bool TryGetPose(float currentTime, bool rightHand, SGCore::EDeviceType deviceType, const std::string& hwVersion, CVProcessedHandData& out_handData, bool clampValues = true);


};

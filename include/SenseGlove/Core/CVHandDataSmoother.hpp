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
 *  Keeps track of a small history of CVHandDataPoints to compensate for low(er) update rates. For example, running a VR simulation at 90Hz while sampling at 30.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

#include "DeviceTypes.hpp"

namespace SGCore
{
    namespace CV
    {

        /// <summary> The way handPoses are smoothed in this class. </summary>
        enum class SGCORE_API ESmoothingMethod : uint8_t
        {
            /// <summary> None. You'll always get the latest pose received. No performance increase, but might result in a "stop-motion" effect on lower framerates.  </summary>
            None,
            /// <summary> Pretend you're one sample behind, and interpolate along the exact paths. More accurate, but we will lag 1 frame behind. </summary>
            InterpolateBehind,
            /// <summary> Take the last two handPoses and estimate the current values based on extrapolation. Is percieved as "faster", but is more likely to overhoot during sudden changes in direction.  </summary>
            ExtrapolateAhead
        };

        /// <summary> Unprocessed data received from CV Device(s), used as input for processing. </summary>
        class SGCORE_API CVHandTrackingData;
        /// <summary> CV Data processed into joint angles and wrist location. </summary>
        class SGCORE_API CVProcessedHandData;

        /// <summary> Keeps track of a small history of CVHandDataPoints to compensate for low(er) update rates. For example, running a VR simulation at 90Hz while sampling at 30. </summary>
        class SGCORE_API CVHandDataSmoother;
    }
}// namespace SGCore

/// <summary> Keeps track of a small history of CVHandDataPoints to compensate for low(er) update rates. For example, running a VR simulation at 90Hz while sampling at 30. </summary>
class SGCORE_API SGCore::CV::CVHandDataSmoother
{

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /**
     * The copy constructor.
     */
    CVHandDataSmoother(const CVHandDataSmoother& rhs);

    /**
     * The move constructor.
     */
    CVHandDataSmoother(CVHandDataSmoother&& rhs)
    noexcept;

    virtual ~CVHandDataSmoother();


    /**
     * The copy assignment operator.
     */
    CVHandDataSmoother& operator=(const CVHandDataSmoother& rhs);

    /**
     * The move assignment operator.
     */
    CVHandDataSmoother& operator=(CVHandDataSmoother&& rhs) noexcept;

public:

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    CVHandDataSmoother();
#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

public:

    /// <summary> Create a new instance of Smoothed Hand Data, using a first frame. </summary>
    /// <param name="firstFrame"></param>

    CVHandDataSmoother(CVHandTrackingData& firstFrame);

    //---------------------------------------------------------------------------------
    // Accessors

public:

    /// <summary> The way in which we're smoothing the incoming data </summary>
    /// <returns></returns>
    SG_NODISCARD ESmoothingMethod GetSmoothingMethod() const;
    void SetSmoothingMethod(ESmoothingMethod value);


    //--------------------------------------------------------------------------------------------------------------------
	// Utility Functions

	/// <summary> Returns true if this Smoother was created for the same device as the one of this cvPose. Used in CVHandLayer </summary>
	/// <param name="cvPose"></param>
	/// <returns></returns>
    bool MatchesDevice(const CVHandTrackingData& cvPose);

	/// <summary> Returns true if this Smoother was created for a particular hand / deviceType / hw. Used in CVHandLayer </summary>
	/// <param name="isRight"></param>
	/// <param name="type"></param>
	/// <param name="hwVer"></param>
	/// <returns></returns>
    bool MatchesDevice(bool isRight, EDeviceType type, std::string hwVer);

	/// <summary> Clear smoothing data. </summary>
    void ClearFrames();

	/// <summary> The amount of frames currently in this smoother (0 .. maxDataPoints). </summary>
	/// <returns></returns>
    int GetFrameCount();


	/// <summary> Safely retrieve a HandDataPoint out of this class' frame buffer. </summary>
	/// <param name="index"></param>
	/// <param name="frame"></param>
	/// <returns></returns>
    bool GetFrame(uint32_t index, CVProcessedHandData& out_frame);



    //---------------------------------------------------------------------------------
    // Member Functions

public:

    /// <summary> Post new CVHandOutput into this Smoother, which will converted into handAngles and calculate the appropriate values.. </summary>
	/// <param name="nextFrame"></param>
    void AddFrame(CVHandTrackingData& nextFrame);

    
	/// <summary> Updates Projection values, which is used when using SmoothingMethod.ExtrapolateAhead. </summary>
    void UpdateProjection();

private:

	/// <summary> Since the last smoothed pose is updated every time I request one, I need to keep track of it When using SmoothingMethod.ExtrapolateAhead </summary>
	/// <param name="newSmoothedData"></param>
    void SetLastSmoothed(CVProcessedHandData& newSmoothedData);


public:

	/// <summary> Based on the last X frames in this buffer, each with an earlier timestamp, Retrieve Smoothed Hand Data at currentTime </summary>
	/// <param name="currentTime">Time at which this data is requested, used to interpolate / extrapolate. </param>
	/// <param name="smoothedData"> Output: Smoothed Hand Data </param>
	/// <param name="clampValues"> If true, any smoothed output pose cannot 'extend' beyond the latest (predicted) values. </param>
	/// <returns></returns>
    bool GetSmoothedPose(const float currentTime, CVProcessedHandData& out_smoothedData, const bool clampValues = true);


};
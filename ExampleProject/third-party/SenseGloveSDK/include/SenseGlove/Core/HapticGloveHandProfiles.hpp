/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2026 SenseGlove
 *
 * @section DESCRIPTION
 *
 * An interface to get calibration to / from disk.
 */


#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGCore
{
    namespace Calibration
    {
        class SensorRange;
    }// namespace Calibration

    class HandProfile;
    class HapticGlove;

    /// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality. </summary>
    class SGCORE_API HapticGloveHandProfiles;
}// namespace SGCore

/// <summary> A glove developed by SenseGlove, that has hand tracking and/or haptic feedback functionality. </summary>
class SGCORE_API SGCore::HapticGloveHandProfiles
{
public:
    //-------------------------------------------------------------------------------------------------------------------------
    // Accessors

    /// <summary> Returns the directory where our HandProfiles are stored. </summary>
    [[nodiscard]] static const std::string& GetProfileDirectory();

    /// <summary> Set the directory where our HandProfiles are stored. </summary>
    static void SetProfileDirectory(const std::string& directory);

    /// <summary> Access the latest Left Hand Profile from disk. </summary>
    static void GetLeftHandProfile(HandProfile& out_handProfile);

    /// <summary> Sets the newest Left Hand Profile - also stores it on disk. </summary>
    static void SetLeftHandProfile(const HandProfile& handProfile);

    /// <summary> Access the latest Right Hand Profile from disk. </summary>
    static void GetRightHandProfile(HandProfile& out_handProfile);

    /// <summary> Sets the newest Right Hand Profile - also stores it on disk. </summary>
    static void SetRightHandProfile(const HandProfile& handProfile);

    //-------------------------------------------------------------------------------------------------------------------------
    // Profile Accessing Functions

    /// <summary> Retrieve a left- or right handed profile. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    static void GetProfile(bool bRightHanded, HandProfile& out_handProfile);

    /// <summary> Store a profile in the global variables and on disk. The profile determines if this is a left or right hand. </summary>
    /// <param name="profile"></param>
    static void SetProfile(const HandProfile& handProfile);

    /// <summary> Store a profile in the global variables and on disk. You determine if this is a left or right hand. </summary>
    /// <param name="profile"></param>
    /// <param name="bRightHanded"></param>
    static void SetProfile(const HandProfile& handProfile, bool bRightHanded);

    /// <summary> Restore both profiles back to their default values. </summary>
    static void RestoreDefaults();

    /// <summary> Restore the left- or right hand profiles back to their default values. </summary>
    /// <param name="bRightHanded"></param>
    static void RestoreDefaults(bool bRightHanded);

    //-------------------------------------------------------------------------------------------------------------------------
    // Store / Load functions

    /// <summary> Load the latest profiles from disk. Automatically called when you first try to access a profile.
    /// Exposed so you can force-reload profiles. </summary>
    static void TryLoadingFromDisk();

    /// <summary> Stores the last sensor range of a glove. </summary>
    /// <param name="currentRange"></param>
    /// <param name="forGlove"></param>
    /// <returns></returns>
    static bool SaveLastRange(const Calibration::SensorRange& currentRange, std::shared_ptr<HapticGlove> forGlove);

    /// <summary> Loads the last sensor range of a glove. </summary>
    /// <param name="forGlove"></param>
    /// <param name="lastRange"></param>
    /// <returns></returns>
    static bool LoadLastRange(std::shared_ptr<HapticGlove> forGlove, Calibration::SensorRange& out_lastRange);

private:
    struct Impl;

public:
    HapticGloveHandProfiles() = delete;
    virtual ~HapticGloveHandProfiles() = delete;
};

/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2023 SenseGlove
 *
 * @section DESCRIPTION
 *
 * A profile containing all the information required for HapticGloves.
 */


#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace Nova
    {
        class NovaGloveHandProfile;
    }// namespace Nova

    namespace SG
    {
        class SenseGloveHandProfile;
    }// namespace SG

    /// <summary> Interpolation profiles for a user's hand, compatible with all HapticGloves. </summary>
    class SGCORE_API HandProfile;
}// namespace SGCore

/// <summary> Interpolation profiles for a user's hand, compatible with all HapticGloves. </summary>
class SGCORE_API SGCore::HandProfile
{
public:
    /// <summary> Generate a new handProfile for either a left or right hand. </summary>
    /// <param name="rightHand"></param>
    /// <returns></returns>
    SG_NODISCARD static HandProfile Default(bool bRightHanded);

    /// <summary> Convert a string notation of a NovaGloveHandProfile into a new instance. </summary>
    /// <param name="serializedString"></param>
    /// <returns></returns>
    SG_NODISCARD static HandProfile Deserialize(const std::string& serializedString);

public:
    //--------------------------------------------------------------------------------------
    // Global Accessing and Saving

    /// <summary> Returns the directory where HandProfiles are being stored. Does not include a '\\' at the end. </summary>
    /// <returns></returns>
    SG_NODISCARD static const std::string& GetProfileDirectory();

    /// <summary> Filename for the left hand profile. </summary>
    SG_NODISCARD static const std::string& GetLeftHandFileName();

    /// <summary> Filename for the right hand profile. </summary>
    SG_NODISCARD static const std::string& GetRightHandFileName();

    /// <summary> Returns the fileName of the left or right-handed profiles. </summary>
    /// <param name="bRightHanded"></param>
    /// <returns></returns>
    SG_NODISCARD static const std::string& GetProfileFileName(bool bRightHanded);

    /// <summary> Retrieves the latest HandProfile from disk. If this function returns false, latestProfils is equal to SGCOre::HandProfile::Default(rightHand). </summary>
    /// <param name="bRightHand"></param>
    /// <returns></returns>
    static bool GetLatestProfile(bool bRightHanded, HandProfile& out_latestProfile);

    /// <summary> Stores a HandProfile on disk for other programs to access. Call this function only if your software handles calibration functions. </summary>
    /// <param name="profileToStore"></param>
    /// <returns></returns>
    static bool StoreProfile(const HandProfile& profileToStore);

    /// <summary> Resets the Calibration of a specific back to default values. </summary>
    /// <param name="bOnDisk"></param>
    /// <param name="bRightHanded">  </param>
    /// <returns></returns>
    static bool ResetCalibration(bool bRightHanded, bool bOnDisk = true);

    /// <summary> Resets the Calibration of both hands back to default values. </summary>
    /// <param name="bOnDisk"></param>
    /// <returns></returns>
    static void ResetCalibration(bool bOnDisk = true);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> The default constructor. </summary>
    /// <returns></returns>
    HandProfile();

    /// <summary> Creates a new instance of a HandProfile. </summary>
    /// <param name="bRightHand"></param>
    /// <param name="senseGloveHandProfile"></param>
    /// <param name="novaGloveHandProfile"></param>
    /// <returns></returns>
    HandProfile(bool bRightHanded,
                const SG::SenseGloveHandProfile& senseGloveHandProfile,
                const Nova::NovaGloveHandProfile& novaGloveHandProfile);

    /**
     * The copy constructor.
     */
    HandProfile(const HandProfile& rhs);

    /**
     * The move constructor.
     */
    HandProfile(HandProfile&& rhs) noexcept;

    virtual ~HandProfile();

public:
    /**
     * The copy assignment operator.
     */
    HandProfile& operator=(const HandProfile& rhs);

    /**
     * The move assignment operator.
     */
    HandProfile& operator=(HandProfile&& rhs) noexcept;

public:
    /// <summary> Whether this profile was created for a left or right hand. </summary>
    SG_NODISCARD bool IsRight() const;

    /// <summary> Profile for SenseGloves. </summary>
    SG_NODISCARD SG::SenseGloveHandProfile& GetSenseGloveHandProfile() const;

    /// <summary> User profile for Nova. </summary>
    SG_NODISCARD Nova::NovaGloveHandProfile& GetNovaGloveHandProfile() const;

public:
    SG_NODISCARD bool Equals(const HandProfile& handProfile) const;

    /// <summary> Reset this profile back to its default values. </summary>
    void Reset();

public:
    /// <summary> Convert this NovaGloveHandProfile into a string notation so it can be stored on disk. </summary>
    /// <returns></returns>
    SG_NODISCARD std::string Serialize() const;
};

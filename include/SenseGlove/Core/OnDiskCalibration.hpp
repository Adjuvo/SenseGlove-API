/**
 * @file
 *
 * @author  Max Lammers <max@senseglove.com>
 * @author  Mamadou Babaei <mamadou@senseglove.com>
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 - 2024 SenseGlove
 *
 * @section DESCRIPTION
 *
 * Manages calibration data stored on disk. One for left, another for right. We'll assume your user will use no more than 2 gloves at a time.
 */


#pragma once

#include <memory>
#include <string>

#include "DeviceTypes.hpp"
#include "Platform.hpp"

namespace SGCore
{
    namespace Util
    {
        /// <summary> A rotation in 3D space that can be applied to a 3D vector or converted into Euler Angles. </summary>
        class OnDiskCalibration;
    }// namespace Util
}// namespace SGCore

/// <summary> A rotation in 3D space that can be applied to a 3D vector or converted into Euler Angles. </summary>
class SGCORE_API SGCore::Util::OnDiskCalibration
{
    //----------------------------------------------------------------------------------------------------------------------------
    // Static Functions
public:
    SG_NODISCARD static bool Deserialize(const std::string& serialized, OnDiskCalibration& out_calibrationData);

    SG_NODISCARD static OnDiskCalibration GetRightHandProfile();
    static void SetRightHandProfile(const OnDiskCalibration& profile);

    SG_NODISCARD static OnDiskCalibration GetLeftHandProfile();
    static void SetLeftHandProfile(const OnDiskCalibration& profile);

    SG_NODISCARD static OnDiskCalibration GetHandProfile(bool bRightHand);
    static void StoreHandProfile(bool bRightHand, EDeviceType type, const std::string& serialized);

    static void TryLoadingProfiles();
    static void ResetProfiles();

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /**
     * The default constructor.
     */
    OnDiskCalibration();

    /// <summary> Creates a new instance of a OnDiskCalibration. </summary>
    OnDiskCalibration(SGCore::EDeviceType deviceType, bool bRightHand,
                      const std::string& lib, const std::string& serialized);

    /**
     * The copy constructor.
     */
    OnDiskCalibration(const OnDiskCalibration& rhs);

    /**
     * The move constructor.
     */
    OnDiskCalibration(OnDiskCalibration&& rhs) noexcept;

    virtual ~OnDiskCalibration();

public:
    /**
     * The copy assignment operator.
     */
    OnDiskCalibration& operator=(const OnDiskCalibration& rhs);

    /**
     * The move assignment operator.
     */
    OnDiskCalibration& operator=(OnDiskCalibration&& rhs) noexcept;

    //----------------------------------------------------------------------------------------------------------------------------
    // Accessors

public:
    SG_NODISCARD EDeviceType GetDeviceType() const;
    void SetDeviceType(EDeviceType type);

    SG_NODISCARD bool GetRightHanded() const;
    void SetRightHanded(bool bRightHand);

    SG_NODISCARD const std::string& GetLibVersion() const;
    void SetLibVersion(const std::string& libVer);

    SG_NODISCARD const std::string& GetSerializedProfile() const;
    void SetSerializedProfile(const std::string& serialized);

    //----------------------------------------------------------------------------------------------------------------------------
    // Class Functions

    SG_NODISCARD bool IsValid() const;

    SG_NODISCARD std::string Serialize() const;
};
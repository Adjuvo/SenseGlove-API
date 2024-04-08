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
 * Internal class that acts as a sort of 'in between' handProfile. This class
 * converts SG Dk1 Angles into 'normalized data' - between 0 .. 1.
 */


#pragma once

#include <memory>
#include <vector>

#include "Platform.hpp"

namespace SGCore
{
    namespace SG
    {
        /// <summary> Acts as a sort of 'in between' handProfile. This class converts SG Dk1 Angles into
        /// 'normalized data' - between 0 .. 1. </summary>
        class SGCORE_API SenseGloveSensorNormalizer;
    }// namespace Util
}// namespace SGCore

/// <summary> Acts as a sort of 'in between' handProfile. This class converts SG Dk1 Angles into 'normalized data' -
/// between 0 .. 1. </summary>
class SGCORE_API SGCore::SG::SenseGloveSensorNormalizer
{
private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

public:
    SenseGloveSensorNormalizer();

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /// <summary> Creates a new SenseGlove Sensor Normalizer based off the device's sensor angles. </summary>
    /// <param name="bRightHanded"></param>
    explicit SenseGloveSensorNormalizer(bool bRightHanded);

    /**
     * The copy constructor.
     */
    SenseGloveSensorNormalizer(const SenseGloveSensorNormalizer& rhs);

    /**
     * The move constructor.
     */
    SenseGloveSensorNormalizer(SenseGloveSensorNormalizer&& rhs) noexcept;

    virtual ~SenseGloveSensorNormalizer();

public:
    /**
     * The copy assignment operator.
     */
    SenseGloveSensorNormalizer& operator=(const SenseGloveSensorNormalizer& rhs);

    /**
     * The move assignment operator.
     */
    SenseGloveSensorNormalizer& operator=(SenseGloveSensorNormalizer&& rhs) noexcept;

public:
    //---------------------------------------------------------------------------------
    // Accessors

    //---------------------------------------------------------------------------------
    // Member Functions

public:
    /// <summary> Normalize a finger's flexion, based on the total flexion of the exoskeleton. </summary>
    /// <param name="finger"></param>
    /// <param name="sumFlexionAngles"></param>
    /// <returns></returns>
    SG_NODISCARD float NormalizeFlexion(int32_t finger, float sumFlexionAngles) const;

    /// <summary> Normalize a finger's abduction, based on the total abduction of the exoskeleton. </summary>
    /// <param name="finger"></param>
    /// <param name="sumAbductionAngles"></param>
    /// <returns></returns>
    SG_NODISCARD float NormalizeAbduction(int32_t finger, float sumAbductionAngles) const;
};
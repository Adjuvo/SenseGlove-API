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
 * Describes a vibration based on a number of parameters. Is sent to Nova Gloves to be generated on the hardware and played.
 */


#pragma once

#include <memory>

#include "Platform.hpp"

namespace SGCore
{
    /// <summary> Waveform type for an advanced Buzz Command </summary>
    enum class SGCORE_API EWaveformType : uint8_t
    {
        /// <summary> We're not sure what type of Waveform to use </summary>
        Unknown = 0,
        /// <summary> Smooth sine wave </summary>
        Sine,
        /// <summary> Can shift duty Cycle </summary>
        Square,
        /// <summary> Inverse of SawDown  </summary>
        SawUp,
        /// <summary> Inverse of SawUp </summary>
        SawDown,
        /// <summary> Triangle waveform </summary>
        Triangle,
        /// <summary> A random, noisy signal </summary>
        Noise
    };

    /// <summary> A single vibration pulse for Nova Gloves </summary>
    class SGCORE_API CustomWaveform;
}// namespace SGCore


/// <summary> A single vibration pulse for Nova Gloves </summary>
class SGCORE_API SGCore::CustomWaveform
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
    CustomWaveform(const CustomWaveform& rhs);

    /**
     * The move constructor.
     */
    CustomWaveform(CustomWaveform&& rhs) noexcept;

    virtual ~CustomWaveform();


    /**
     * The copy assignment operator.
     */
    CustomWaveform& operator=(const CustomWaveform& rhs);

    /**
     * The move assignment operator.
     */
    CustomWaveform& operator=(CustomWaveform&& rhs) noexcept;

public:

#if SENSEGLOVE_UNREAL_ENGINE_PLUGIN
    CustomWaveform();
#endif /* SENSEGLOVE_UNREAL_ENGINE_PLUGIN */

    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    CustomWaveform(float amplitude, float duration);

    CustomWaveform(float amplitude, float duration, float frequency);

    //---------------------------------------------------------------------------------
    // Accessors

public:

    /// <summary> Get the total amplitude of the wavefrom, represented by 0 (off) or 1 (maximum value) </summary>
    /// <returns></returns>
    SG_NODISCARD float GetAmplitude() const;
    /// <summary> Set the total amplitude of the wavefrom, represented by 0 (off) or 1 (maximum value) </summary>
    /// <param name="finger"></param>
    void SetAmplitude(float value);

    /// <summary> Get the Type of waveform pattern that is used. </summary>
    /// <returns></returns>
    SG_NODISCARD EWaveformType GetWaveType() const;
    /// <summary> Set the Type of waveform pattern that is used. </summary>
    /// <param name="value"></param>
    void SetWaveType(EWaveformType value);

    /// <summary> Get whether or not this Waveform is infinitely repeating </summary>
    /// <returns></returns>
    SG_NODISCARD bool GetInfinite() const;
    /// <summary> Set whether or not this Waveform is infinitely repeating </summary>
    /// <param name="value"></param>
    void SetInfinite(bool value);

    /// <summary> Get the amount of times to repeat this waveform. 1 is the default. If set to 0, repreats indefinitely. </summary>
    /// <returns></returns>
    SG_NODISCARD int32_t GetRepeatAmount() const;
    /// <summary> Set the amount of times to repeat this waveform. 1 is the default. If set to 0, repreats indefinitely. </summary>
    /// <param name="value"></param>
    void SetRepeatAmount(int32_t value);

    /// <summary> Get time, in seconds, before the signal reaches its maximum amplitude. Limited to 0.01 - 1s. Set to 0 for an instant start. Linear only </summary>
    /// <returns></returns>
    SG_NODISCARD float GetAttackTime() const;
    /// <summary> Set time, in seconds, before the signal reaches its maximum amplitude. Limited to 0.01 - 1s. Set to 0 for an instant start. Linear only </summary>
    /// <returns></returns>
    void SetAttackTime(float value);

    /// <summary> Get time, in seconds, to keep the signal at one Amplidue. Limited to 0.01 - 1s. </summary>
    /// <returns></returns>
    SG_NODISCARD float GetSustainTime() const;
    /// <summary> Set time, in seconds, to keep the signal at one Amplidue. Limited to 0.01 - 1s. </summary>
    /// <returns></returns>
    void SetSustainTime(float value);

    /// <summary> Get time it takes for the effect to fade out after AttackTime+SuatainTime has passed. Limited to 0.01 - 1s. Set to 0 for instant stop. Linear only </summary>
    /// <returns></returns>
    SG_NODISCARD float GetDecayTime() const;
    /// <summary> Set time it takes for the effect to fade out after AttackTime+SuatainTime has passed. Limited to 0.01 - 1s. Set to 0 for instant stop. Linear only </summary>
    /// <returns></returns>
    void SetDecayTime(float value);

    /// <summary> Get the Wavefrom Frequency at the start of the wavefrom. Limited between [10 - 500Hz] for Nova Gloves </summary>
    /// <returns></returns>
    SG_NODISCARD float GetFrequencyStart() const;
    /// <summary> Set the Wavefrom Frequency at the start of the wavefrom. Limited between [10 - 500Hz] for Nova Gloves </summary>
    /// <returns></returns>
    void SetFrequencyStart(float value);

    /// <summary> Get the Wavefrom Frequency at the end of the wavefrom. Limited between [10 - 500Hz] for Nova Gloves </summary>
    /// <returns></returns>
    SG_NODISCARD float GetFrequencyEnd() const;
    /// <summary> Set the Wavefrom Frequency at the end of the wavefrom. Limited between [10 - 500Hz] for Nova Gloves </summary>
    /// <returns></returns>
    void SetFrequencyEnd(float value);

    /// <summary> Get value of [0..1], repesenting a perentage of total time (attack+sustain+decay). After that moment passes, we increase the frequency by FrequencySwicth factor </summary>
    /// <returns></returns>
    SG_NODISCARD float GetFrequencySwitchTime() const;
    /// <summary> Set value of [0..1], repesenting a perentage of total time (attack+sustain+decay). After that moment passes, we increase the frequency by FrequencySwicth factor </summary>
    /// <returns></returns>
    void SetFrequencySwitchTime(float value);

    /// <summary> After a certain % of the waveform (FrequencySwitchTime) plays, multiply the frequency by this factor [1x .. 3x] </summary>
    /// <returns></returns>
    SG_NODISCARD float GetFrequencySwitchFactor() const;
    /// <summary> After a certain % of the waveform (FrequencySwitchTime) plays, multiply the frequency by this factor [1x .. 3x] </summary>
    /// <param name="value"></param>
    void SetFrequencySwitchFactor(float value);


    //---------------------------------------------------------------------------------
    // Member Functions

public:

    /// <summary> The total command time of a single play of this pattern (not taking into account the RepeatAmount). </summary>
    /// <returns></returns>
    SG_NODISCARD float GetEffectTime() const; 

    /// <summary> Total time for the entire effect (effecttime multipled by the repeatamount) </summary>
    /// <returns></returns>
    SG_NODISCARD float GetTotalEffectTime() const;

    /// <summary>  If true, the frequency of this waveform jumps at any time during its playtime by FrequencySwitchFactor. </summary>
    /// <returns></returns>
    SG_NODISCARD bool FrequencyJumps() const;

    /// <summary> Check if this CustomWaveform is roughly equal to another. </summary>
    SG_NODISCARD bool Equals(const CustomWaveform& other) const;

    /// <summary> Create a string representation of this CustomWaveform. </summary>
    SG_NODISCARD std::string ToString() const;

    /// <summary> Creates a strign representation of the EWaveformType </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    SG_NODISCARD static std::string ToString(EWaveformType type);
};

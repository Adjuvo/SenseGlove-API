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
 * Contains information on Haptic channels available to this device for IPC.
 * Some devices have different "Haptic Channels". This info is exposed via IPC to
 * SGCore.
 */


#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    /// <summary> Different types of Haptic Channels - with different behaviours </summary>
    enum class SGCONNECT_API EHapticChannelType : uint8_t
    {
        /// <summary> This type of haptic channel can be constantly overridden. SGConnect will only send a command if
        /// a change occurs. Ideal for Force-Feedback. </summary>
        StreamingChannel,
        /// <summary> These commands must be sent once, after thire queue is cleared. </summary>
        FireAndForgetChannel
    };

    /// <summary> Contains information on Haptic channels available to this device for IPC. </summary>
    class HapticResponse;
}// namespace SGCore

/// <summary> Contains information on Haptic channels available to this device for IPC. </summary>
class SGCONNECT_API SGConnect::HapticResponse
{
public:
    /// <summary> Byte used to identify streaming channels </summary>
    static uint8_t GetStreamingType();
    /// <summary> byte used to indicate fire-and-forget channels. </summary>
    static uint8_t GetFireNForgetType();

public:
    /// <summary> Parse a raw HapticResponse, as received from a possible SGDevice, into useful data. </summary>
    static HapticResponse Parse(std::string& out_rawCommand);

    /// <summary> Parse a series of characters into a collections of 'enumerators' (uint8_t). </summary>
    /// <param name="section"></param>
    /// <returns></returns>
    static std::vector<uint8_t> ParseChannels(const std::string& section);

    //---------------------------------------------------------------------------------
    // C++ Constructor Voodoo

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    //---------------------------------------------------------------------------------
    // Actual C++ Constructors

    /// <summary> Create a new instance of an invalid IdResponse </summary>
    HapticResponse();

    /// <summary> Create a new instance of a processed IdResponse </summary>
    HapticResponse(const std::vector<uint8_t>& sChannels, const std::vector<uint8_t>& hChannels);

public:
    /**
     * The copy constructor.
     */
    HapticResponse(const HapticResponse& rhs);

    /**
     * The move constructor.
     */
    HapticResponse(HapticResponse&& rhs) noexcept;

public:
    virtual ~HapticResponse();

public:
    /**
     * The copy assignment operator.
     */
    HapticResponse& operator=(const HapticResponse& rhs);

    /**
     * The move assignment operator.
     */
    HapticResponse& operator=(HapticResponse&& rhs) noexcept;

public:
    //---------------------------------------------------------------------------------
    // Accessors

    //---------------------------------------------------------------------------------
    // Class Methods

    /// <summary> Generates new Device Addresses for this haptic data </summary>
    /// <param name="deviceIndex"></param>
    void RegenerateAddresses(int32_t deviceIndex);


    int32_t GetHapticChannelCount() const;

    /// <summary> Returns true if we need to clear the channel </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    bool ClearsChannel(int32_t index) const;

    /// <summary> Returns the device address wihtin the block(s). </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    bool GetBlockAddress(int32_t index, std::string& out_address) const;

    /// <summary> Returns the device address wihtin the block(s) - without checking if this Index is valid. </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    std::string& GetBlockAddress_Unguarded(int32_t index) const;

    /// <summary> Returns the channel byte type - without checking if this Index is valid </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    uint8_t GetChannelType_Unguarded(int32_t index) const;

    /// <summary> Store the last sent haptics in the appropriate channel. </summary>
    /// <param name="channel"></param>
    /// <param name="lastHaptics"></param>
    void SetLastHaptics_Unguarded(int32_t channel, const std::string& lastHaptics);

    /// <summary> Retrieve the last haptic command send through a channel. Returns true if length > 0. </summary>
    /// <param name="channel"></param>
    /// <param name="out_sentAmount"></param>
    /// <param name="out_sentAmount"></param>
    /// <returns></returns>
    void GetLastHaptics_Unguarded(int32_t channel, std::string& out_lastHaptics, int32_t& out_sentAmount) const;

    /// <summary> Set the amount of times a message was sent to the channel </summary>
    /// <param name="channel"></param>
    /// <param name="sentAmount"></param>
    void SetSentAmount_Unguarded(int32_t channel, int32_t sentAmount);

    /// <summary> Increment the SentAmount of a specific channel, after sending the command to the device. </summary>
    /// <param name="channel"></param>
    void IncrementSentAmount_Unguarded(int32_t channel);

    /// <summary> Returns a string representing a series of characters for SGCore to detect the haptic channel
    /// implementation. </summary>
    /// <returns></returns>
    const std::string& ReportChannels() const;
};

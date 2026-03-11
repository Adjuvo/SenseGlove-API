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
 * Class to parse incoming/outgoing commands read from shared memory.
 *
 * The idea here is that incoming messages can have a 'messageID'. If they do,
 * we assume they require a response from the device, which we will post back to
 * Shared Memory with the same ID so the requesting program knows this response
 * is to its specific command.
 */


#pragma once

#include <memory>
#include <string>

#include <SenseGlove/Common/Platform.hpp>

namespace SGConnect
{
    class IpcCommand;
}

/// <summary> A command read from IPC or to be written to IPC. </summary>
class SGCONNECT_API SGConnect::IpcCommand
{
public:
    /// <summary> Parse an IpcCommand from the raw IPC string. </summary>
    static IpcCommand Parse(const std::string& IpcString);

private:
    struct Impl;
    std::unique_ptr<Impl> Pimpl;

public:
    /// <summary> Create a new instance of the IPC Command </summary>
    IpcCommand(const std::string& cmId, const std::string& cmdContent);

    /**
     * The copy constructor.
     */
    IpcCommand(const IpcCommand& rhs);

    /**
     * The move constructor.
     */
    IpcCommand(IpcCommand&& rhs) noexcept;

    virtual ~IpcCommand();

public:
    /**
     * The copy assignment operator.
     */
    IpcCommand& operator=(const IpcCommand& rhs);

    /**
     * The move assignment operator.
     */
    IpcCommand& operator=(IpcCommand&& rhs) noexcept;

public:
    /// <summary> Message ID for this command </summary>
    [[nodiscard]] const std::string& GetId() const;

    /// <summary> The content of the message </summary>
    [[nodiscard]] const std::string& GetContent() const;

public:
    /// <summary> Returns true if this command requires a response from the device. </summary>
    [[nodiscard]] bool HasResponse() const;
};

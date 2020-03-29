#pragma once

namespace ProtocolCraft
{
    enum class ConnectionState
    {
        None = -1,
        Handshake = 0,
        Status = 1,
        Login = 2,
        Play = 3
    };
} // ProtocolCraft

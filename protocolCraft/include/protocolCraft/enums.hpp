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

    enum class HandshakeClientboundIds
    {

    };

    enum class HandshakeServerboundIds
    {
        Handshake = 0x00
    };

    enum class StatusClientboundIds
    {

    };

    enum class StatusServerboundIds
    {

    };

    enum class LoginClienboundIds
    {
        DisconnectLogin = 0x00,
        EncryptionRequest = 0x01,
        LoginSuccess = 0x02,
        SetCompression = 0x03
    };

    enum class LoginServerboundIds
    {
        LoginStart = 0x00,
        EncryptionResponse = 0x01
    };
} // ProtocolCraft
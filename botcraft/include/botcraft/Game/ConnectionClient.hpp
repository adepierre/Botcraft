#pragma once

#include "protocolCraft/Handler.hpp"

namespace Botcraft
{
    class NetworkManager;

    /// @brief The base client handling connection with a server.
    /// Only processes packets required to maintain the connection.
    class ConnectionClient : public ProtocolCraft::Handler
    {
    public:
        ConnectionClient();
        virtual ~ConnectionClient();

        /// @brief Connect the client to the server at address
        /// @param address Address to connect to, as written in minecraft multiplayer window
        /// @param login If login is empty, will try to connect with a Microsoft account
        /// @param force_microsoft_account If true, then Microsoft auth flow will be used. In this case, login is used as key to cache the credentials
        void Connect(const std::string& address, const std::string& login, const bool force_microsoft_account = false);
        virtual void Disconnect();

        bool GetShouldBeClosed() const;
        void SetShouldBeClosed(const bool b);

        std::shared_ptr<NetworkManager> GetNetworkManager() const;

        /// @brief Send a message in the game chat
        /// @param msg The message to send
        void SendChatMessage(const std::string& msg);

        /// @brief Send a command in the game chat
        /// @param command The command to send (with no / at start)
        void SendChatCommand(const std::string& command);

        /// @brief Ask to respawn when dead
        void Respawn();

    protected:
        using ProtocolCraft::Handler::Handle; // Don't hide all Handle() functions from base classes
        virtual void Handle(ProtocolCraft::ClientboundLoginDisconnectPacket& packet) override;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        virtual void Handle(ProtocolCraft::ClientboundContainerAckPacket& packet) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundDisconnectPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket& packet) override;
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        virtual void Handle(ProtocolCraft::ClientboundDisconnectConfigurationPacket& packet) override;
#endif
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& packet) override;
#endif

    protected:
        std::shared_ptr<NetworkManager> network_manager;

        bool should_be_closed;
    };
} //Botcraft

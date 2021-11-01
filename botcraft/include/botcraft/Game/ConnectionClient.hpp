#pragma once

#include "protocolCraft/Handler.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllMessages.hpp"

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
        /// @param password If password is empty and login is not, will be in offline mode. If password is given, will connect with a Mojang account.
        void Connect(const std::string& address, const std::string& login, const std::string& password);
        virtual void Disconnect();

        const bool GetShouldBeClosed() const;
        void SetShouldBeClosed(const bool b);

        std::shared_ptr<NetworkManager> GetNetworkManager() const;

        /// @brief Send a message in the game chat
        /// @param msg The message to send
        void SendChatMessage(const std::string& msg);
        
        /// @brief Ask to respawn when dead
        void Respawn();

    protected:
        virtual void Handle(ProtocolCraft::Message &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLoginDisconnectPacket &msg) override;
#if PROTOCOL_VERSION < 755
        virtual void Handle(ProtocolCraft::ClientboundContainerAckPacket &msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundDisconnectPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket &msg) override;
        
    protected:
        std::shared_ptr<NetworkManager> network_manager;

        bool should_be_closed;
    };
} //Botcraft
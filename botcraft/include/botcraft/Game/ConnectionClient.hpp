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

        /// @brief Connect the client in offline mode if login is not empty, fallback to Microsoft auth flow if empty.
        /// @param address Address to connect to, same format as one would type it in a vanilla client
        /// @param login Username the bot will use to connect, will default back to Microsoft auth if empty
        void Connect(const std::string& address, const std::string& login);
        /// @brief Connect the client in online mode. Will prompt user to auth with a valid Microsoft account
        /// @param address Address to connect to, same format as one would type it in a vanilla client
        /// @param cache_key Will be used to store the auth tokens in a cache file to speed up future connection with the same account.
        /// Use different cache keys to store multiple accounts
        void ConnectMicrosoft(const std::string& address, const std::string& cache_key = "");
        /// @brief Connect the client in online mode using the provided minecraft token
        /// @param address Address to connect to, same format as one would type it in a vanilla client
        /// @param minecraft_token Minecraft token to use for auth. It's the user responsability to make sure it's valid.
        void ConnectMinecraftToken(const std::string& address, const std::string& minecraft_token);
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

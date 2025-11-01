#include "botcraft/Game/ConnectionClient.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    ConnectionClient::ConnectionClient()
    {
        network_manager = nullptr;
        should_be_closed = false;
    }

    ConnectionClient::~ConnectionClient()
    {
        Disconnect();
    }

    void ConnectionClient::Connect(const std::string& address, const std::string& login)
    {
        if (login.empty())
        {
            ConnectMicrosoft(address);
        }
        else
        {
            network_manager = std::make_shared<NetworkManager>(address, login, NetworkManager::AuthType::Offline, std::vector<Handler*>{ this });
        }
    }

    void ConnectionClient::ConnectMicrosoft(const std::string& address, const std::string& cache_key)
    {
        network_manager = std::make_shared<NetworkManager>(address, cache_key, NetworkManager::AuthType::Microsoft, std::vector<Handler*>{ this });
    }

    void ConnectionClient::ConnectMinecraftToken(const std::string& address, const std::string& minecraft_token)
    {
        network_manager = std::make_shared<NetworkManager>(address, minecraft_token, NetworkManager::AuthType::McToken, std::vector<Handler*>{ this });
    }

    void ConnectionClient::Disconnect()
    {
        should_be_closed = true;
        if (network_manager)
        {
            network_manager->Stop();
        }
        network_manager.reset();
    }

    bool ConnectionClient::GetShouldBeClosed() const
    {
        return should_be_closed;
    }

    void ConnectionClient::SetShouldBeClosed(const bool b)
    {
        should_be_closed = b;
    }

    std::shared_ptr<NetworkManager> ConnectionClient::GetNetworkManager() const
    {
        return network_manager;
    }

    void ConnectionClient::SendChatMessage(const std::string& msg)
    {
        if (network_manager && network_manager->GetConnectionState() == ConnectionState::Play)
        {
            network_manager->SendChatMessage(msg);
        }
    }

    void ConnectionClient::SendChatCommand(const std::string& command)
    {
        if (network_manager && network_manager->GetConnectionState() == ConnectionState::Play)
        {
            network_manager->SendChatCommand(command);
        }
    }

    void ConnectionClient::Respawn()
    {
        if (network_manager && network_manager->GetConnectionState() == ConnectionState::Play)
        {
            std::shared_ptr<ServerboundClientCommandPacket> status_message = std::make_shared<ServerboundClientCommandPacket>();
            status_message->SetAction(0);
            network_manager->Send(status_message);
        }
    }


    void ConnectionClient::Handle(ClientboundLoginDisconnectPacket& packet)
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        LOG_INFO("Disconnect during login with reason: " << packet.GetReason().GetRawText());
#else
        LOG_INFO("Disconnect during login with reason: " << packet.GetReason());
#endif

        should_be_closed = true;
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    void ConnectionClient::Handle(ClientboundContainerAckPacket& packet)
    {
        // If the transaction was not accepted, we must apologize
        // else it's processed in InventoryManager
        if (!packet.GetAccepted())
        {
            std::shared_ptr<ServerboundContainerAckPacket> apologize_packet = std::make_shared<ServerboundContainerAckPacket>();
            apologize_packet->SetContainerId(packet.GetContainerId());
            apologize_packet->SetUid(packet.GetUid());
            apologize_packet->SetAccepted(packet.GetAccepted());

            network_manager->Send(apologize_packet);
        }
    }
#endif

    void ConnectionClient::Handle(ClientboundDisconnectPacket& packet)
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        LOG_INFO("Disconnect during playing with reason: " << packet.GetReason().GetRawText());
#else
        LOG_INFO("Disconnect during playing with reason: " << packet.GetReason().Serialize().Dump());
#endif

        should_be_closed = true;
    }

    void ConnectionClient::Handle(ClientboundPlayerPositionPacket& packet)
    {
        // Confirmations have to be sent from here, as there is no PhysicsManager with a ConnectionClient
        std::shared_ptr<ServerboundAcceptTeleportationPacket> confirm_packet = std::make_shared<ServerboundAcceptTeleportationPacket>();
        confirm_packet->SetId_(packet.GetId_());

        network_manager->Send(confirm_packet);
    }

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    void ConnectionClient::Handle(ClientboundDisconnectConfigurationPacket& packet)
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        LOG_INFO("Disconnect during configuration with reason: " << packet.GetReason().GetRawText());
#else
        LOG_INFO("Disconnect during configuration with reason: " << packet.GetReason().Serialize().Dump());
#endif

        should_be_closed = true;
    }
#endif

#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
    void ConnectionClient::Handle(ClientboundLoginPacket& packet)
    {
        network_manager->Send(std::make_shared<ServerboundPlayerLoadedPacket>());
    }

    void ConnectionClient::Handle(ClientboundRespawnPacket& packet)
    {
        network_manager->Send(std::make_shared<ServerboundPlayerLoadedPacket>());
    }
#endif
} //Botcraft

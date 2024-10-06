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

    void ConnectionClient::Connect(const std::string& address, const std::string& login, const bool force_microsoft_account)
    {
        network_manager = std::make_shared<NetworkManager>(address, login, force_microsoft_account, std::vector<Handler*>(1, this));
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


    void ConnectionClient::Handle(ClientboundLoginDisconnectPacket& msg)
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        LOG_INFO("Disconnect during login with reason: " << msg.GetReason().GetRawText());
#else
        LOG_INFO("Disconnect during login with reason: " << msg.GetReason());
#endif

        should_be_closed = true;
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    void ConnectionClient::Handle(ClientboundContainerAckPacket& msg)
    {
        // If the transaction was not accepted, we must apologize
        // else it's processed in InventoryManager
        if (!msg.GetAccepted())
        {
            std::shared_ptr<ServerboundContainerAckPacket> apologize_msg = std::make_shared<ServerboundContainerAckPacket>();
            apologize_msg->SetContainerId(msg.GetContainerId());
            apologize_msg->SetUid(msg.GetUid());
            apologize_msg->SetAccepted(msg.GetAccepted());

            network_manager->Send(apologize_msg);
        }
    }
#endif

    void ConnectionClient::Handle(ClientboundDisconnectPacket& msg)
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        LOG_INFO("Disconnect during playing with reason: " << msg.GetReason().GetRawText());
#else
        LOG_INFO("Disconnect during playing with reason: " << msg.GetReason().Serialize().Dump());
#endif

        should_be_closed = true;
    }

    void ConnectionClient::Handle(ClientboundPlayerPositionPacket& msg)
    {
        // Confirmations have to be sent from here, as there is no PhysicsManager with a ConnectionClient
        std::shared_ptr<ServerboundAcceptTeleportationPacket> confirm_msg = std::make_shared<ServerboundAcceptTeleportationPacket>();
        confirm_msg->SetId_(msg.GetId_());

        network_manager->Send(confirm_msg);
    }

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    void ConnectionClient::Handle(ClientboundDisconnectConfigurationPacket& msg)
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        LOG_INFO("Disconnect during configuration with reason: " << msg.GetReason().GetRawText());
#else
        LOG_INFO("Disconnect during configuration with reason: " << msg.GetReason().Serialize().Dump());
#endif

        should_be_closed = true;
    }
#endif
} //Botcraft

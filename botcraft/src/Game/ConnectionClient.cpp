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

    void ConnectionClient::Connect(const std::string& address, const std::string& login, const std::string& password, const bool force_microsoft_account)
    {
        network_manager = std::make_shared<NetworkManager>(address, login, password, force_microsoft_account);
        network_manager->AddHandler(this);
    }

    void ConnectionClient::Disconnect()
    {
        should_be_closed = true;
        network_manager.reset();
    }

    const bool ConnectionClient::GetShouldBeClosed() const
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
        if (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            std::shared_ptr<ServerboundChatPacket> chat_message(new ServerboundChatPacket);
            chat_message->SetMessage(msg);
#if PROTOCOL_VERSION > 758
            chat_message->SetTimestamp(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
#endif
            network_manager->Send(chat_message);
        }
    }

    void ConnectionClient::Respawn()
    {
        if (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            std::shared_ptr<ServerboundClientCommandPacket> status_message(new ServerboundClientCommandPacket);
            status_message->SetAction(0);
            network_manager->Send(status_message);
        }
    }


    void ConnectionClient::Handle(Message &msg)
    {

    }

    void ConnectionClient::Handle(ClientboundLoginDisconnectPacket &msg)
    {
        LOG_INFO("Disconnect during login with reason: " << msg.GetReason().GetText());

        should_be_closed = true;
    }

#if PROTOCOL_VERSION < 755
    void ConnectionClient::Handle(ClientboundContainerAckPacket &msg)
    {
        // If the transaction was not accepted, we must apologize
        // else it's processed in InventoryManager
        if (!msg.GetAccepted())
        {
            std::shared_ptr<ServerboundContainerAckPacket> apologize_msg(new ServerboundContainerAckPacket);
            apologize_msg->SetContainerId(msg.GetContainerId());
            apologize_msg->SetUid(msg.GetUid());
            apologize_msg->SetAccepted(msg.GetAccepted());

            network_manager->Send(apologize_msg);
        }
    }
#endif

    void ConnectionClient::Handle(ClientboundDisconnectPacket &msg)
    {
        LOG_INFO("Disconnect during playing with reason: " << msg.GetReason().GetRawText());
        
        should_be_closed = true;
    }

    void ConnectionClient::Handle(ClientboundPlayerPositionPacket& msg)
    {
        // Confirmations have to be sent from here, as there is no
        // EntityManager with only a ConnectionClient
        std::shared_ptr<ServerboundAcceptTeleportationPacket> confirm_msg(new ServerboundAcceptTeleportationPacket);
        confirm_msg->SetId_(msg.GetId_());

        network_manager->Send(confirm_msg);
    }
} //Botcraft

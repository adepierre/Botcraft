#include <functional>

#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Network/TCP_Com.hpp"
#include "botcraft/Network/Authentifier.hpp"
#include "botcraft/Network/AESEncrypter.hpp"
#if USE_COMPRESSION
#include "botcraft/Network/Compression.hpp"
#endif
#include "botcraft/Utilities/Logger.hpp"
#if PROTOCOL_VERSION > 758
#include "botcraft/Utilities/StringUtilities.hpp"
#endif


#include "protocolCraft/BinaryReadWrite.hpp"
#include "protocolCraft/MessageFactory.hpp"

namespace Botcraft
{
    NetworkManager::NetworkManager(const std::string& address, const std::string& login, const bool force_microfost_auth)
    {
        com = nullptr;

        // Online mode with Microsoft login flow
        if (login.empty() || force_microfost_auth)
        {
            authentifier = std::make_shared<Authentifier>();
            if (!authentifier->AuthMicrosoft(login))
            {
                throw std::runtime_error("Error trying to authenticate on Mojang server using Microsoft auth flow");
            }
            name = authentifier->GetPlayerDisplayName();
        }
        // Online mode false
        else
        {
            authentifier = nullptr;
            name = login;
        }

        compression = -1;
        AddHandler(this);

        state = ProtocolCraft::ConnectionState::Handshake;

        //Start the thread to process the incoming packets
        m_thread_process = std::thread(&NetworkManager::WaitForNewPackets, this);

        com = std::make_shared<TCP_Com>(address, std::bind(&NetworkManager::OnNewRawData, this, std::placeholders::_1));

        //Let some time to initialize the communication before actually send data
        // TODO: make this in a cleaner way?
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::shared_ptr<ProtocolCraft::ServerboundClientIntentionPacket> handshake_msg = std::make_shared<ProtocolCraft::ServerboundClientIntentionPacket>();
        handshake_msg->SetProtocolVersion(PROTOCOL_VERSION);
        handshake_msg->SetHostName(com->GetIp());
        handshake_msg->SetPort(com->GetPort());
        handshake_msg->SetIntention((int)ProtocolCraft::ConnectionState::Login);
        Send(handshake_msg);

        state = ProtocolCraft::ConnectionState::Login;

        std::shared_ptr<ProtocolCraft::ServerboundHelloPacket> loginstart_msg = std::make_shared<ProtocolCraft::ServerboundHelloPacket>();
#if PROTOCOL_VERSION < 759
        loginstart_msg->SetGameProfile(name);
#else
        loginstart_msg->SetName(name);
        if (authentifier)
        {
            ProtocolCraft::ProfilePublicKey key;
            key.SetTimestamp(authentifier->GetKeyTimestamp());
            key.SetKey(RSAToBytes(authentifier->GetPublicKey()));
            key.SetSignature(DecodeBase64(authentifier->GetKeySignature()));

            loginstart_msg->SetPublicKey(key);
#if PROTOCOL_VERSION > 759
            loginstart_msg->SetProfileId(authentifier->GetPlayerUUID());
#endif
        }
#endif
        Send(loginstart_msg);
    }

    NetworkManager::NetworkManager(const ProtocolCraft::ConnectionState constant_connection_state)
    {
        state = constant_connection_state;
        compression = -1;
    }

    NetworkManager::~NetworkManager()
    {
        state = ProtocolCraft::ConnectionState::None;

        if (com)
        {
            com->close();
        }

        process_condition.notify_all();

        if (m_thread_process.joinable())
        {
            m_thread_process.join();
        }
        compression = -1;

        com.reset();
    }

    void NetworkManager::AddHandler(ProtocolCraft::Handler* h)
    {
        subscribed.push_back(h);
    }

    void NetworkManager::Send(const std::shared_ptr<ProtocolCraft::Message> msg)
    {
        if (com)
        {
            std::lock_guard<std::mutex> lock(mutex_send);
            std::vector<unsigned char> msg_data;
            msg->Write(msg_data);
            if (compression == -1)
            {
                com->SendPacket(msg_data);
            }
            else
            {
#ifdef USE_COMPRESSION
                if (msg_data.size() < compression)
                {
                    msg_data.insert(msg_data.begin(), 0x00);
                    com->SendPacket(msg_data);
                }
                else
                {
                    std::vector<unsigned char> compressed_msg;
                    ProtocolCraft::WriteData<ProtocolCraft::VarInt>(msg_data.size(), compressed_msg);
                    std::vector<unsigned char> compressed_data = Compress(msg_data);
                    compressed_msg.insert(compressed_msg.end(), compressed_data.begin(), compressed_data.end());
                    com->SendPacket(compressed_msg);
                }
#else
                throw(std::runtime_error("Program compiled without ZLIB. Cannot send compressed message"));
#endif
            }
        }
    }

    const ProtocolCraft::ConnectionState NetworkManager::GetConnectionState() const
    {
        return state;
    }

    const std::string& NetworkManager::GetMyName() const
    {
        return name;
    }

    void NetworkManager::SendChatMessage(const std::string& message)
    {
        std::shared_ptr<ProtocolCraft::ServerboundChatPacket> chat_message = std::make_shared<ProtocolCraft::ServerboundChatPacket>();
        chat_message->SetMessage(message);
#if PROTOCOL_VERSION > 758
        chat_message->SetSignedPreview(false);
        if (authentifier)
        {
            long long int salt, timestamp;
            std::vector<unsigned char> signature;
#if PROTOCOL_VERSION < 760
            signature = authentifier->GetMessageSignature(message, salt, timestamp);
#else
            ProtocolCraft::LastSeenMessagesUpdate last_seen_update;
            {
                std::lock_guard<std::mutex> lock_messages(mutex_chat);
                last_seen_update.SetLastSeen({ last_seen.begin(), last_seen.begin() + std::min(static_cast<int>(last_seen.size()), 5) });
                signature = authentifier->GetMessageSignature(message, last_signature_sent, last_seen_update.GetLastSeen(), salt, timestamp);
                // Update last signature with current one for the next message
                last_signature_sent = signature;
            }
#endif
            if (signature.empty())
            {
                throw std::runtime_error("Empty chat message signature.");
            }
            chat_message->SetTimestamp(timestamp);

#if PROTOCOL_VERSION < 760
            ProtocolCraft::SaltSignature salt_signature;
            salt_signature.SetSalt(salt);
            salt_signature.SetSignature(signature);

            chat_message->SetSaltSignature(salt_signature);
#else
            chat_message->SetSalt(salt);
            chat_message->SetSignature(signature);
            chat_message->SetLastSeenMessages(last_seen_update);
#endif
        }
        // Offline mode, empty signature
        else
        {
            chat_message->SetTimestamp(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        }
#endif
        Send(chat_message);
    }

    void NetworkManager::WaitForNewPackets()
    {
        Logger::GetInstance().RegisterThread("NetworkPacketProcessing");
        while (state != ProtocolCraft::ConnectionState::None)
        {
            {
                std::unique_lock<std::mutex> lck(mutex_process);
                process_condition.wait(lck);
            }
            while (!packets_to_process.empty())
            {
                std::vector<unsigned char> packet;
                { // process_guard scope
                    std::lock_guard<std::mutex> process_guard(mutex_process);
                    if (!packets_to_process.empty())
                    {
                        packet = packets_to_process.front();
                        packets_to_process.pop();
                    }
                }
                if (packet.size() > 0)
                {
                    if (compression == -1)
                    {
                        ProcessPacket(packet);
                    }
                    else
                    {
#ifdef USE_COMPRESSION
                        size_t length = packet.size();
                        ProtocolCraft::ReadIterator iter = packet.begin();
                        int data_length = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length);

                        //Packet not compressed
                        if (data_length == 0)
                        {
                            //Erase the first 0
                            packet.erase(packet.begin());
                            ProcessPacket(packet);
                        }
                        //Packet compressed
                        else
                        {
                            int size_varint = packet.size() - length;

                            std::vector<unsigned char> uncompressed_msg = Decompress(packet, size_varint);
                            ProcessPacket(uncompressed_msg);
                        }
#else
                        throw(std::runtime_error("Program compiled without USE_COMPRESSION. Cannot read compressed message"));
#endif
                    }
                }
            }
        }
    }

    void NetworkManager::ProcessPacket(const std::vector<unsigned char>& packet)
    {
        if (packet.empty())
        {
            return;
        }

        std::vector<unsigned char>::const_iterator packet_iterator = packet.begin();
        size_t length = packet.size();

        int packet_id = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(packet_iterator, length);

        std::shared_ptr<ProtocolCraft::Message> msg = ProtocolCraft::MessageFactory::CreateMessageClientbound(packet_id, state);

        if (msg)
        {
            msg->Read(packet_iterator, length);
            for (int i = 0; i < subscribed.size(); i++)
            {
                msg->Dispatch(subscribed[i]);
            }
        }
    }
    
    void NetworkManager::OnNewRawData(const std::vector<unsigned char>& packet)
    {
        std::unique_lock<std::mutex> lck(mutex_process);
        packets_to_process.push(packet);
        process_condition.notify_all();
    }

#if PROTOCOL_VERSION > 759
    void NetworkManager::NewMessageSeen(const ProtocolCraft::LastSeenMessagesEntry& header)
    {
        std::lock_guard<std::mutex> lock_messages(mutex_chat);

        // Push new header in front
        last_seen.push_front(header);

        // Remove old messages from the same player
        for (int i = 1; i < last_seen.size(); ++i)
        {
            if (last_seen[i].GetProfileId() == header.GetProfileId())
            {
                last_seen.erase(last_seen.begin() + i);
            }
        }

        // Limit the size to 5 messages
        while (last_seen.size() > 5)
        {
            last_seen.pop_back();
        }
    }
#endif

    void NetworkManager::Handle(ProtocolCraft::Message& msg)
    {

    }

    void NetworkManager::Handle(ProtocolCraft::ClientboundLoginCompressionPacket& msg)
    {
        compression = msg.GetCompressionThreshold();
    }

    void NetworkManager::Handle(ProtocolCraft::ClientboundGameProfilePacket& msg)
    {
        state = ProtocolCraft::ConnectionState::Play;
    }

    void NetworkManager::Handle(ProtocolCraft::ClientboundHelloPacket& msg)
    {
        if (authentifier == nullptr)
        {
            throw(std::runtime_error("Authentication asked while no valid account has been provided, make sure to connect with a valid Mojang or Microsoft Account"));
            return;
        }

#ifdef USE_ENCRYPTION
        std::shared_ptr<AESEncrypter> encrypter = std::make_shared<AESEncrypter>();

        std::vector<unsigned char> raw_shared_secret;
        std::vector<unsigned char> encrypted_shared_secret;

#if PROTOCOL_VERSION < 759
        std::vector<unsigned char> encrypted_nonce;
        encrypter->Init(msg.GetPublicKey(), msg.GetNonce(),
            raw_shared_secret, encrypted_nonce, encrypted_shared_secret);
#else
        std::vector<unsigned char> salted_nonce_signature;
        long long int salt;
        encrypter->Init(msg.GetPublicKey(), msg.GetNonce(), authentifier->GetPrivateKey(),
            raw_shared_secret, encrypted_shared_secret,
            salt, salted_nonce_signature);
#endif

        authentifier->JoinServer(msg.GetServerID(), raw_shared_secret, msg.GetPublicKey());

        std::shared_ptr<ProtocolCraft::ServerboundKeyPacket> response_msg = std::make_shared<ProtocolCraft::ServerboundKeyPacket>();
        response_msg->SetKeyBytes(encrypted_shared_secret);

#if PROTOCOL_VERSION < 759
        // Pre-1.19 behaviour, send encrypted nonce
        response_msg->SetNonce(encrypted_nonce);
#else
        // 1.19+ behaviour, send salted nonce signature
        ProtocolCraft::SaltSignature salt_signature;
        salt_signature.SetSalt(salt);
        salt_signature.SetSignature(salted_nonce_signature);
        response_msg->SetSaltSignature(salt_signature);
#endif

        Send(response_msg);

        // Enable encryption from now on
        com->SetEncrypter(encrypter);
#else
        throw(std::runtime_error("Your version of botcraft doesn't support encryption. Either run your server with online-mode=false or recompile botcraft"));
#endif
    }

    void NetworkManager::Handle(ProtocolCraft::ClientboundKeepAlivePacket& msg)
    {
        std::shared_ptr<ProtocolCraft::ServerboundKeepAlivePacket> keep_alive_msg = std::make_shared<ProtocolCraft::ServerboundKeepAlivePacket>();
        keep_alive_msg->SetId_(msg.GetId_());
        Send(keep_alive_msg);
    }

#if PROTOCOL_VERSION > 340
    void NetworkManager::Handle(ProtocolCraft::ClientboundCustomQueryPacket& msg)
    {
        // Vanilla like response when asked by fabric API
        // Not implemented in fabric before December 05 2020,
        // so not necessary before version 1.16.4
#if PROTOCOL_VERSION > 753
        if (msg.GetIdentifier().GetFull() == "fabric-networking-api-v1:early_registration")
        {
            std::shared_ptr<ProtocolCraft::ServerboundCustomQueryPacket> custom_query_response = std::make_shared<ProtocolCraft::ServerboundCustomQueryPacket>();
            custom_query_response->SetTransactionId(msg.GetTransactionId());
            custom_query_response->SetData({});
            Send(custom_query_response);
            return;
        }
#endif
    }
#endif

#if PROTOCOL_VERSION > 759
    void NetworkManager::Handle(ProtocolCraft::ClientboundPlayerChatPacket& msg)
    {
        ProtocolCraft::LastSeenMessagesEntry last_seen;
        last_seen.SetLastSignature(msg.GetMessage_().GetHeaderSignature());
        last_seen.SetProfileId(msg.GetMessage_().GetSignedHeader().GetSender());
        NewMessageSeen(last_seen);
    }

    void NetworkManager::Handle(ProtocolCraft::ClientboundPlayerChatHeaderPacket& msg)
    {
        ProtocolCraft::LastSeenMessagesEntry last_seen;
        last_seen.SetLastSignature(msg.GetHeaderSignature());
        last_seen.SetProfileId(msg.GetHeader().GetSender());
        NewMessageSeen(last_seen);
    }
#endif
}

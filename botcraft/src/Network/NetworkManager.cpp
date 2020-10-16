#include <functional>

#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Network/TCP_Com.hpp"
#include "botcraft/Network/Authentifier.hpp"
#include "botcraft/Network/AESEncrypter.hpp"

#if USE_COMPRESSION
#include "botcraft/Network/Compression.hpp"
#endif

#include "protocolCraft/BinaryReadWrite.hpp"
#include "protocolCraft/MessageFactory.hpp"

namespace Botcraft
{
    NetworkManager::NetworkManager(const std::string& address, const std::string& login, const std::string& password)
    {
        com = nullptr;
        authentifier = nullptr;

        compression = -1;
        AddHandler(this);

        state = ProtocolCraft::ConnectionState::Handshake;

        //Start the thread to process the incoming packets
        m_thread_process = std::thread(&NetworkManager::WaitForNewPackets, this);

        com = std::shared_ptr<TCP_Com>(new TCP_Com(address, std::bind(&NetworkManager::OnNewRawData, this, std::placeholders::_1)));

        //Let some time to initialize the communication before actually send data
        // TODO: make this in a cleaner way?
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::shared_ptr<ProtocolCraft::Handshake> handshake_msg(new ProtocolCraft::Handshake);
        handshake_msg->SetProtocolVersion(PROTOCOL_VERSION);
        handshake_msg->SetServerAddress(com->GetIp());
        handshake_msg->SetServerPort(com->GetPort());
        handshake_msg->SetNextState((int)ProtocolCraft::ConnectionState::Login);
        Send(handshake_msg);

        state = ProtocolCraft::ConnectionState::Login;

        // Online mode false
        if (password == "")
        {
            name = login;
        }
        // Online mode true
        else
        {
            authentifier = std::shared_ptr<Authentifier>(new Authentifier());
            if (!authentifier->AuthToken(login, password))
            {
                throw std::runtime_error("Error trying to authenticate on Mojang server");
            }
            name = authentifier->GetPlayerDisplayName();
        }

        std::shared_ptr<ProtocolCraft::LoginStart> loginstart_msg(new ProtocolCraft::LoginStart);
        loginstart_msg->SetName_(name);
        Send(loginstart_msg);
    }

    NetworkManager::NetworkManager(const ProtocolCraft::ConnectionState constant_connection_state)
    {
        state = constant_connection_state;
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
                    ProtocolCraft::WriteVarInt(msg_data.size(), compressed_msg);
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

    void NetworkManager::WaitForNewPackets()
    {
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
                        packets_to_process.pop_front();
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
                        int data_length = ProtocolCraft::ReadVarInt(iter, length);

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

        int packet_id = ProtocolCraft::ReadVarInt(packet_iterator, length);

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
        packets_to_process.push_back(packet);
        process_condition.notify_all();
    }

    void NetworkManager::Handle(ProtocolCraft::Message& msg)
    {

    }

    void NetworkManager::Handle(ProtocolCraft::SetCompression& msg)
    {
        compression = msg.GetThreshold();
    }

    void NetworkManager::Handle(ProtocolCraft::LoginSuccess& msg)
    {
        state = ProtocolCraft::ConnectionState::Play;
    }

    void NetworkManager::Handle(ProtocolCraft::EncryptionRequest& msg)
    {
        if (authentifier == nullptr)
        {
            throw(std::runtime_error("Authentication asked while no password has been provided, make sure to connect with a valid Mojang Account"));
            return;
        }

#ifdef USE_ENCRYPTION
        std::shared_ptr<AESEncrypter> encrypter = std::shared_ptr<AESEncrypter>(new AESEncrypter());

        std::vector<unsigned char> encrypted_token;
        std::vector<unsigned char> encrypted_shared_secret;
        std::vector<unsigned char> raw_shared_secret;

        encrypter->Init(msg.GetPublicKey(), msg.GetVerifyToken(),
            raw_shared_secret, encrypted_token, encrypted_shared_secret);

        authentifier->JoinServer(msg.GetServerID(), raw_shared_secret, msg.GetPublicKey());

        std::shared_ptr<ProtocolCraft::EncryptionResponse> response_msg(new ProtocolCraft::EncryptionResponse);
        response_msg->SetSharedSecretLength(encrypted_shared_secret.size());
        response_msg->SetSharedSecret(encrypted_shared_secret);
        response_msg->SetVerifyTokenLength(encrypted_token.size());
        response_msg->SetVerifyToken(encrypted_token);

        Send(response_msg);

        // Enable encryption from now on
        com->SetEncrypter(encrypter);
#else
        throw(std::runtime_error("Your version of botcraft doesn't support encryption. Either run your server with online-mode=false or recompile botcraft"));
#endif
    }

    void NetworkManager::Handle(ProtocolCraft::KeepAliveClientbound& msg)
    {
        std::shared_ptr<ProtocolCraft::KeepAliveServerbound> keep_alive_msg(new ProtocolCraft::KeepAliveServerbound);
        keep_alive_msg->SetKeepAliveId(msg.GetKeepAliveId());
        Send(keep_alive_msg);
    }
}
#pragma once

#include "protocolCraft/Handler.hpp"
#include "protocolCraft/enums.hpp"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "botcraft/Network/LastSeenMessagesTracker.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include <atomic>
#endif

namespace Botcraft
{
    class TCP_Com;
    class Authentifier;

    class NetworkManager : public ProtocolCraft::Handler
    {
    public:
        NetworkManager(const std::string& address, const std::string& login, const bool force_microsoft_auth, const std::vector<ProtocolCraft::Handler*>& handlers = {});
        // Used to create a dummy network manager that does not fire any packet
        // but is always in constant_connection_state
        NetworkManager(const ProtocolCraft::ConnectionState constant_connection_state);
        ~NetworkManager();

        void Stop();

        void AddHandler(ProtocolCraft::Handler* h);
        void Send(const std::shared_ptr<ProtocolCraft::Packet> packet);
        const ProtocolCraft::ConnectionState GetConnectionState() const;
        const std::string& GetMyName() const;

        void SendChatMessage(const std::string& message);
        void SendChatCommand(const std::string& command);

        std::thread::id GetProcessingThreadId() const;

    private:
        void WaitForNewPackets();
        void ProcessPacket(const std::vector<unsigned char>& bytes);
        void OnNewRawData(const std::vector<unsigned char>& bytes);


        virtual void Handle(ProtocolCraft::ClientboundLoginCompressionPacket& packet) override;
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket& packet) override;
#else
        virtual void Handle(ProtocolCraft::ClientboundLoginFinishedPacket& packet) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundHelloPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundKeepAlivePacket& packet) override;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        virtual void Handle(ProtocolCraft::ClientboundPingPacket& packet) override;
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        virtual void Handle(ProtocolCraft::ClientboundCustomQueryPacket& packet) override;
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        virtual void Handle(ProtocolCraft::ClientboundPlayerChatPacket& packet) override;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        virtual void Handle(ProtocolCraft::ClientboundPlayerChatHeaderPacket& packet) override;
#endif
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& packet) override;
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        virtual void Handle(ProtocolCraft::ClientboundFinishConfigurationPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundKeepAliveConfigurationPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundPingConfigurationPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundStartConfigurationPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundChunkBatchStartPacket& packet) override;
        virtual void Handle(ProtocolCraft::ClientboundChunkBatchFinishedPacket& packet) override;
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        virtual void Handle(ProtocolCraft::ClientboundSelectKnownPacksPacket& packet) override;
#endif

    private:
        std::vector<ProtocolCraft::Handler*> subscribed;

        std::shared_ptr<TCP_Com> com;
        std::shared_ptr<Authentifier> authentifier;
        ProtocolCraft::ConnectionState state;

        std::thread m_thread_process;//Thread running to process incoming packets without blocking com

        std::queue<std::vector<unsigned char> > packets_to_process;
        std::mutex mutex_process;
        std::condition_variable process_condition;
        int compression;

        std::mutex mutex_send;

        std::string name;

#if PROTOCOL_VERSION > 759 /* > 1.19 */
        LastSeenMessagesTracker chat_context;
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        ProtocolCraft::UUID chat_session_uuid{};
        std::atomic<int> message_sent_index;
#endif

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        std::chrono::steady_clock::time_point chunk_batch_start_time;
#endif

    };
}

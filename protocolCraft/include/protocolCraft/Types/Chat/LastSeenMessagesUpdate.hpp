#if PROTOCOL_VERSION > 759
#pragma once


#include "protocolCraft/NetworkType.hpp"

#if PROTOCOL_VERSION < 761
#include <vector>

#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"
#endif

namespace ProtocolCraft
{
    class LastSeenMessagesUpdate : public NetworkType
    {
    public:
        virtual ~LastSeenMessagesUpdate() override
        {

        }


#if PROTOCOL_VERSION < 761
        void SetLastSeen(const std::vector<LastSeenMessagesEntry>& last_seen_)
        {
            last_seen = last_seen_;
        }

        void SetLastReceived(const LastSeenMessagesEntry& last_received_)
        {
            last_received = last_received_;
        }
#else
        void SetOffset(const int offset_)
        {
            offset = offset_;
        }

        void SetAcknowledged(const std::bitset<20>& acknowledged_)
        {
            acknowledged = acknowledged_;
        }
#endif


#if PROTOCOL_VERSION < 761
        const std::vector<LastSeenMessagesEntry>& GetLastSeen() const
        {
            return last_seen;
        }

        const LastSeenMessagesEntry& GetLastReceived() const
        {
            return last_received;
        }
#else
        const int GetOffset() const
        {
            return offset;
        }

        const std::bitset<20>& GetAcknowledged() const
        {
            return acknowledged;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 761
            const int last_seen_size = ReadData<VarInt>(iter, length);
            last_seen = std::vector<LastSeenMessagesEntry>(last_seen_size);
            for (int i = 0; i < last_seen_size; ++i)
            {
                last_seen[i].Read(iter, length);
            }
            const bool has_last_received = ReadData<bool>(iter, length);
            if (has_last_received)
            {
                last_received = ReadData<LastSeenMessagesEntry>(iter, length);
            }
#else
            offset = ReadData<VarInt>(iter, length);
            acknowledged = ReadBitset<20>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION < 761
            WriteData<VarInt>(static_cast<int>(last_seen.size()), container);
            for (int i = 0; i < last_seen.size(); ++i)
            {
                last_seen[i].Write(container);
            }
            bool has_last_received = false;
            for (int i = 0; i < last_received.GetLastSignature().size(); ++i)
            {
                if (last_received.GetLastSignature()[i] != 0)
                {
                    has_last_received = true;
                    break;
                }
            }
            WriteData<bool>(has_last_received, container);
            if (has_last_received)
            {
                WriteData<LastSeenMessagesEntry>(last_received, container);
            }
#else
            WriteData<VarInt>(offset, container);
            WriteBitset<20>(acknowledged, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 761
            output["last_seen"] = nlohmann::json::array();
            for (int i = 0; i < last_seen.size(); ++i)
            {
                output["last_seen"].push_back(last_seen[i].Serialize());
            };
            bool has_last_received = false;
            for (int i = 0; i < last_received.GetLastSignature().size(); ++i)
            {
                if (last_received.GetLastSignature()[i] != 0)
                {
                    has_last_received = true;
                    break;
                }
            }
            if (has_last_received)
            {
                output["last_received"] = last_received.Serialize();
            }
#else
            output["offset"] = offset;
            output["acknowledged"] = acknowledged.to_string();
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761
        std::vector<LastSeenMessagesEntry> last_seen;
        LastSeenMessagesEntry last_received;
#else
        int offset;
        std::bitset<20> acknowledged;
#endif
    };
} // ProtocolCraft
#endif

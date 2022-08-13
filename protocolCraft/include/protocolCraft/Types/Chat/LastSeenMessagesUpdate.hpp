#if PROTOCOL_VERSION > 759
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"

namespace ProtocolCraft
{
    class LastSeenMessagesUpdate : public NetworkType
    {
    public:
        virtual ~LastSeenMessagesUpdate() override
        {

        }


        void SetLastSeen(const std::vector<LastSeenMessagesEntry>& last_seen_)
        {
            last_seen = last_seen_;
        }

        void SetLastReceived(const LastSeenMessagesEntry& last_received_)
        {
            last_received = last_received_;
        }


        const std::vector<LastSeenMessagesEntry>& GetLastSeen() const
        {
            return last_seen;
        }

        const LastSeenMessagesEntry& GetLastReceived() const
        {
            return last_received;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            const int last_seen_size = ReadData<VarInt>(iter, length);
            last_seen = std::vector<LastSeenMessagesEntry>(last_seen_size);
            for (int i = 0; i < last_seen_size; ++i)
            {
                last_seen[i].Read(iter, length);
            }
            const bool has_last_received = ReadData<bool>(iter, length);
            if (has_last_received)
            {
                last_received.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(last_seen.size(), container);
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
                last_received.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

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

            return output;
        }

    private:
        std::vector<LastSeenMessagesEntry> last_seen;
        LastSeenMessagesEntry last_received;
    };
} // ProtocolCraft
#endif

#if PROTOCOL_VERSION > 759
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/ChatMessageContent.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"

namespace ProtocolCraft
{
    class SignedMessageBody : public NetworkType
    {
    public:
        virtual ~SignedMessageBody() override
        {

        }


        void SetContent(const ChatMessageContent& content_)
        {
            content = content_;
        }

        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

        void SetSalt(const long long int salt_)
        {
            salt = salt_;
        }

        void SetLastSeen(const std::vector<LastSeenMessagesEntry>& last_seen_)
        {
            last_seen = last_seen_;
        }
    

        const ChatMessageContent& GetContent() const
        {
            return content;
        }

        const long long int GetTimestamp() const
        {
            return timestamp;
        }

        const long long int GetSalt() const
        {
            return salt;
        }

        const std::vector<LastSeenMessagesEntry>& GetLastSeen() const
        {
            return last_seen;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            content.Read(iter, length);
            timestamp = ReadData<long long int>(iter, length);
            salt = ReadData<long long int>(iter, length);
            const int last_seen_size = ReadData<VarInt>(iter, length);
            last_seen = std::vector<LastSeenMessagesEntry>(last_seen_size);
            for (int i = 0; i < last_seen_size; ++i)
            {
                last_seen[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            content.Write(container);
            WriteData<long long int>(timestamp, container);
            WriteData<long long int>(salt, container);
            WriteData<VarInt>(last_seen.size(), container);
            for (int i = 0; i < last_seen.size(); ++i)
            {
                last_seen[i].Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["content"] = content.Serialize();
            output["timestamp"] = timestamp;
            output["salt"] = salt;
            output["last_seen"] = nlohmann::json::array();
            for (int i = 0; i < last_seen.size(); ++i)
            {
                output.push_back(last_seen[i].Serialize());
            }


            return output;
        }

    private:
        ChatMessageContent content;
        long long int timestamp;
        long long int salt;
        std::vector<LastSeenMessagesEntry> last_seen;
    };
} // ProtocolCraft
#endif

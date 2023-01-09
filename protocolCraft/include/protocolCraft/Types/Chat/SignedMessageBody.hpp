#if PROTOCOL_VERSION > 759
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION < 761
#include "protocolCraft/Types/Chat/ChatMessageContent.hpp"
#endif
#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"

namespace ProtocolCraft
{
    class SignedMessageBody : public NetworkType
    {
    public:
        virtual ~SignedMessageBody() override
        {

        }


#if PROTOCOL_VERSION < 761
        void SetContent(const ChatMessageContent& content_)
        {
            content = content_;
        }
#else
        void SetContent(const std::string& content_)
        {
            content = content_;
        }
#endif

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
    

#if PROTOCOL_VERSION < 761
        const ChatMessageContent& GetContent() const
        {
            return content;
        }
#else
        const std::string& GetContent() const
        {
            return content;
        }
#endif

        long long int GetTimestamp() const
        {
            return timestamp;
        }

        long long int GetSalt() const
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
#if PROTOCOL_VERSION < 761
            content = ReadData<ChatMessageContent>(iter, length);
#else
            content = ReadData<std::string>(iter, length);
#endif
            timestamp = ReadData<long long int>(iter, length);
            salt = ReadData<long long int>(iter, length);
            last_seen = ReadVector<LastSeenMessagesEntry>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION < 761
            WriteData<ChatMessageContent>(content, container);
#else
            WriteData<std::string>(content, container);
#endif
            WriteData<long long int>(timestamp, container);
            WriteData<long long int>(salt, container);
            WriteVector<LastSeenMessagesEntry>(last_seen, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 761
            output["content"] = content.Serialize();
#else
            output["content"] = content;
#endif
            output["timestamp"] = timestamp;
            output["salt"] = salt;
            output["last_seen"] = nlohmann::json::array();
            for (const auto& l : last_seen)
            {
                output["last_seen"].push_back(l.Serialize());
            }


            return output;
        }

    private:
#if PROTOCOL_VERSION < 761
        ChatMessageContent content;
#else
        std::string content;
#endif
        long long int timestamp;
        long long int salt;
        std::vector<LastSeenMessagesEntry> last_seen;
    };
} // ProtocolCraft
#endif

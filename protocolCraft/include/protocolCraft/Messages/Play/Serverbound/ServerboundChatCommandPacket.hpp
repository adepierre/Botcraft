#if PROTOCOL_VERSION > 758
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 759
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundChatCommandPacket : public BaseMessage<ServerboundChatCommandPacket>
    {
    public:
#if PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x04;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Chat Command";

        virtual ~ServerboundChatCommandPacket() override
        {

        }

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

#if PROTOCOL_VERSION > 759
        void SetSalt(const long long int salt_)
        {
            salt = salt_;
        }
#endif

        void SetArgumentSignatures(const std::map<std::string, std::vector<unsigned char> >& argument_signatures_)
        {
            argument_signatures = argument_signatures_;
        }

#if PROTOCOL_VERSION < 761
        void SetSignedPreview(const bool signed_preview_)
        {
            signed_preview = signed_preview_;
        }
#endif

#if PROTOCOL_VERSION > 759
        void SetLastSeenMessages(const LastSeenMessagesUpdate& last_seen_messages_)
        {
            last_seen_messages = last_seen_messages_;
        }
#endif


        const std::string& GetCommand() const
        {
            return command;
        }

        long long int GetTimestamp() const
        {
            return timestamp;
        }

#if PROTOCOL_VERSION > 759
        long long int GetSalt() const
        {
            return salt;
        }
#endif

        const std::map<std::string, std::vector<unsigned char> >& GetArgumentSignatures() const
        {
            return argument_signatures;
        }

#if PROTOCOL_VERSION < 761
        bool GetSignedPreview() const
        {
            return signed_preview;
        }
#endif

#if PROTOCOL_VERSION > 759
        const LastSeenMessagesUpdate& GetLastSeenMessages() const
        {
            return last_seen_messages;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            command = ReadData<std::string>(iter, length);
            timestamp = ReadData<long long int>(iter, length);
#if PROTOCOL_VERSION > 759
            salt = ReadData<long long int>(iter, length);
#endif
            argument_signatures = ReadMap<std::string, std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const std::string key = ReadData<std::string>(i, l);
                    const std::vector<unsigned char> val = ReadVector<unsigned char>(i, l);

                    return std::make_pair(key, val);
                }
            );
#if PROTOCOL_VERSION < 761
            signed_preview = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 759
            last_seen_messages = ReadData<LastSeenMessagesUpdate>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(command, container);
            WriteData<long long int>(timestamp, container);
#if PROTOCOL_VERSION > 759
            WriteData<long long int>(salt, container);
#endif
            WriteMap<std::string, std::vector<unsigned char>>(argument_signatures, container,
                [](const std::pair<const std::string, std::vector<unsigned char>>& p, WriteContainer& c)
                {
                    WriteData<std::string>(p.first, c);
                    WriteVector<unsigned char>(p.second, c);
                }
            );
#if PROTOCOL_VERSION < 761
            WriteData<bool>(signed_preview, container);
#endif
#if PROTOCOL_VERSION > 759
            WriteData<LastSeenMessagesUpdate>(last_seen_messages, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["command"] = command;
            output["timestamp"] = timestamp;
#if PROTOCOL_VERSION > 759
            output["salt"] = salt;
#endif
            output["argument_signatures"] = Json::Object();
            for (const auto& s: argument_signatures)
            {
                output["argument_signatures"][s.first] = "Vector of " + std::to_string(s.second.size()) + " unsigned char";
            }
#if PROTOCOL_VERSION < 761
            output["signed_preview"] = signed_preview;
#endif
#if PROTOCOL_VERSION > 759
            output["last_seen_messages"] = last_seen_messages;
#endif


            return output;
        }

    private:
        std::string command;
        long long int timestamp;
#if PROTOCOL_VERSION > 759
        long long int salt;
#endif
        std::map<std::string, std::vector<unsigned char> > argument_signatures;
#if PROTOCOL_VERSION < 761
        bool signed_preview;
#endif
#if PROTOCOL_VERSION > 759
        LastSeenMessagesUpdate last_seen_messages;
#endif
    };
} //ProtocolCraft
#endif

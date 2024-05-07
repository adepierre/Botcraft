#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace ProtocolCraft
{
    class ServerboundChatCommandSignedPacket : public BaseMessage<ServerboundChatCommandSignedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Command Signed";

        virtual ~ServerboundChatCommandSignedPacket() override
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

        void SetSalt(const long long int salt_)
        {
            salt = salt_;
        }

        void SetArgumentSignatures(const std::map<std::string, std::vector<unsigned char> >& argument_signatures_)
        {
            argument_signatures = argument_signatures_;
        }

        void SetLastSeenMessages(const LastSeenMessagesUpdate& last_seen_messages_)
        {
            last_seen_messages = last_seen_messages_;
        }


        const std::string& GetCommand() const
        {
            return command;
        }

        long long int GetTimestamp() const
        {
            return timestamp;
        }

        long long int GetSalt() const
        {
            return salt;
        }

        const std::map<std::string, std::vector<unsigned char> >& GetArgumentSignatures() const
        {
            return argument_signatures;
        }

        const LastSeenMessagesUpdate& GetLastSeenMessages() const
        {
            return last_seen_messages;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            command = ReadData<std::string>(iter, length);
            timestamp = ReadData<long long int>(iter, length);
            salt = ReadData<long long int>(iter, length);
            argument_signatures = ReadMap<std::string, std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const std::string key = ReadData<std::string>(i, l);
                    const std::vector<unsigned char> val = ReadVector<unsigned char>(i, l);

                    return std::make_pair(key, val);
                }
            );
            last_seen_messages = ReadData<LastSeenMessagesUpdate>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(command, container);
            WriteData<long long int>(timestamp, container);
            WriteData<long long int>(salt, container);
            WriteMap<std::string, std::vector<unsigned char>>(argument_signatures, container,
                [](const std::pair<const std::string, std::vector<unsigned char>>& p, WriteContainer& c)
                {
                    WriteData<std::string>(p.first, c);
                    WriteVector<unsigned char>(p.second, c);
                }
            );
            WriteData<LastSeenMessagesUpdate>(last_seen_messages, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["command"] = command;
            output["timestamp"] = timestamp;
            output["salt"] = salt;
            output["argument_signatures"] = Json::Object();
            for (const auto& s: argument_signatures)
            {
                output["argument_signatures"][s.first] = "Vector of " + std::to_string(s.second.size()) + " unsigned char";
            }
            output["last_seen_messages"] = last_seen_messages;


            return output;
        }

    private:
        std::string command;
        long long int timestamp = 0;
        long long int salt = 0;
        std::map<std::string, std::vector<unsigned char> > argument_signatures;
        LastSeenMessagesUpdate last_seen_messages;
    };
} //ProtocolCraft
#endif

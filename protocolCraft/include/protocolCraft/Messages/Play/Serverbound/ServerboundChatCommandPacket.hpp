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
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x03;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x04;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Command";
        }

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

        void SetSignedPreview(const bool signed_preview_)
        {
            signed_preview = signed_preview_;
        }

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

        const long long int GetTimestamp() const
        {
            return timestamp;
        }

#if PROTOCOL_VERSION > 759
        const long long int GetSalt() const
        {
            return salt;
        }
#endif

        const std::map<std::string, std::vector<unsigned char> >& GetArgumentSignatures() const
        {
            return argument_signatures;
        }

        const bool GetSignedPreview() const
        {
            return signed_preview;
        }

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
            const int argument_signatures_size = ReadData<VarInt>(iter, length);
            for (int i = 0; i < argument_signatures_size; ++i)
            {
                const std::string key = ReadData<std::string>(iter, length);
                const int value_size = ReadData<VarInt>(iter, length);
                argument_signatures[key] = ReadByteArray(iter, length, value_size);
            }
            signed_preview = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 759
            last_seen_messages.Read(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(command, container);
            WriteData<long long int>(timestamp, container);
#if PROTOCOL_VERSION > 759
            WriteData<long long int>(salt, container);
#endif
            WriteData<VarInt>(argument_signatures.size(), container);
            for (const auto& s: argument_signatures)
            {
                WriteData<std::string>(s.first, container);
                WriteData<VarInt>(s.second.size(), container);
                WriteByteArray(s.second, container);
            }
            WriteData<bool>(signed_preview, container);
#if PROTOCOL_VERSION > 759
            last_seen_messages.Write(container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["command"] = command;
            output["timestamp"] = timestamp;
#if PROTOCOL_VERSION > 759
            output["salt"] = salt;
#endif
            output["argument_signatures"] = nlohmann::json();
            for (const auto& s: argument_signatures)
            {
                output["signature"][s.first] = "Vector of " + std::to_string(s.second.size()) + " unsigned char";
            }
            output["signed_preview"] = signed_preview;
#if PROTOCOL_VERSION > 759
            output["last_seen_messages"] = last_seen_messages.Serialize();
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
        bool signed_preview;
#if PROTOCOL_VERSION > 759
        LastSeenMessagesUpdate last_seen_messages;
#endif
    };
} //ProtocolCraft
#endif

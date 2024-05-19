#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundChatCommandPacket : public BaseMessage<ServerboundChatCommandPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */ ||  \
      PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */
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

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

#if PROTOCOL_VERSION > 759 /* > 1.19 */
        void SetSalt(const long long int salt_)
        {
            salt = salt_;
        }
#endif

        void SetArgumentSignatures(const std::map<std::string, std::vector<unsigned char> >& argument_signatures_)
        {
            argument_signatures = argument_signatures_;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetSignedPreview(const bool signed_preview_)
        {
            signed_preview = signed_preview_;
        }
#endif

#if PROTOCOL_VERSION > 759 /* > 1.19 */
        void SetLastSeenMessages(const LastSeenMessagesUpdate& last_seen_messages_)
        {
            last_seen_messages = last_seen_messages_;
        }
#endif
#endif


        const std::string& GetCommand() const
        {
            return command;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        long long int GetTimestamp() const
        {
            return timestamp;
        }

#if PROTOCOL_VERSION > 759 /* > 1.19 */
        long long int GetSalt() const
        {
            return salt;
        }
#endif

        const std::map<std::string, std::vector<unsigned char> >& GetArgumentSignatures() const
        {
            return argument_signatures;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        bool GetSignedPreview() const
        {
            return signed_preview;
        }
#endif

#if PROTOCOL_VERSION > 759 /* > 1.19 */
        const LastSeenMessagesUpdate& GetLastSeenMessages() const
        {
            return last_seen_messages;
        }
#endif
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            command = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            timestamp = ReadData<long long int>(iter, length);
#if PROTOCOL_VERSION > 759 /* > 1.19 */
            salt = ReadData<long long int>(iter, length);
#endif
            argument_signatures = ReadData<std::map<std::string, std::vector<unsigned char>>>(iter, length);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            signed_preview = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
            last_seen_messages = ReadData<LastSeenMessagesUpdate>(iter, length);
#endif
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(command, container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<long long int>(timestamp, container);
#if PROTOCOL_VERSION > 759 /* > 1.19 */
            WriteData<long long int>(salt, container);
#endif
            WriteData<std::map<std::string, std::vector<unsigned char>>>(argument_signatures, container);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<bool>(signed_preview, container);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
            WriteData<LastSeenMessagesUpdate>(last_seen_messages, container);
#endif
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["command"] = command;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            output["timestamp"] = timestamp;
#if PROTOCOL_VERSION > 759 /* > 1.19 */
            output["salt"] = salt;
#endif
            output["argument_signatures"] = Json::Object();
            for (const auto& s: argument_signatures)
            {
                output["argument_signatures"][s.first] = "Vector of " + std::to_string(s.second.size()) + " unsigned char";
            }
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["signed_preview"] = signed_preview;
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
            output["last_seen_messages"] = last_seen_messages;
#endif
#endif


            return output;
        }

    private:
        std::string command;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        long long int timestamp = 0;
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        long long int salt = 0;
#endif
        std::map<std::string, std::vector<unsigned char> > argument_signatures;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        bool signed_preview = false;
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        LastSeenMessagesUpdate last_seen_messages;
#endif
#endif
    };
} //ProtocolCraft
#endif

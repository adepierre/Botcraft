#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"

namespace ProtocolCraft
{
    class ClientboundDisguisedChatPacket : public BaseMessage<ClientboundDisguisedChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x1B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Disguised Chat";

        virtual ~ClientboundDisguisedChatPacket() override
        {

        }


        void SetMessage(const Chat& message_)
        {
            message = message_;
        }

        void SetChatType(const ChatTypeBoundNetwork& chat_type_)
        {
            chat_type = chat_type_;
        }


        const Chat& GetMessage() const
        {
            return message;
        }

        const ChatTypeBoundNetwork& GetChatType() const
        {
            return chat_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            message = ReadData<Chat>(iter, length);
            chat_type = ReadData<ChatTypeBoundNetwork>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Chat>(message, container);
            WriteData<ChatTypeBoundNetwork>(chat_type, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["message"] = message;
            output["chat_type"] = chat_type;

            return output;
        }

    private:
        Chat message;
        ChatTypeBoundNetwork chat_type;
    };
} //ProtocolCraft
#endif

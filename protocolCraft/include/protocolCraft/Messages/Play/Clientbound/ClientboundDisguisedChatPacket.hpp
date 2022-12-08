#if PROTOCOL_VERSION > 760
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"

namespace ProtocolCraft
{
    class ClientboundDisguisedChatPacket : public BaseMessage<ClientboundDisguisedChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 761 // 1.19.3
            return 0x18;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Disguised Chat";
        }

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
            message.Read(iter, length);
            chat_type.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            message.Write(container);
            chat_type.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["message"] = message.Serialize();
            output["chat_type"] = chat_type.Serialize();

            return output;
        }

    private:
        Chat message;
        ChatTypeBoundNetwork chat_type;
    };
} //ProtocolCraft
#endif

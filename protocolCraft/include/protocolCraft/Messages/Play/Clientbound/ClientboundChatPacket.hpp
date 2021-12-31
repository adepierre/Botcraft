#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPacket : public BaseMessage<ClientboundChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0E;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0F;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x0F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat";
        }

        virtual ~ClientboundChatPacket() override
        {

        }

        void SetMessage(const Chat& message_)
        {
            message = message_;
        }

        void SetType(const char type_)
        {
            type = type_;
        }

#if PROTOCOL_VERSION > 717
        void SetSender(const UUID& sender_)
        {
            sender = sender_;
        }
#endif

        const Chat& GetMessage() const
        {
            return message;
        }

        const char GetType() const
        {
            return type;
        }

#if PROTOCOL_VERSION > 717
        const UUID& GetSender() const
        {
            return sender;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            message.Read(iter, length);
            type = ReadData<char>(iter, length);
#if PROTOCOL_VERSION > 717
            sender = ReadData<UUID>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            message.Write(container);
            WriteData<char>(type, container);
#if PROTOCOL_VERSION > 717
            WriteData<UUID>(sender, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["message"] = message.Serialize();
            output["type"] = type;
#if PROTOCOL_VERSION > 717
            output["sender"] = sender;
#endif

            return output;
        }

    private:
        Chat message;
        char type;
#if PROTOCOL_VERSION > 717
        UUID sender;
#endif
    };
} //ProtocolCraft
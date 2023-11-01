#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPacket : public BaseMessage<ClientboundChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat";

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

#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
        void SetSender(const UUID& sender_)
        {
            sender = sender_;
        }
#endif

        const Chat& GetMessage() const
        {
            return message;
        }

        char GetType() const
        {
            return type;
        }

#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
        const UUID& GetSender() const
        {
            return sender;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            message = ReadData<Chat>(iter, length);
            type = ReadData<char>(iter, length);
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
            sender = ReadData<UUID>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Chat>(message, container);
            WriteData<char>(type, container);
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
            WriteData<UUID>(sender, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["message"] = message;
            output["type"] = type;
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
            output["sender"] = sender;
#endif

            return output;
        }

    private:
        Chat message;
        char type = 0;
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
        UUID sender = {};
#endif
    };
} //ProtocolCraft
#endif

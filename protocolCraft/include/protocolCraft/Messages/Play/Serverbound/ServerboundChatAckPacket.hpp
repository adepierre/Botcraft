#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace ProtocolCraft
{
    class ServerboundChatAckPacket : public BaseMessage<ServerboundChatAckPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x03;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x03;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Ack";
        }

        virtual ~ServerboundChatAckPacket() override
        {

        }


#if PROTOCOL_VERSION < 761
        void SetLastSeenMessages(const LastSeenMessagesUpdate& last_seen_messages_)
        {
            last_seen_messages = last_seen_messages_;
        }
#else
        void SetOffset(const int offset_)
        {
            offset = offset_;
        }
#endif


#if PROTOCOL_VERSION < 761
        const LastSeenMessagesUpdate& GetLastSeenMessages() const
        {
            return last_seen_messages;
        }
#else
        const int GetOffset() const
        {
            return offset;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761
            last_seen_messages = ReadData<LastSeenMessagesUpdate>(iter, length);
#else
            offset = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761
            WriteData<LastSeenMessagesUpdate>(last_seen_messages, container);
#else
            WriteData<VarInt>(offset, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 761
            output["last_seen_message"] = last_seen_messages.Serialize();
#else
            output["offset"] = offset;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761
        LastSeenMessagesUpdate last_seen_messages;
#else
        int offset;
#endif

    };
} //ProtocolCraft
#endif

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

        
        void SetLastSeenMessages(const LastSeenMessagesUpdate& last_seen_messages_)
        {
            last_seen_messages = last_seen_messages_;
        }


        const LastSeenMessagesUpdate& GetLastSeenMessages() const
        {
            return last_seen_messages;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            last_seen_messages.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            last_seen_messages.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;
            
            output["last_seen_message"] = last_seen_messages.Serialize();

            return output;
        }

    private:
        LastSeenMessagesUpdate last_seen_messages;

    };
} //ProtocolCraft
#endif

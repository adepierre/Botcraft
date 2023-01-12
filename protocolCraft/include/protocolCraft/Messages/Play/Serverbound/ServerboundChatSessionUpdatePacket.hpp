#if PROTOCOL_VERSION > 760
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"

namespace ProtocolCraft
{
    class ServerboundChatSessionUpdatePacket : public BaseMessage<ServerboundChatSessionUpdatePacket>
    {
    public:
#if PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x20;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Chat Session Update";

        virtual ~ServerboundChatSessionUpdatePacket() override
        {

        }

        void SetChatSession(const RemoteChatSessionData& chat_session_)
        {
            chat_session = chat_session_;
        }


        const RemoteChatSessionData& GetChatSession() const
        {
            return chat_session;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            chat_session = ReadData<RemoteChatSessionData>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<RemoteChatSessionData>(chat_session, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["chat_session"] = chat_session;


            return output;
        }

    private:
        RemoteChatSessionData chat_session;
    };
} //ProtocolCraft
#endif

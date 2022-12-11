#if PROTOCOL_VERSION > 760
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"

namespace ProtocolCraft
{
    class ServerboundChatSessionUpdatePacket : public BaseMessage<ServerboundChatSessionUpdatePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 761 // 1.19.3
            return 0x20;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Session Update";
        }

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
            chat_session.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            chat_session.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["chat_session"] = chat_session.Serialize();


            return output;
        }

    private:
        RemoteChatSessionData chat_session;
    };
} //ProtocolCraft
#endif
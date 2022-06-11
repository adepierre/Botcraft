#if PROTOCOL_VERSION > 758
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSystemChatPacket : public BaseMessage<ClientboundSystemChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x5F;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "System Chat";
        }

        virtual ~ClientboundSystemChatPacket() override
        {

        }

        void SetContent(const Chat& signed_content_)
        {
            content = signed_content_;
        }

        void SetTypeId(const int type_id_)
        {
            type_id = type_id_;
        }


        const Chat& GetContent() const
        {
            return content;
        }

        const int GetTypeId() const
        {
            return type_id;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            content.Read(iter, length);
            type_id = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            content.Write(container);
            WriteData<VarInt>(type_id, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["content"] = content.Serialize();
            output["type_id"] = type_id;


            return output;
        }

    private:
        Chat content;
        int type_id;
    };
} //ProtocolCraft
#endif

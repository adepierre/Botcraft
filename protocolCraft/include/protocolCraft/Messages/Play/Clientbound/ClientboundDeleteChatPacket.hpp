#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDeleteChatPacket : public BaseMessage<ClientboundDeleteChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x18;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Delete Chat";
        }

        virtual ~ClientboundDeleteChatPacket() override
        {

        }

        void SetMessageSignature(const std::vector<unsigned char>& message_signature_)
        {
            message_signature = message_signature_;
        }


        const std::vector<unsigned char>& GetMessageSignature() const
        {
            return message_signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            const int size = ReadData<VarInt>(iter, length);
            message_signature = ReadByteArray(iter, length, size);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(message_signature.size(), container);
            WriteByteArray(message_signature, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["message_signature"] = "Vector of " + std::to_string(message_signature.size()) + " unsigned char";

            return output;
        }

    private:
        std::vector<unsigned char> message_signature;
    };
} //ProtocolCraft
#endif

#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDeleteChatPacket : public BaseMessage<ClientboundDeleteChatPacket>
    {
    public:
#if PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x16;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Delete Chat";

        virtual ~ClientboundDeleteChatPacket() override
        {

        }

#if PROTOCOL_VERSION > 760
        void SetMessageSignatureId(const int message_signature_id_)
        {
            message_signature_id = message_signature_id_;
        }
#endif

        void SetMessageSignature(const std::vector<unsigned char>& message_signature_)
        {
            message_signature = message_signature_;
        }

#if PROTOCOL_VERSION > 760
        int GetMessageSignatureId() const
        {
            return message_signature_id;
        }
#endif

        const std::vector<unsigned char>& GetMessageSignature() const
        {
            return message_signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 760
            message_signature_id = ReadData<VarInt>(iter, length) - 1;
            if (message_signature_id == -1)
            {
                message_signature = ReadByteArray(iter, length, 256);
            }
#else
            message_signature = ReadVector<unsigned char>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 760
            WriteData<VarInt>(message_signature_id + 1, container);
            if (message_signature_id == -1)
            {
                WriteByteArray(message_signature, container);
            }
#else
            WriteVector<unsigned char>(message_signature, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 760
            output["message_signature_id"] = message_signature_id;
            if (message_signature_id == -1)
            {
                output["message_signature"] = "Vector of " + std::to_string(message_signature.size()) + " unsigned char";
            }
#else
            output["message_signature"] = "Vector of " + std::to_string(message_signature.size()) + " unsigned char";
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 760
        int message_signature_id;
#endif
        std::vector<unsigned char> message_signature;
    };
} //ProtocolCraft
#endif

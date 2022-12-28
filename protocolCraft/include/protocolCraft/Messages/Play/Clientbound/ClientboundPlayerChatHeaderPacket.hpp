#if PROTOCOL_VERSION > 759 && PROTOCOL_VERSION < 761
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerChatHeaderPacket : public BaseMessage<ClientboundPlayerChatHeaderPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x32;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Chat Header";
        }

        virtual ~ClientboundPlayerChatHeaderPacket() override
        {

        }

        void SetHeader(const SignedMessageHeader& header_)
        {
            header = header_;
        }

        void SetHeaderSignature(const std::vector<unsigned char>& header_signature_)
        {
            header_signature = header_signature_;
        }

        void SetBodyDigest(const std::vector<unsigned char>& body_digest_)
        {
            body_digest = body_digest_;
        }


        const SignedMessageHeader& GetHeader() const
        {
            return header;
        }

        const std::vector<unsigned char>& GetHeaderSignature() const
        {
            return header_signature;
        }

        const std::vector<unsigned char>& GetBodyDigest() const
        {
            return body_digest;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            header.Read(iter, length);
            const int header_signature_size = ReadData<VarInt>(iter, length);
            header_signature = ReadByteArray(iter, length, header_signature_size);
            const int body_digest_size = ReadData<VarInt>(iter, length);
            body_digest = ReadByteArray(iter, length, body_digest_size);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            header.Write(container);
            WriteData<VarInt>(static_cast<int>(header_signature.size()), container);
            WriteByteArray(header_signature, container);
            WriteData<VarInt>(static_cast<int>(body_digest.size()), container);
            WriteByteArray(body_digest, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["header"] = header.Serialize();
            output["header_signature"] = "Vector of " + std::to_string(header_signature.size()) + " unsigned char";
            output["body_digest"] = "Vector of " + std::to_string(body_digest.size()) + " unsigned char";

            return output;
        }

    private:
        SignedMessageHeader header;
        std::vector<unsigned char> header_signature;
        std::vector<unsigned char> body_digest;
    };
}
#endif

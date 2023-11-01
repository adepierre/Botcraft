#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerChatHeaderPacket : public BaseMessage<ClientboundPlayerChatHeaderPacket>
    {
    public:
#if   PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x32;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Chat Header";

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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            header = ReadData<SignedMessageHeader>(iter, length);
            header_signature = ReadVector<unsigned char>(iter, length);
            body_digest = ReadVector<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<SignedMessageHeader>(header, container);
            WriteVector<unsigned char>(header_signature, container);
            WriteVector<unsigned char>(body_digest, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["header"] = header;
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

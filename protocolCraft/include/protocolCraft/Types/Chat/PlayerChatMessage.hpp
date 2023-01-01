#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/FilterMask.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"
#include "protocolCraft/Types/Chat/SignedMessageBody.hpp"

namespace ProtocolCraft
{
    class PlayerChatMessage : public NetworkType
    {
    public:
        virtual ~PlayerChatMessage() override
        {

        }

        void SetSignedHeader(const SignedMessageHeader& signed_header_)
        {
            signed_header = signed_header_;
        }

        void SetHeaderSignature(const std::vector<unsigned char>& header_signature_)
        {
            header_signature = header_signature_;
        }

        void SetSignedBody(const SignedMessageBody& signed_body_)
        {
            signed_body = signed_body_;
        }

        void SetUnsignedContent(const std::optional<Chat>& unsigned_content_)
        {
            unsigned_content = unsigned_content_;
        }

        void SetFilterMask(const FilterMask& filter_mask_)
        {
            filter_mask = filter_mask_;
        }


        const SignedMessageHeader& GetSignedHeader() const
        {
            return signed_header;
        }

        const std::vector<unsigned char>& GetHeaderSignature() const
        {
            return header_signature;
        }

        const SignedMessageBody& GetSignedBody() const
        {
            return signed_body;
        }

        const std::optional<Chat>& GetUnsignedContent() const
        {
            return unsigned_content;
        }

        const FilterMask& GetFilterMask() const
        {
            return filter_mask;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            signed_header = ReadData<SignedMessageHeader>(iter, length);
            const int header_signature_size = ReadData<VarInt>(iter, length);
            header_signature = ReadByteArray(iter, length, header_signature_size);
            signed_body = ReadData<SignedMessageBody>(iter, length);
            unsigned_content = ReadOptional<Chat>(iter, length);
            filter_mask = ReadData<FilterMask>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<SignedMessageHeader>(signed_header, container);
            WriteData<VarInt>(static_cast<int>(header_signature.size()), container);
            WriteByteArray(header_signature, container);
            WriteData<SignedMessageBody>(signed_body, container);
            WriteOptional<Chat>(unsigned_content, container);
            WriteData<FilterMask>(filter_mask, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["signed_header"] = signed_header.Serialize();
            output["header_signature"] = "Vector of " + std::to_string(header_signature.size()) + " unsigned char";
            output["signed_body"] = signed_body.Serialize();
            if (unsigned_content.has_value())
            {
                output["unsigned_content"] = unsigned_content.value().Serialize();
            }
            output["filter_mask"] = filter_mask.Serialize();


            return output;
        }

    private:
        SignedMessageHeader signed_header;
        std::vector<unsigned char> header_signature;
        SignedMessageBody signed_body;
        std::optional<Chat> unsigned_content;
        FilterMask filter_mask;
    };
}
#endif

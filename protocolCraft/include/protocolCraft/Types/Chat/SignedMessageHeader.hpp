#if PROTOCOL_VERSION > 759
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SignedMessageHeader : public NetworkType
    {
    public:
        virtual ~SignedMessageHeader() override
        {

        }

        void SetPreviousSignature(const std::vector<unsigned char>& previous_signature_)
        {
            previous_signature = previous_signature_;
        }
        
        void SetSender(const UUID& sender_)
        {
            sender = sender_;
        }
    

        const std::vector<unsigned char>& GetPreviousSignature() const
        {
            return previous_signature;
        }
        
        const UUID& GetSender() const
        {
            return sender;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            const bool has_previous_signature = ReadData<bool>(iter, length);
            if (has_previous_signature)
            {
                const int size = ReadData<VarInt>(iter, length);
                previous_signature = ReadByteArray(iter, length, size);
            }
            sender = ReadData<UUID>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(previous_signature.size() > 0, container);
            if (previous_signature.size() > 0)
            {
                WriteData<VarInt>(previous_signature.size(), container);
                WriteByteArray(previous_signature, container);
            }
            WriteData<UUID>(sender, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["previous_signature"] = "Vector of " + std::to_string(previous_signature.size()) + " unsigned char";
            output["sender"] = sender;


            return output;
        }

    private:
        std::vector<unsigned char> previous_signature;
        UUID sender;
    };
} // ProtocolCraft
#endif

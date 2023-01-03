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

        void SetPreviousSignature(const std::optional<std::vector<unsigned char>>& previous_signature_)
        {
            previous_signature = previous_signature_;
        }
        
        void SetSender(const UUID& sender_)
        {
            sender = sender_;
        }
    

        const std::optional<std::vector<unsigned char>>& GetPreviousSignature() const
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
            previous_signature = ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<unsigned char>(i, l);
                }
            );
            sender = ReadData<UUID>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteOptional<std::vector<unsigned char>>(previous_signature, container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteVector<unsigned char>(v, c);
                }
            );
            WriteData<UUID>(sender, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            if (previous_signature.has_value())
            {
                output["previous_signature"] = "Vector of " + std::to_string(previous_signature.value().size()) + " unsigned char";
            }
            output["sender"] = sender;


            return output;
        }

    private:
        std::optional<std::vector<unsigned char>> previous_signature;
        UUID sender;
    };
} // ProtocolCraft
#endif

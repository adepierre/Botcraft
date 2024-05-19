#if PROTOCOL_VERSION > 759 /* > 1.19 */
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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            previous_signature = ReadData<std::optional<std::vector<unsigned char>>>(iter, length);
            sender = ReadData<UUID>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::optional<std::vector<unsigned char>>>(previous_signature, container);
            WriteData<UUID>(sender, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (previous_signature.has_value())
            {
                output["previous_signature"] = "Vector of " + std::to_string(previous_signature.value().size()) + " unsigned char";
            }
            output["sender"] = sender;


            return output;
        }

    private:
        std::optional<std::vector<unsigned char>> previous_signature;
        UUID sender = {};
    };
} // ProtocolCraft
#endif

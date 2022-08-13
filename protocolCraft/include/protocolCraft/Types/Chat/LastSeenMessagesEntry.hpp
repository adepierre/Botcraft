#if PROTOCOL_VERSION > 759
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class LastSeenMessagesEntry : public NetworkType
    {
    public:
        virtual ~LastSeenMessagesEntry() override
        {

        }


        void SetProfileId(const UUID& profile_id_)
        {
            profile_id = profile_id_;
        }

        void SetLastSignature(const std::vector<unsigned char>& last_signature_)
        {
            last_signature = last_signature_;
        }
    

        const UUID& GetProfileId() const
        {
            return profile_id;
        }

        const std::vector<unsigned char>& GetLastSignature() const
        {
            return last_signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            profile_id = ReadData<UUID>(iter, length);
            const int last_signature_size = ReadData<VarInt>(iter, length);
            last_signature = ReadByteArray(iter, length, last_signature_size);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<UUID>(profile_id, container);
            WriteData<VarInt>(last_signature.size(), container);
            WriteByteArray(last_signature, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["profile_id"] = profile_id;
            output["last_signature"] = "Vector of " + std::to_string(last_signature.size()) + " unsigned char";

            return output;
        }

    private:
        UUID profile_id;
        std::vector<unsigned char> last_signature;
    };
} // ProtocolCraft
#endif

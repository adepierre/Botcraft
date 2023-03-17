#if PROTOCOL_VERSION > 760
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BaseMessage<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:
#if PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x6B;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Update Enabled Features";

        virtual ~ClientboundUpdateEnabledFeaturesPacket() override
        {

        }


        void SetFeatures(const std::vector<Identifier>& features_)
        {
            features = features_;
        }


        const std::vector<Identifier>& GetFeatures() const
        {
            return features;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            features = ReadVector<Identifier>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<Identifier>(features, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["features"] = features;

            return output;
        }

    private:
        std::vector<Identifier> features;

    };
} //ProtocolCraft
#endif

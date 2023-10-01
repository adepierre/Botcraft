#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

#include <vector>
#include <string>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BaseMessage<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:
        static constexpr int packet_id = 0x07;

        static constexpr std::string_view packet_name = "Update Enabled Features";

        virtual ~ClientboundUpdateEnabledFeaturesPacket() override
        {

        }

        void SetFeatures(const std::vector<std::string>& features_)
        {
            features = features_;
        }

        const std::vector<std::string>& GetFeatures() const
        {
            return features;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            features = ReadVector<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVector<std::string>(features, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["features"] = features;

            return output;
        }

    private:
        std::vector<std::string> features;
    };
} //ProtocolCraft
#endif

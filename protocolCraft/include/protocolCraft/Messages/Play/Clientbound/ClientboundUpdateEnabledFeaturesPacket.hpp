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
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 761 // 1.19.3
            return 0x67;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Enabled Features";
        }

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
            const int features_size = ReadData<VarInt>(iter, length);
            features = std::vector<Identifier>(features_size);
            for (size_t i = 0; i < features_size; ++i)
            {
                features[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(static_cast<int>(features.size()), container);
            for (size_t i = 0; i < features.size(); ++i)
            {
                features[i].Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["features"] = nlohmann::json::array();
            for (size_t i = 0; i < features.size(); ++i)
            {
                output["features"].push_back(features[i].Serialize());
            }

            return output;
        }

    private:
        std::vector<Identifier> features;

    };
} //ProtocolCraft
#endif

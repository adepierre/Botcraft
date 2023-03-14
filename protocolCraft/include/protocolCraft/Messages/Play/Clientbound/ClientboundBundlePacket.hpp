#if PROTOCOL_VERSION > 761
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundBundlePacket : public BaseMessage<ClientboundBundlePacket>
    {
    public:
#if PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x00;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Bundle";

        virtual ~ClientboundBundlePacket() override
        {

        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {

        }

        virtual void WriteImpl(WriteContainer &container) const override
        {

        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;


            return output;
        }

    private:

    };
} //ProtocolCraft
#endif

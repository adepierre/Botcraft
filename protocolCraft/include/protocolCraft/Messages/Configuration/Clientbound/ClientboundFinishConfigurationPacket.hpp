#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundFinishConfigurationPacket : public BaseMessage<ClientboundFinishConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x02;

        static constexpr std::string_view packet_name = "Finish Configuration";

        virtual ~ClientboundFinishConfigurationPacket() override
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

        }

        virtual void WriteImpl(WriteContainer& container) const override
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

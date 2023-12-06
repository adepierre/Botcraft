#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStartConfigurationPacket : public BaseMessage<ClientboundStartConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x67;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Start Configuration";

        virtual ~ClientboundStartConfigurationPacket() override
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

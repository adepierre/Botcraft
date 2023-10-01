#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundConfigurationAcknowledgedPacket : public BaseMessage<ServerboundConfigurationAcknowledgedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x0B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Configuration Acknowledged";

        virtual ~ServerboundConfigurationAcknowledgedPacket() override
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

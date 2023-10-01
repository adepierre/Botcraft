#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundLoginAcknowledgedPacket : public BaseMessage<ServerboundLoginAcknowledgedPacket>
    {
    public:
        static constexpr int packet_id = 0x03;
        static constexpr std::string_view packet_name = "Login Acknowledged";

        virtual ~ServerboundLoginAcknowledgedPacket() override
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
} // ProtocolCraft
#endif

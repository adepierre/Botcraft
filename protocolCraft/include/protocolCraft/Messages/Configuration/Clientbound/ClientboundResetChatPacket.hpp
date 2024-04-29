#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResetChatPacket : public BaseMessage<ClientboundResetChatPacket>
    {
    public:
        static constexpr int packet_id = 0x06;
        static constexpr std::string_view packet_name = "Reset Chat";

        virtual ~ClientboundResetChatPacket() override
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
}
#endif

#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDisconnectConfigurationPacket : public BaseMessage<ClientboundDisconnectConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x01;

        static constexpr std::string_view packet_name = "Disconnect (Configuration)";

        virtual ~ClientboundDisconnectConfigurationPacket() override
        {

        }

        void SetReason(const Chat& reason_)
        {
            reason = reason_;
        }

        const Chat& GetReason() const
        {
            return reason;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            reason = ReadData<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<Chat>(reason, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["reason"] = reason;

            return output;
        }

    private:
        Chat reason;
    };
} //ProtocolCraft
#endif

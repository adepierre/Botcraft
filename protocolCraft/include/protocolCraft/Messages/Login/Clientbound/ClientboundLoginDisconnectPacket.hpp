#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginDisconnectPacket : public BaseMessage<ClientboundLoginDisconnectPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Login Disconnect";

        virtual ~ClientboundLoginDisconnectPacket() override
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

            output["reason"] = reason.Serialize();

            return output;
        }

    private:
        Chat reason;
    };
}

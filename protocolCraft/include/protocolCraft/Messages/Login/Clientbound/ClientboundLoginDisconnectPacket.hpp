#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginDisconnectPacket : public BaseMessage<ClientboundLoginDisconnectPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Login Disconnect";
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
            reason.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            reason.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["reason"] = reason.Serialize();

            return value;
        }

    private:
        Chat reason;
    };
}
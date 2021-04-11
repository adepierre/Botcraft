#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStatusResponsePacket : public BaseMessage<ClientboundStatusResponsePacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Status Response";
        }

        void SetStatus(const std::string& status_)
        {
            status = status_;
        }

        const std::string& GetStatus() const
        {
            return status;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            status = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(status, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["status"] = picojson::value(status);

            return value;
        }

    private:
        std::string status;
    };
} //ProtocolCraft
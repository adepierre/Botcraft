#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStatusResponsePacket : public BaseMessage<ClientboundStatusResponsePacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Status Response";

        virtual ~ClientboundStatusResponsePacket() override
        {

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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            status = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(status, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["status"] = status;

            return output;
        }

    private:
        std::string status;
    };
} //ProtocolCraft

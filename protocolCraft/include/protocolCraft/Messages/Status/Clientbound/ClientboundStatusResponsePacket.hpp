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
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            status = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(status, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["status"] = status;

            return output;
        }

    private:
        std::string status;
    };
} //ProtocolCraft

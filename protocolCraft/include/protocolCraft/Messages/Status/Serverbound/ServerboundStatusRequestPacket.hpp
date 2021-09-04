#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundStatusRequestPacket : public BaseMessage<ServerboundStatusRequestPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Status Request";
        }

        virtual ~ServerboundStatusRequestPacket() override
        {

        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            return output;
        }

    private:

    };
} // Botcraft
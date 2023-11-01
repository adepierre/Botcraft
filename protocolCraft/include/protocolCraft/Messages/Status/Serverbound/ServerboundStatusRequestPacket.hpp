#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundStatusRequestPacket : public BaseMessage<ServerboundStatusRequestPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Status Request";

        virtual ~ServerboundStatusRequestPacket() override
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
} // ProtocolCraft

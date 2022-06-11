#if PROTOCOL_VERSION > 758
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockChangedAckPacket : public BaseMessage<ClientboundBlockChangedAckPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x05;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Block Changed Ack";
        }

        virtual ~ClientboundBlockChangedAckPacket() override
        {

        }

        void SetSequence(const int sequence_)
        {
            sequence = sequence_;
        }


        const int GetSequence() const
        {
            return sequence;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            sequence = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(sequence, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["sequence"] = sequence;

            return output;
        }

    private:
        int sequence;
    };
} //ProtocolCraft

#endif

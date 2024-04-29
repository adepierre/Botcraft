#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStepPacket : public BaseMessage<ClientboundTickingStepPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x6F;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x72;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ticking Step";

        virtual ~ClientboundTickingStepPacket() override
        {

        }

        void SetTickingSteps(const int ticking_steps_)
        {
            ticking_steps = ticking_steps_;
        }


        int GetTickingSteps() const
        {
            return ticking_steps;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            ticking_steps = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(ticking_steps, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["ticking_steps"] = ticking_steps;

            return output;
        }

    private:
        int ticking_steps = 0;
    };
} //ProtocolCraft
#endif

#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStatePacket : public BaseMessage<ClientboundTickingStatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x6E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ticking State";

        virtual ~ClientboundTickingStatePacket() override
        {

        }


        void SetTickRate(const float tick_rate_)
        {
            tick_rate = tick_rate_;
        }

        void SetIsFrozen(const bool is_frozen_)
        {
            is_frozen = is_frozen_;
        }


        float GetTickRate() const
        {
            return tick_rate;
        }

        bool GetIsFrozen() const
        {
            return is_frozen;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            tick_rate = ReadData<float>(iter, length);
            is_frozen = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(tick_rate, container);
            WriteData<bool>(is_frozen, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["tick_rate"] = tick_rate;
            output["is_frozen"] = is_frozen;

            return output;
        }

    private:
        float tick_rate = 0.0f;
        bool is_frozen = false;
    };
} //ProtocolCraft
#endif

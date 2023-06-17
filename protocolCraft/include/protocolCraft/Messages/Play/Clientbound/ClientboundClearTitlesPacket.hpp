#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundClearTitlesPacket : public BaseMessage<ClientboundClearTitlesPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x0E;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Clear Titles";

        virtual ~ClientboundClearTitlesPacket() override
        {

        }

        void SetResetTimes(const bool reset_times_)
        {
            reset_times = reset_times_;
        }


        bool GetResetTimes() const
        {
            return reset_times;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            reset_times = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(reset_times, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["reset_times"] = reset_times;

            return output;
    }

    private:
        bool reset_times = false;

    };
} //ProtocolCraft
#endif

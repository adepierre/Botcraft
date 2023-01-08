#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTimePacket : public BaseMessage<ClientboundSetTimePacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x5A;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Time";

        virtual ~ClientboundSetTimePacket() override
        {

        }

        void SetGameTime(const long long int game_time_)
        {
            game_time = game_time_;
        }

        void SetDayTime(const long long int day_time_)
        {
            day_time = day_time_;
        }

        const long long int GetGameTime() const
        {
            return game_time;
        }

        const long long int GetDayTime() const
        {
            return day_time;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            game_time = ReadData<long long int>(iter, length);
            day_time = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<long long int>(game_time, container);
            WriteData<long long int>(day_time, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["game_time"] = game_time;
            output["day_time"] = day_time;

            return output;
        }

    private:
        long long int game_time;
        long long int day_time;
    };
} //ProtocolCraft

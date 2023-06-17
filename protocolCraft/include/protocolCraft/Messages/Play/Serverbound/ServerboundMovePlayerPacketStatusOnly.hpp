#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketStatusOnly : public BaseMessage<ServerboundMovePlayerPacketStatusOnly>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x17;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Move Player Status Only";

        virtual ~ServerboundMovePlayerPacketStatusOnly() override
        {

        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        bool GetOnGround() const
        {
            return on_ground;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(on_ground, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["on_ground"] = on_ground;

            return output;
        }

    private:
        bool on_ground = false;

    };
} //ProtocolCraft
#endif

#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDefaultSpawnPositionPacket : public BaseMessage<ClientboundSetDefaultSpawnPositionPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x50;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Default Spawn Position";

        virtual ~ClientboundSetDefaultSpawnPositionPacket() override
        {

        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

#if PROTOCOL_VERSION > 754
        void SetAngle(const float angle_)
        {
            angle = angle_;
        }
#endif


        const NetworkPosition& GetLocation() const
        {
            return location;
        }

#if PROTOCOL_VERSION > 754
        float GetAngle() const
        {
            return angle;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location = ReadData<NetworkPosition>(iter, length);
#if PROTOCOL_VERSION > 754
            angle = ReadData<float>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
           WriteData<NetworkPosition>(location, container);
#if PROTOCOL_VERSION > 754
           WriteData<float>(angle, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["location"] = location;
#if PROTOCOL_VERSION > 754
            output["angle"] = angle;
#endif

            return output;
        }

    private:
        NetworkPosition location;
#if PROTOCOL_VERSION > 754
        float angle;
#endif

    };
} //ProtocolCraft

#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCameraPacket : public BaseMessage<ClientboundSetCameraPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x4C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Camera";

        virtual ~ClientboundSetCameraPacket() override
        {

        }

        void SetCameraId(const int camera_id_)
        {
            camera_id = camera_id_;
        }


        int GetCameraId() const
        {
            return camera_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            camera_id = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(camera_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["camera_id"] = camera_id;

            return output;
        }

    private:
        int camera_id = 0;

    };
} //ProtocolCraft

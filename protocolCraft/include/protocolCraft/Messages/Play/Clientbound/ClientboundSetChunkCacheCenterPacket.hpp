#pragma once

#if PROTOCOL_VERSION > 471
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetChunkCacheCenterPacket : public BaseMessage<ClientboundSetChunkCacheCenterPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x4E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Chunk Cache Center";

        virtual ~ClientboundSetChunkCacheCenterPacket() override
        {

        }

        void SetX(const int x_)
        {
            x = x_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }


        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            x = ReadData<VarInt>(iter, length);
            z = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(x, container);
            WriteData<VarInt>(z, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["z"] = z;

            return output;
        }

    private:
        int x = 0;
        int z = 0;

    };
} //ProtocolCraft
#endif

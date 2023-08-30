#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundForgetLevelChunkPacket : public BaseMessage<ClientboundForgetLevelChunkPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x1E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Forget Level Chunk";

        virtual ~ClientboundForgetLevelChunkPacket() override
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
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<int>(iter, length);
            z = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(x, container);
            WriteData<int>(z, container);
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

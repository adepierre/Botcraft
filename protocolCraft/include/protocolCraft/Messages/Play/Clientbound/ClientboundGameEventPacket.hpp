#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundGameEventPacket : public BaseMessage<ClientboundGameEventPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x1F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Game Event";

        virtual ~ClientboundGameEventPacket() override
        {

        }

        void SetType(const unsigned char type_)
        {
            type = type_;
        }

        void SetParam(const float param_)
        {
            param = param_;
        }


        unsigned char GetType() const
        {
            return type;
        }

        float GetParam() const
        {
            return param;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = ReadData<unsigned char>(iter, length);
            param = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(type, container);
            WriteData<float>(param, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["type"] = type;
            output["param"] = param;

            return output;
        }

    private:
        unsigned char type = 0;
        float param = 0.0f;

    };
} //ProtocolCraft

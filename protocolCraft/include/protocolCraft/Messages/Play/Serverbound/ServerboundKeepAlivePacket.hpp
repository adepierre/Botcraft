#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundKeepAlivePacket : public BaseMessage<ServerboundKeepAlivePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x12;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Keep Alive";

        virtual ~ServerboundKeepAlivePacket() override
        {

        }

        void SetId_(const long long int l)
        {
            id_ = l;
        }

        long long int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<long long int>(id_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;

            return output;
        }

    private:
        long long int id_ = 0;
    };
} //ProtocolCraft

#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCooldownPacket : public BaseMessage<ClientboundCooldownPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 759 || PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x15;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Cooldown";

        virtual ~ClientboundCooldownPacket() override
        {

        }

        void SetItem(const int item_)
        {
            item = item_;
        }

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }


        int GetItem() const
        {
            return item;
        }

        int GetDuration() const
        {
            return duration;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            item = ReadData<VarInt>(iter, length);
            duration = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(item, container);
            WriteData<VarInt>(duration, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["item"] = item;
            output["duration"] = duration;

            return output;
        }

    private:
        int item = 0;
        int duration = 0;

    };
} //ProtocolCraft

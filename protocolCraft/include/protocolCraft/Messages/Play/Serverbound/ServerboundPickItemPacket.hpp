#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPickItemPacket : public BaseMessage<ServerboundPickItemPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x1A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Pick Item";

        virtual ~ServerboundPickItemPacket() override
        {

        }

        void SetSlot(const int slot_)
        {
            slot = slot_;
        }


        int GetSlot() const
        {
            return slot;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            slot = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(slot, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["slot"] = slot;

            return output;
        }

    private:
        int slot = 0;

    };
} //ProtocolCraft
#endif

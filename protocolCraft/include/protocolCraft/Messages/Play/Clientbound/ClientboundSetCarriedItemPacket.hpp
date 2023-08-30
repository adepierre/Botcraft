#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCarriedItemPacket : public BaseMessage<ClientboundSetCarriedItemPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x4D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Carried Item";

        virtual ~ClientboundSetCarriedItemPacket() override
        {

        }

        void SetSlot(const char slot_)
        {
            slot = slot_;
        }

        char GetSlot() const
        {
            return slot;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            slot = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(slot, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["slot"] = slot;

            return output;
        }

    private:
        char slot = 0;
    };
}

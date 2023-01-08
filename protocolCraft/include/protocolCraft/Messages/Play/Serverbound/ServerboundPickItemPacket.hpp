#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPickItemPacket : public BaseMessage<ServerboundPickItemPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x19;
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


        const int GetSlot() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["slot"] = slot;

            return output;
        }

    private:
        int slot;

    };
} //ProtocolCraft
#endif

#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityDataPacket : public BaseMessage<ClientboundSetEntityDataPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x4E;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Entity Data";

        virtual ~ClientboundSetEntityDataPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetPackedItems(const std::vector<unsigned char>& packed_items_)
        {
            packed_items = packed_items_;
        }


        const int GetId_() const
        {
            return id_;
        }

        const std::vector<unsigned char>& GetPackedItems() const
        {
            return packed_items;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            packed_items = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteByteArray(packed_items, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["id_"] = id_;
            output["packed_items"] = "Vector of " + std::to_string(packed_items.size()) + " unsigned chars";

            return output;
        }

    private:
        int id_;
        std::vector<unsigned char> packed_items;

    };
} //ProtocolCraft

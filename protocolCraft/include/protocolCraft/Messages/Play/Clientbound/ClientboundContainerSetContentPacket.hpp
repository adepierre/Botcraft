#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BaseMessage<ClientboundContainerSetContentPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x12;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Container Set Content";

        virtual ~ClientboundContainerSetContentPacket() override
        {

        }

        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }

        void SetItems(const std::vector<Slot>& items_)
        {
            items = items_;
        }

#if PROTOCOL_VERSION > 755
        void SetCarriedItem(const Slot& carried_item_)
        {
            carried_item = carried_item_;
        }

        void SetStateId(const int state_id_)
        {
            state_id = state_id_;
        }
#endif

        unsigned char GetContainerId() const
        {
            return container_id;
        }

        const std::vector<Slot>& GetSlotData() const
        {
            return items;
        }

#if PROTOCOL_VERSION > 755
        const Slot& GetCarriedItem() const
        {
            return carried_item;
        }

        int GetStateId() const
        {
            return state_id;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 756
            items = ReadVector<Slot, short>(iter, length);
#else
            state_id = ReadData<VarInt>(iter, length);
            items = ReadVector<Slot>(iter, length);
            carried_item = ReadData<Slot>(iter, length);
#endif            
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>(container_id, container);
#if PROTOCOL_VERSION < 756
            WriteVector<Slot, short>(items, container);
#else
            WriteData<VarInt>(state_id, container);
            WriteVector<Slot>(items, container);
            WriteData<Slot>(carried_item, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["items"] = items;

#if PROTOCOL_VERSION > 755
            output["state_id"] = state_id;
            output["carried_item"] = carried_item;
#endif

            return output;
        }

    private:
        unsigned char container_id;
        std::vector<Slot> items;
#if PROTOCOL_VERSION > 755
        Slot carried_item;
        int state_id;
#endif
    };
} //ProtocolCraft

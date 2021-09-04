#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BaseMessage<ClientboundContainerSetContentPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x14;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x15;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x14;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x13;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x14;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Container Set Content";
        }

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

        const unsigned char GetContainerId() const
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

        const int GetStateId() const
        {
            return state_id;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 756
            short count = ReadData<short>(iter, length);
            items = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                items[i].Read(iter, length);
            }
#else
            state_id = ReadData<VarInt>(iter, length);
            int count = ReadData<VarInt>(iter, length);
            items = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                items[i].Read(iter, length);
            }
            carried_item.Read(iter, length);
#endif            
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>(container_id, container);
#if PROTOCOL_VERSION < 756
            WriteData<short>(items.size(), container);
            for (int i = 0; i < items.size(); ++i)
            {
                items[i].Write(container);
            }
#else
            WriteData<VarInt>(state_id, container);
            WriteData<VarInt>(items.size(), container);
            for (int i = 0; i < items.size(); ++i)
            {
                items[i].Write(container);
            }
            carried_item.Write(container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["container_id"] = container_id;
            output["items"] = nlohmann::json::array();
            for (int i = 0; i < items.size(); ++i)
            {
                output["items"].push_back(items[i].Serialize());
            }

#if PROTOCOL_VERSION > 755
            output["state_id"] = state_id;
            output["carried_item"] = carried_item.Serialize();
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
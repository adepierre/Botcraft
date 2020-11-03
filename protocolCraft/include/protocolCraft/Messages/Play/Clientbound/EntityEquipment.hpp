#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class EntityEquipment : public BaseMessage<EntityEquipment>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x3F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x42;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x46;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x47;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x47;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x47;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Equipment";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

#if PROTOCOL_VERSION > 730
        void SetSlot(const std::vector<unsigned char>& slot_)
        {
            slot = slot_;
        }

        void SetItem(const std::vector<Slot>& item_)
        {
            item = item_;
        }
#else
        void SetSlot(const int slot_)
        {
            slot = slot_;
        }

        void SetItem(const Slot& item_)
        {
            item = item_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION > 730
        const std::vector<unsigned char>& GetSlot() const
        {
            return slot;
        }

        const std::vector<Slot>& GetItem() const
        {
            return item;
        }
#else
        const int GetSlot() const
        {
            return slot;
        }

        const Slot& GetItem() const
        {
            return item;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);

#if PROTOCOL_VERSION > 730
            bool has_value = true;
            slot = std::vector<unsigned char>(0);
            item = std::vector<Slot>(0);
            while (has_value)
            {
                unsigned char current_slot = ReadData<unsigned char>(iter, length);
                slot.push_back(current_slot);
                item.push_back(Slot());
                item[item.size() - 1].Read(iter, length);
                has_value = current_slot & (1 << 7);
            }
#else
            slot = ReadVarInt(iter, length);
            item.Read(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
#if PROTOCOL_VERSION > 730
            for (int i = 0; i < slot.size(); ++i)
            {
                WriteData<unsigned char>(slot[i], container);
                item[i].Write(container);
            }
#else
            WriteVarInt(slot, container);
            item.Write(container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
#if PROTOCOL_VERSION > 730
            object["slot"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["slot"].get<picojson::array>();
            for (int i = 0; i < slot.size(); ++i)
            {
                array.push_back(picojson::value((double)(slot[i])));
            }
            object["item"] = picojson::value(picojson::array_type, false);
            array = object["item"].get<picojson::array>();
            for (int i = 0; i < item.size(); ++i)
            {
                array.push_back(item[i].Serialize());
            }
#else
            object["slot"] = picojson::value((double)slot);
            object["item"] = item.Serialize();
#endif

            return value;
        }

    private:
        int entity_id;
#if PROTOCOL_VERSION > 730
        std::vector<unsigned char> slot;
        std::vector<Slot> item;
#else
        int slot;
        Slot item;
#endif

    };
} //ProtocolCraft
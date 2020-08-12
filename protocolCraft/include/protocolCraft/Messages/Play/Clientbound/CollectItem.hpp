#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class CollectItem : public BaseMessage<CollectItem>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x4F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x55;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x56;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x55;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x55;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Collect Item";
        }

        void SetCollectedEntityId(const int collected_entity_id_)
        {
            collected_entity_id = collected_entity_id_;
        }

        void SetCollectorEntityId(const int collector_entity_id_)
        {
            collector_entity_id = collector_entity_id_;
        }

        void SetPickupItemCount(const int pickup_item_count_)
        {
            pickup_item_count = pickup_item_count_;
        }


        const int GetCollectedEntityId() const
        {
            return collected_entity_id;
        }

        const int GetCollectorEntityId() const
        {
            return collector_entity_id;
        }

        const int GetPickupItemCount() const
        {
            return pickup_item_count;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            collected_entity_id = ReadVarInt(iter, length);
            collector_entity_id = ReadVarInt(iter, length);
            pickup_item_count = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(collected_entity_id, container);
            WriteVarInt(collector_entity_id, container);
            WriteVarInt(pickup_item_count, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["collected_entity_id"] = picojson::value((double)collected_entity_id);
            object["collector_entity_id"] = picojson::value((double)collector_entity_id);
            object["pickup_item_count"] = picojson::value((double)pickup_item_count);

            return value;
        }

    private:
        int collected_entity_id;
        int collector_entity_id;
        int pickup_item_count;

    };
} //ProtocolCraft
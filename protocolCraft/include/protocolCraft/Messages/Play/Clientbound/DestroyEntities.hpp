#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class DestroyEntities : public BaseMessage<DestroyEntities>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x32;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x35;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x37;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x38;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Destroy Entities";
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetEntityIds(const std::vector<int>& entity_ids_)
        {
            entity_ids = entity_ids_;
        }


        const int GetCount() const
        {
            return count;
        }

        const std::vector<int>& GetEntityIds() const
        {
            return entity_ids;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            count = ReadVarInt(iter, length);
            entity_ids = std::vector<int>(count);
            for (int i = 0; i < count; ++i)
            {
                entity_ids[i] = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(count, container);
            for (int i = 0; i < count; ++i)
            {
                WriteVarInt(entity_ids[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["count"] = picojson::value((double)count);
            object["entity_ids"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["entity_ids"].get<picojson::array>();
            for (int i = 0; i < count; ++i)
            {
                array.push_back(picojson::value((double)entity_ids[i]));
            }

            return value;
        }

    private:
        int count;
        std::vector<int> entity_ids;

    };
} //ProtocolCraft
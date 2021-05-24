#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class Ingredient : public NetworkType
    {
    public:
        virtual ~Ingredient() override
        {

        }

        void SetCount(const int count_)
        {
            count = count_;
        }
        
        void SetItems(const std::vector<Slot>& items_)
        {
            items = items_;
        }
        
        
        const int GetCount() const
        {
            return count;
        }
        
        const std::vector<Slot>& GeItems() const
        {
            return items;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            count = ReadVarInt(iter, length);
            items = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                items[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(count, container);
            for (int i = 0; i < count; ++i)
            {
                items[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["count"] = picojson::value((double)count);
            object["items"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["items"].get<picojson::array>();
            for (int i = 0; i < count; ++i)
            {
                array.push_back(items[i].Serialize());
            }

            return value;
        }

    private:
        int count;
        std::vector<Slot> items;
    };
}
#endif

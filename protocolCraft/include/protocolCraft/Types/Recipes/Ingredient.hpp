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
            count = ReadData<VarInt>(iter, length);
            items = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                items[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(count, container);
            for (int i = 0; i < count; ++i)
            {
                items[i].Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["count"] = count;
            output["items"] = nlohmann::json::array();
            for (int i = 0; i < count; ++i)
            {
                output["items"].push_back(items[i].Serialize());
            }

            return output;
        }

    private:
        int count;
        std::vector<Slot> items;
    };
}
#endif

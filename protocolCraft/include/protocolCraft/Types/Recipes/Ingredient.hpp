#pragma once

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class Ingredient : public NetworkType
    {
    public:
        virtual ~Ingredient() override
        {

        }


        void SetItems(const std::vector<Slot>& items_)
        {
            items = items_;
        }


        const std::vector<Slot>& GetItems() const
        {
            return items;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            items = ReadData<std::vector<Slot>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::vector<Slot>>(items, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["items"] = items;

            return output;
        }

    private:
        std::vector<Slot> items;
    };
}
#endif

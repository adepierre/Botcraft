#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"

namespace ProtocolCraft
{
    class ItemCost : public NetworkType
    {
    public:
        virtual ~ItemCost() override
        {

        }


        int GetItemID() const
        {
            return item_id;
        }

        int GetCount() const
        {
            return count;
        }

        const Components::DataComponentPredicate& GetComponents() const
        {
            return components;
        }


        void SetItemId(const int item_id_)
        {
            item_id = item_id_;
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetComponents(const Components::DataComponentPredicate& components_)
        {
            components = components_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            item_id = ReadData<VarInt>(iter, length);
            count = ReadData<VarInt>(iter, length);
            components = ReadData<Components::DataComponentPredicate>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(item_id, container);
            WriteData<VarInt>(count, container);
            WriteData<Components::DataComponentPredicate>(components, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["item_id"] = item_id;
            output["count"] = count;
            output["components"] = components;

            return output;
        }

    private:
        int item_id = 0;
        int count = 0;
        Components::DataComponentPredicate components;

    };
} // ProtocolCraft
#endif

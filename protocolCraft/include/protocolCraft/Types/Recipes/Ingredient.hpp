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


        void SetItems(const std::vector<Slot>& items_)
        {
            items = items_;
        }
        

        const std::vector<Slot>& GeItems() const
        {
            return items;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            items = ReadVector<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<Slot>(items, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["items"] = nlohmann::json::array();
            for (const auto& i : items)
            {
                output["items"].push_back(i.Serialize());
            }

            return output;
        }

    private:
        std::vector<Slot> items;
    };
}
#endif

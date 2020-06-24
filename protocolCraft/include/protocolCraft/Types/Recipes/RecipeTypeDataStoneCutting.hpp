#pragma once

#if PROTOCOL_VERSION > 572
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataStoneCutting : public RecipeTypeData
    {
    public:
        void SetGroup(const std::string& group_)
        {
            group = group_;
        }

        void SetIngredient(const Ingredient& ingredient_)
        {
            ingredient = ingredient_;
        }

        void SetResult(const Slot& result_)
        {
            result = result_;
        }


        const std::string& GetGroup() const
        {
            return group;
        }

        const Ingredient& GetIngredient() const
        {
            return ingredient;
        }

        const Slot& GetResult() const
        {
            return result;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            group = ReadString(iter, length);
            ingredient.Read(iter, length);
            result.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(group, container);
            ingredient.Write(container);
            result.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["group"] = picojson::value(group);
            object["ingredient"] = ingredient.Serialize();
            object["result"] = result.Serialize();

            return value;
        }

    private:
        std::string group;
        Ingredient ingredient;
        Slot result;
    };
}
#endif

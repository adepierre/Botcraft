#pragma once

#if PROTOCOL_VERSION > 453 /* > 1.13.2 */
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataStoneCutting : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataStoneCutting() override
        {

        }

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
            group = ReadData<std::string>(iter, length);
            ingredient = ReadData<Ingredient>(iter, length);
            result = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(group, container);
            WriteData<Ingredient>(ingredient, container);
            WriteData<Slot>(result, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["group"] = group;
            output["ingredient"] = ingredient;
            output["result"] = result;

            return output;
        }

    private:
        std::string group;
        Ingredient ingredient;
        Slot result;
    };
}
#endif

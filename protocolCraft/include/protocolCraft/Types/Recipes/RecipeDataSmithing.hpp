#pragma once

#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithing : public RecipeData
    {
    public:
        virtual ~RecipeDataSmithing() override
        {

        }

        void SetBase(const Ingredient& base_)
        {
            base = base_;
        }

        void SetIngredient(const Ingredient& ingredient_)
        {
            ingredient = ingredient_;
        }

        void SetResult(const Slot& result_)
        {
            result = result_;
        }


        const Ingredient& GetBase() const
        {
            return base;
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
            base = ReadData<Ingredient>(iter, length);
            ingredient = ReadData<Ingredient>(iter, length);
            result = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Ingredient>(base, container);
            WriteData<Ingredient>(ingredient, container);
            WriteData<Slot>(result, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["base"] = base;
            output["ingredient"] = ingredient;
            output["result"] = result;

            return output;
        }

    private:
        Ingredient base;
        Ingredient ingredient;
        Slot result;
    };
}
#endif

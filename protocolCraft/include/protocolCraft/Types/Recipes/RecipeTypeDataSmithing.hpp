#pragma once

#if PROTOCOL_VERSION > 732
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataSmithing : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataSmithing() override
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
            base.Read(iter, length);
            ingredient.Read(iter, length);
            result.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            base.Write(container);
            ingredient.Write(container);
            result.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["base"] = base.Serialize();
            output["ingredient"] = ingredient.Serialize();
            output["result"] = result.Serialize();

            return output;
        }

    private:
        Ingredient base;
        Ingredient ingredient;
        Slot result;
    };
}
#endif

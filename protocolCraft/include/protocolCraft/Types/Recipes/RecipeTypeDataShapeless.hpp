#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataShapeless : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataShapeless() override
        {

        }

        void SetGroup(const std::string& group_)
        {
            group = group_;
        }
        
        void SetIngredientCount(const int ingredient_count_)
        {
            ingredient_count = ingredient_count_;
        }

        void SetIngredients(const std::vector<Ingredient>& ingredients_)
        {
            ingredients = ingredients_;
        }

        void SetResult(const Slot& result_)
        {
            result = result_;
        }


        const std::string& GetGroup() const
        {
            return group;
        }

        const int GetIngredientCount() const
        {
            return ingredient_count;
        }

        const std::vector<Ingredient>& GetIngredients() const
        {
            return ingredients;
        }

        const Slot& GetResult() const
        {
            return result;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

            group = ReadString(iter, length);
            ingredient_count = ReadVarInt(iter, length);
            ingredients = std::vector<Ingredient>(ingredient_count);
            for (int i = 0; i < ingredient_count; ++i)
            {
                ingredients[i].Read(iter, length);
            }
            result.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(group, container);
            WriteVarInt(ingredient_count, container);
            for (int i = 0; i < ingredient_count; ++i)
            {
                ingredients[i].Write(container);
            }
            result.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["group"] = picojson::value(group);
            object["ingredient_count"] = picojson::value((double)ingredient_count);
            object["ingredients"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["ingredients"].get<picojson::array>();
            for (int i = 0; i < ingredient_count; ++i)
            {
                array.push_back(ingredients[i].Serialize());
            }
            object["result"] = result.Serialize();

            return value;
        }

    private:
        std::string group;
        int ingredient_count;
        std::vector<Ingredient> ingredients;
        Slot result;
    };
}
#endif

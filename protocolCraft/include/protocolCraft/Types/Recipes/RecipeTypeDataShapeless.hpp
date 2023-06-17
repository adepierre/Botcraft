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

#if PROTOCOL_VERSION > 760
        void SetCookingBookCategory(const int cooking_book_category_)
        {
            cooking_book_category = cooking_book_category_;
        }
#endif

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

#if PROTOCOL_VERSION > 760
        int GetCookingBookCategory() const
        {
            return cooking_book_category;
        }
#endif

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

            group = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 760
            cooking_book_category = ReadData<VarInt>(iter, length);
#endif
            ingredients = ReadVector<Ingredient>(iter, length);
            result = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(group, container);
#if PROTOCOL_VERSION > 760
            WriteData<VarInt>(cooking_book_category, container);
#endif
            WriteVector<Ingredient>(ingredients, container);
            WriteData<Slot>(result, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["group"] = group;
#if PROTOCOL_VERSION > 760
            output["cooking_book_category"] = cooking_book_category;
#endif
            output["ingredients"] = ingredients;
            output["result"] = result;

            return output;
        }

    private:
        std::string group;
#if PROTOCOL_VERSION > 760
        int cooking_book_category = 0;
#endif
        std::vector<Ingredient> ingredients;
        Slot result;
    };
}
#endif

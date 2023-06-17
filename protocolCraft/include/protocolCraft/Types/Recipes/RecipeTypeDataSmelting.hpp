#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataSmelting : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataSmelting() override
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

        void SetIngredient(const Ingredient& ingredient_)
        {
            ingredient = ingredient_;
        }

        void SetResult(const Slot& result_)
        {
            result = result_;
        }

        void SetExperience(const float experience_)
        {
            experience = experience_;
        }

        void SetCookingTime(const int cooking_time_)
        {
            cooking_time = cooking_time_;
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

        const Ingredient& GetIngredient() const
        {
            return ingredient;
        }

        const Slot& GetResult() const
        {
            return result;
        }

        float GetExperience() const
        {
            return experience;
        }

        int GetCookingTime() const
        {
            return cooking_time;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            group = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 760
            cooking_book_category = ReadData<VarInt>(iter, length);
#endif
            ingredient = ReadData<Ingredient>(iter, length);
            result = ReadData<Slot>(iter, length);
            experience = ReadData<float>(iter, length);
            cooking_time = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(group, container);
#if PROTOCOL_VERSION > 760
            WriteData<VarInt>(cooking_book_category, container);
#endif
            WriteData<Ingredient>(ingredient, container);
            WriteData<Slot>(result, container);
            WriteData<float>(experience, container);
            WriteData<VarInt>(cooking_time, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["group"] = group;
#if PROTOCOL_VERSION > 760
            output["cooking_book_category"] = cooking_book_category;
#endif
            output["ingredient"] = ingredient;
            output["result"] = result;
            output["experience"] = experience;
            output["cooking_time"] = cooking_time;

            return output;
        }

    private:
        std::string group;
#if PROTOCOL_VERSION > 760
        int cooking_book_category = 0;
#endif
        Ingredient ingredient;
        Slot result;
        float experience = 0.0f;
        int cooking_time = 0;
    };
}
#endif

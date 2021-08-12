#pragma once

#if PROTOCOL_VERSION > 453
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataSmoking : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataSmoking() override
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

        const Ingredient& GetIngredient() const
        {
            return ingredient;
        }

        const Slot& GetResult() const
        {
            return result;
        }

        const float GetExperience() const
        {
            return experience;
        }

        const int GetCookingTime() const
        {
            return cooking_time;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            group = ReadData<std::string>(iter, length);
            ingredient.Read(iter, length);
            result.Read(iter, length);
            experience = ReadData<float>(iter, length);
            cooking_time = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(group, container);
            ingredient.Write(container);
            result.Write(container);
            WriteData<float>(experience, container);
            WriteData<VarInt>(cooking_time, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["group"] = group;
            output["ingredient"] = ingredient.Serialize();
            output["result"] = result.Serialize();
            output["experience"] = experience;
            output["cooking_time"] = cooking_time;

            return output;
        }

    private:
        std::string group;
        Ingredient ingredient;
        Slot result;
        float experience;
        int cooking_time;
    };
}
#endif

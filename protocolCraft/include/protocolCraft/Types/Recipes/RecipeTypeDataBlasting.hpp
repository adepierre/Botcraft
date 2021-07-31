#pragma once

#if PROTOCOL_VERSION > 453
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataBlasting : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataBlasting() override
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

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["group"] = picojson::value(group);
            object["ingredient"] = ingredient.Serialize();
            object["result"] = result.Serialize();
            object["experience"] = picojson::value((double)experience);
            object["cooking_time"] = picojson::value((double)cooking_time);

            return value;
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

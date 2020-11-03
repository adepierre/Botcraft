#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/Recipe.hpp"

namespace ProtocolCraft
{
    class DeclareRecipes : public BaseMessage<DeclareRecipes>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x54;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x5A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x5B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x5A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x5A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Declare Recipes";
        }

        void SetNumRecipes(const int num_recipes_)
        {
            num_recipes = num_recipes_;
        }

        void SetRecipe(const std::vector<Recipe>& recipe_)
        {
            recipe = recipe_;
        }


        const int GetNumRecipes() const
        {
            return num_recipes;
        }

        const std::vector<Recipe>& GetRecipe() const
        {
            return recipe;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            num_recipes = ReadVarInt(iter, length);
            recipe = std::vector<Recipe>(num_recipes);
            for (int i = 0; i < num_recipes; ++i)
            {
                recipe[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(num_recipes, container);
            for (int i = 0; i < num_recipes; ++i)
            {
                recipe[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["num_recipes"] = picojson::value((double)num_recipes);
            object["recipe"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["recipe"].get<picojson::array>();

            for (int i = 0; i < num_recipes; ++i)
            {
                array.push_back(recipe[i].Serialize());
            }

            return value;
        }

    private:
        int num_recipes;
        std::vector<Recipe> recipe;

    };
} //ProtocolCraft
#endif

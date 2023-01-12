#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataShaped : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataShaped() override
        {

        }

        void SetWidth(const int width_)
        {
            width = width_;
        }

        void SetHeight(const int height_)
        {
            height = height_;
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


        int GetWidth() const
        {
            return width;
        }

        int GetHeight() const
        {
            return height;
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
            
            width = ReadData<VarInt>(iter, length);
            height = ReadData<VarInt>(iter, length);
            group = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 760
            cooking_book_category = ReadData<VarInt>(iter, length);
#endif
            ingredients = std::vector<Ingredient>(width * height);
            for (int i = 0; i < width * height; ++i)
            {
                ingredients[i] = ReadData<Ingredient>(iter, length);
            }
            result = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(width, container);
            WriteData<VarInt>(height, container);
            WriteData<std::string>(group, container);
#if PROTOCOL_VERSION > 760
            WriteData<VarInt>(cooking_book_category, container);
#endif
            for (int i = 0; i < width * height; ++i)
            {
                WriteData<Ingredient>(ingredients[i], container);
            }
            WriteData<Slot>(result, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["width"] = width;
            output["height"] = height;
            output["group"] = group;
#if PROTOCOL_VERSION > 760
            output["cooking_book_category"] = cooking_book_category;
#endif
            output["ingredients"] = ingredients;
            output["result"] = result;

            return output;
        }

    private:
        int width;
        int height;
        std::string group;
#if PROTOCOL_VERSION > 760
        int cooking_book_category;
#endif
        std::vector<Ingredient> ingredients;
        Slot result;
    };
}
#endif

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
        
        void SetIngredients(const std::vector<Ingredient>& ingredients_)
        {
            ingredients = ingredients_;
        }

        void SetResult(const Slot& result_)
        {
            result = result_;
        }


        const int GetWidth() const
        {
            return width;
        }

        const int GetHeight() const
        {
            return height;
        }

        const std::string& GetGroup() const
        {
            return group;
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
            
            width = ReadData<VarInt>(iter, length);
            height = ReadData<VarInt>(iter, length);
            group = ReadData<std::string>(iter, length);
            ingredients = std::vector<Ingredient>(width * height);
            for (int i = 0; i < width * height; ++i)
            {
                ingredients[i].Read(iter, length);
            }
            result.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(width, container);
            WriteData<VarInt>(height, container);
            WriteData<std::string>(group, container);
            for (int i = 0; i < width * height; ++i)
            {
                ingredients[i].Write(container);
            }
            result.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["width"] = picojson::value((double)width);
            object["height"] = picojson::value((double)height);
            object["group"] = picojson::value(group);
            object["ingredients"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["ingredients"].get<picojson::array>();
            for (int i = 0; i < width * height; ++i)
            {
                array.push_back(ingredients[i].Serialize());
            }
            object["result"] = result.Serialize();

            return value;
        }

    private:
        int width;
        int height;
        std::string group;
        std::vector<Ingredient> ingredients;
        Slot result;
    };
}
#endif

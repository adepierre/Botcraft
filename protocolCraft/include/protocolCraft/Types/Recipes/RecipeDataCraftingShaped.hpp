#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"

namespace ProtocolCraft
{
    class RecipeDataCraftingShaped : public RecipeData
    {
    private:
        using THIS = RecipeDataCraftingShaped;
        std::vector<Ingredient> ReadIngredients(ReadIterator& iter, size_t& length) const
        {
            std::vector<Ingredient> ingredients(GetWidth() * GetHeight());
            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                ingredients[i] = ReadData<Ingredient>(iter, length);
            }
            return ingredients;
        }

        void WriteIngredients(const std::vector<Ingredient>& ingredients, WriteContainer& container) const
        {
            // TODO: assert that ingredients.size() == GetWidth() * GetHeight()
            for (int i = 0; i < ingredients.size(); ++i)
            {
                WriteData<Ingredient>(ingredients[i], container);
            }
        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SERIALIZED_FIELD(Width, VarInt);
        SERIALIZED_FIELD(Height, VarInt);
#endif
        SERIALIZED_FIELD(Group, std::string);
#if PROTOCOL_VERSION > 760 /* > 1.19.2*/
        SERIALIZED_FIELD(CookingBookCategory, VarInt);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SERIALIZED_FIELD(Width, VarInt);
        SERIALIZED_FIELD(Height, VarInt);
#endif
        SERIALIZED_FIELD(Ingredients, Internal::CustomType<std::vector<Ingredient>, &THIS::ReadIngredients, &THIS::WriteIngredients>);
        SERIALIZED_FIELD(Result, Slot);
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        SERIALIZED_FIELD(ShowNotification, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataCraftingShaped : public RecipeData
    {
    private:
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

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (VarInt, VarInt, std::string, Internal::CustomType<std::vector<Ingredient>, &RecipeDataCraftingShaped::ReadIngredients, &RecipeDataCraftingShaped::WriteIngredients>, Slot),
            (Width,  Height, Group,       Ingredients,                                                                                                                            Result)
        );
#elif PROTOCOL_VERSION < 762 /* < 1.19.4 */
        DECLARE_FIELDS(
            (VarInt, VarInt, std::string, VarInt,              Internal::CustomType<std::vector<Ingredient>, &RecipeDataCraftingShaped::ReadIngredients, &RecipeDataCraftingShaped::WriteIngredients>, Slot),
            (Width,  Height, Group,       CookingBookCategory, Ingredients,                                                                                                                            Result)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (VarInt, VarInt, std::string, VarInt,              Internal::CustomType<std::vector<Ingredient>, &RecipeDataCraftingShaped::ReadIngredients, &RecipeDataCraftingShaped::WriteIngredients>, Slot,   bool),
            (Width,  Height, Group,       CookingBookCategory, Ingredients,                                                                                                                            Result, ShowNotification)
        );
#else
        DECLARE_FIELDS(
            (std::string, VarInt,              VarInt, VarInt, Internal::CustomType<std::vector<Ingredient>, &RecipeDataCraftingShaped::ReadIngredients, &RecipeDataCraftingShaped::WriteIngredients>, Slot,   bool),
            (Group,       CookingBookCategory, Width,  Height, Ingredients,                                                                                                                            Result, ShowNotification)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Width);
        GETTER_SETTER(Height);
        GETTER_SETTER(Group);
        GETTER_SETTER(Ingredients);
        GETTER_SETTER(Result);
#if PROTOCOL_VERSION > 760 /* > 1.19.2*/
        GETTER_SETTER(CookingBookCategory);
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        GETTER_SETTER(ShowNotification);
#endif
    };
}
#endif

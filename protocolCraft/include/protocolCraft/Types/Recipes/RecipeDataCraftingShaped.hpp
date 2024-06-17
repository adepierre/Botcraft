#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataCraftingShaped : public RecipeData
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (VarInt, VarInt, std::string, std::vector<Ingredient>, Slot),
            (Width,  Height, Group,       Ingredients,             Result)
        );
#elif PROTOCOL_VERSION < 762 /* < 1.19.4 */
        DECLARE_FIELDS(
            (VarInt, VarInt, std::string, VarInt,              std::vector<Ingredient>, Slot),
            (Width,  Height, Group,       CookingBookCategory, Ingredients,             Result)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (VarInt, VarInt, std::string, VarInt,              std::vector<Ingredient>, Slot,   bool),
            (Width,  Height, Group,       CookingBookCategory, Ingredients,             Result, ShowNotification)
        );
#else
        DECLARE_FIELDS(
            (std::string, VarInt,              VarInt, VarInt, std::vector<Ingredient>, Slot,   bool),
            (Group,       CookingBookCategory, Width,  Height, Ingredients,             Result, ShowNotification)
        );
#endif
        DECLARE_SERIALIZE;

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

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            SetWidth(ReadData<VarInt>(iter, length));
            SetHeight(ReadData<VarInt>(iter, length));
#endif
            SetGroup(ReadData<std::string>(iter, length));
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
            SetCookingBookCategory(ReadData<VarInt>(iter, length));
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            SetWidth(ReadData<VarInt>(iter, length));
            SetHeight(ReadData<VarInt>(iter, length));
#endif
            std::vector<Ingredient> ingredients(GetWidth() * GetHeight());
            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                ingredients[i] = ReadData<Ingredient>(iter, length);
            }
            SetIngredients(ingredients);
            SetResult(ReadData<Slot>(iter, length));
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
            SetShowNotification(ReadData<bool>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            WriteData<VarInt>(GetWidth(), container);
            WriteData<VarInt>(GetHeight(), container);
#endif
            WriteData<std::string>(GetGroup(), container);
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
            WriteData<VarInt>(GetCookingBookCategory(), container);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            WriteData<VarInt>(GetWidth(), container);
            WriteData<VarInt>(GetHeight(), container);
#endif
            for (int i = 0; i < GetWidth() * GetHeight(); ++i)
            {
                WriteData<Ingredient>(GetIngredients()[i], container);
            }
            WriteData<Slot>(GetResult(), container);
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
            WriteData<bool>(GetShowNotification(), container);
#endif
        }
    };
}
#endif

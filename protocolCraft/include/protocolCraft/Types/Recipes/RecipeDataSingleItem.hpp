#if PROTOCOL_VERSION > 453 /* > 1.13.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSingleItem : public RecipeData
    {
        DECLARE_FIELDS(
            (std::string, Ingredient, Slot),
            (Group,       Ingredient, Result)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Group);
        GETTER_SETTER(Ingredient);
        GETTER_SETTER(Result);
    };
}
#endif

#if PROTOCOL_VERSION > 453 /* > 1.13.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSingleItem : public RecipeData
    {
        SERIALIZED_FIELD(Group, std::string);
        SERIALIZED_FIELD(Ingredient, ProtocolCraft::Ingredient);
        SERIALIZED_FIELD(Result, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Recipes/SelectableRecipe.hpp"

namespace ProtocolCraft
{
    class SelectableRecipeSingleInputEntry : public NetworkType
    {
        SERIALIZED_FIELD(Input, Ingredient);
        SERIALIZED_FIELD(Recipe, SelectableRecipe);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

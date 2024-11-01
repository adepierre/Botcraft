#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/RecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"

#include <optional>

namespace ProtocolCraft
{
    class RecipeDisplayEntry : public NetworkType
    {
        SERIALIZED_FIELD(Id, VarInt);
        SERIALIZED_FIELD(Display, RecipeDisplay);
        SERIALIZED_FIELD(Group, std::optional<VarInt>);
        SERIALIZED_FIELD(Category, VarInt);
        SERIALIZED_FIELD(CraftingRequirements, std::optional<std::vector<Ingredient>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

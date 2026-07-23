#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/RecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class RecipeDisplayEntry : public NetworkType
    {
        SERIALIZED_FIELD(Id, VarInt);
        SERIALIZED_FIELD(Display, RecipeDisplay);
        SERIALIZED_FIELD(Group, VarInt); // technically an optional varint but encoded as i == 0 -> empty, i > 0 -> i - 1
        SERIALIZED_FIELD(Category, VarInt);
        SERIALIZED_FIELD(CraftingRequirements, std::optional<std::vector<Ingredient>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

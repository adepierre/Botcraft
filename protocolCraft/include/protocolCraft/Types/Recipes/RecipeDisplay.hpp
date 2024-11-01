#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <memory>

namespace ProtocolCraft
{
    enum class RecipeDisplayDataType
    {
        None = -1,
        CraftingShapeless,
        CraftingShaped,
        Furnace,
        Stonecutter,
        Smithing,
        NUM_RECIPE_DISPLAY_DATA_TYPES
    };

    class RecipeDisplayData;

    class RecipeDisplay : public NetworkType
    {
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Internal::DiffType<RecipeDisplayDataType, VarInt>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::shared_ptr<RecipeDisplayData>);

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(Type);
        GETTER(Data);

    public:
        RecipeDisplay& SetType(const RecipeDisplayDataType type);
    };
}
#endif

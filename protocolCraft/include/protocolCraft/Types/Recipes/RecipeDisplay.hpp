#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"

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
    private:
        static std::shared_ptr<RecipeDisplayData> CreateRecipeDisplayData(const RecipeDisplayDataType type);

        SERIALIZED_DYNAMIC_FIELD(RecipeDisplay, Type, Data, RecipeDisplayData, RecipeDisplay::CreateRecipeDisplayData, Internal::DiffType<RecipeDisplayDataType, VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

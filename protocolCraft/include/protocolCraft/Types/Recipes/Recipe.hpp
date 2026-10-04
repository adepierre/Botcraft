#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <memory>

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    enum class RecipeDataType
    {
        None = -1,
        CraftingShaped,
        CraftingShapeless,
        CraftingSpecialArmordye,
        CraftingSpecialBookcloning,
        CraftingSpecialMapcloning,
        CraftingSpecialMapextending,
        CraftingSpecialFireworkRocket,
        CraftingSpecialFireworkStar,
        CraftingSpecialFireworkStarFade,
        CraftingSpecialTippedarrow,
        CraftingSpecialBannerduplicate,
        CraftingSpecialShielddecoration,
        CraftingSpecialShulkerboxcoloring,
        CraftingSpecialSuspiciousstew,
        CraftingSpecialRepairitem,
        Smelting,
        Blasting,
        Smoking,
        CampfireCooking,
        Stonecutting,
        SmithingTransform,
        SmithingTrim,
        CraftingDecoratedPot,
        NUM_RECIPE_DATA_TYPES
    };
#endif

    class RecipeData;

    class Recipe : public NetworkType
    {
    private:
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static std::shared_ptr<RecipeData> CreateRecipeData(const Identifier& type);
#else
        static std::shared_ptr<RecipeData> CreateRecipeData(const RecipeDataType type);
#endif

#if PROTOCOL_VERSION < 453 /* < 1.14 */
        SERIALIZED_FIELD(RecipeId, Identifier);
        SERIALIZED_DYNAMIC_FIELD(Recipe, Type, Data, RecipeData, Recipe::CreateRecipeData, Identifier);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Identifier);
        SERIALIZED_FIELD(RecipeId, Identifier);
        SERIALIZED_DYNAMIC_DATA_FIELD(Data, Recipe::Type, RecipeData, Recipe::CreateRecipeData);
#else
        SERIALIZED_FIELD(RecipeId, Identifier);
        SERIALIZED_DYNAMIC_FIELD(Recipe, Type, Data, RecipeData, Recipe::CreateRecipeData, Internal::DiffType<RecipeDataType, VarInt>);
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER(Type);
        DYNAMIC_TYPE_SETTER(Type, Data, Recipe::CreateRecipeData);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

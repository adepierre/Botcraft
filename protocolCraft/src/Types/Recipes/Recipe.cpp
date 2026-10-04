#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Types/Recipes/Recipe.hpp"
#include "protocolCraft/Types/Recipes/RecipeData.hpp"

#include "protocolCraft/Types/Recipes/RecipeDataCraftingShaped.hpp"
#include "protocolCraft/Types/Recipes/RecipeDataCraftingShapeless.hpp"
#include "protocolCraft/Types/Recipes/RecipeDataSimpleCooking.hpp"
#include "protocolCraft/Types/Recipes/RecipeDataSimpleCrafting.hpp"
#if PROTOCOL_VERSION > 453 /* > 1.13.2 */
#include "protocolCraft/Types/Recipes/RecipeDataSingleItem.hpp"
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
#include "protocolCraft/Types/Recipes/RecipeDataSmithing.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/Recipes/RecipeDataSmithingTransform.hpp"
#include "protocolCraft/Types/Recipes/RecipeDataSmithingTrim.hpp"
#endif
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(RecipeDataCraftingShaped);
    DEFINE_NETWORK_TYPE(RecipeDataCraftingShapeless);
    DEFINE_NETWORK_TYPE(RecipeDataSimpleCooking);
    DEFINE_NETWORK_TYPE(RecipeDataSimpleCrafting);
#if PROTOCOL_VERSION > 453 /* > 1.13.2 */
    DEFINE_NETWORK_TYPE(RecipeDataSingleItem);
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
    DEFINE_NETWORK_TYPE(RecipeDataSmithing);
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    DEFINE_NETWORK_TYPE(RecipeDataSmithingTransform);
    DEFINE_NETWORK_TYPE(RecipeDataSmithingTrim);
#endif

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    std::shared_ptr<RecipeData> Recipe::CreateRecipeData(const Identifier& type)
    {
        const std::string full = type.GetFull();

        if (full == "minecraft:crafting_shapeless")
        {
            return std::make_shared<RecipeDataCraftingShapeless>();
        }
        else if (full == "minecraft:crafting_shaped")
        {
            return std::make_shared<RecipeDataCraftingShaped>();
        }
        else if (full == "minecraft:smelting")
        {
            return std::make_shared<RecipeDataSimpleCooking>();
        }
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        else if (full == "minecraft:blasting")
        {
            return std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:smoking")
        {
            return std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:campfire_cooking")
        {
            return std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:stonecutting")
        {
            return std::make_shared<RecipeDataSingleItem>();
        }
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        else if (full == "minecraft:smithing")
        {
            return std::make_shared<RecipeDataSmithing>();
        }
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        else if (full == "minecraft:smithing_transform")
        {
            return std::make_shared<RecipeDataSmithingTransform>();
        }
        else if (full == "minecraft:smithing_trim")
        {
            return std::make_shared<RecipeDataSmithingTrim>();
        }
#endif
        return std::make_shared<RecipeDataSimpleCrafting>();
    }
#else
    std::shared_ptr<RecipeData> Recipe::CreateRecipeData(const RecipeDataType type)
    {
        if (type <= RecipeDataType::None || type >= RecipeDataType::NUM_RECIPE_DATA_TYPES)
        {
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(type)) + ".");
        }

        switch (type)
        {
        case RecipeDataType::CraftingShaped:
            return std::make_shared<RecipeDataCraftingShaped>();
        case RecipeDataType::CraftingShapeless:
            return std::make_shared<RecipeDataCraftingShapeless>();
        case RecipeDataType::Smelting:
        case RecipeDataType::Blasting:
        case RecipeDataType::Smoking:
        case RecipeDataType::CampfireCooking:
            return std::make_shared<RecipeDataSimpleCooking>();
        case RecipeDataType::CraftingSpecialArmordye:
        case RecipeDataType::CraftingSpecialBookcloning:
        case RecipeDataType::CraftingSpecialMapcloning:
        case RecipeDataType::CraftingSpecialMapextending:
        case RecipeDataType::CraftingSpecialFireworkRocket:
        case RecipeDataType::CraftingSpecialFireworkStar:
        case RecipeDataType::CraftingSpecialFireworkStarFade:
        case RecipeDataType::CraftingSpecialTippedarrow:
        case RecipeDataType::CraftingSpecialBannerduplicate:
        case RecipeDataType::CraftingSpecialShielddecoration:
        case RecipeDataType::CraftingSpecialShulkerboxcoloring:
        case RecipeDataType::CraftingSpecialSuspiciousstew:
        case RecipeDataType::CraftingSpecialRepairitem:
        case RecipeDataType::CraftingDecoratedPot:
            return std::make_shared<RecipeDataSimpleCrafting>();
        case RecipeDataType::Stonecutting:
            return std::make_shared<RecipeDataSingleItem>();
        case RecipeDataType::SmithingTransform:
            return std::make_shared<RecipeDataSmithingTransform>();
        case RecipeDataType::SmithingTrim:
            return std::make_shared<RecipeDataSmithingTrim>();
        default:
            // This should not happen
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(type)) + ".");
            return nullptr;
        }
        return nullptr;
    }
#endif

    DEFINE_NETWORK_TYPE(Recipe);
}
#endif

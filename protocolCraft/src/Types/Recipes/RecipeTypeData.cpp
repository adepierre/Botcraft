#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"

#include "protocolCraft/Types/Recipes/RecipeTypeDataNone.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataBlasting.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataCampfireCooking.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataShaped.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataShapeless.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmelting.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmoking.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmithing.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataStoneCutting.hpp"
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmithingTransform.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmithingTrim.hpp"
#endif

namespace ProtocolCraft
{
    RecipeTypeData::~RecipeTypeData()
    {

    }

    std::shared_ptr<RecipeTypeData> RecipeTypeData::CreateRecipeTypeData(const Identifier& recipe_type)
    {
        if (recipe_type.GetFull() == "minecraft:crafting_shapeless")
        {
            return std::make_shared<RecipeTypeDataShapeless>();
        }
        else if (recipe_type.GetFull() == "minecraft:crafting_shaped")
        {
            return std::make_shared<RecipeTypeDataShaped>();
        }
        else if (recipe_type.GetFull() == "minecraft:smelting")
        {
            return std::make_shared<RecipeTypeDataSmelting>();
        }
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        else if (recipe_type.GetFull() == "minecraft:blasting")
        {
            return std::make_shared<RecipeTypeDataBlasting>();
        }
        else if (recipe_type.GetFull() == "minecraft:smoking")
        {
            return std::make_shared<RecipeTypeDataSmoking>();
        }
        else if (recipe_type.GetFull() == "minecraft:campfire_cooking")
        {
            return std::make_shared<RecipeTypeDataCampfireCooking>();
        }
        else if (recipe_type.GetFull() == "minecraft:stonecutting")
        {
            return std::make_shared<RecipeTypeDataStoneCutting>();
        }
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        else if (recipe_type.GetFull() == "minecraft:smithing")
        {
            return std::make_shared<RecipeTypeDataSmithing>();
        }
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        else if (recipe_type.GetFull() == "minecraft:smithing_transform")
        {
            return std::make_shared<RecipeTypeDataSmithingTransform>();
        }
        else if (recipe_type.GetFull() == "minecraft:smithing_trim")
        {
            return std::make_shared<RecipeTypeDataSmithingTrim>();
        }
#endif
        else
        {
            return std::make_shared<RecipeTypeDataNone>();
        }
    }
}
#endif

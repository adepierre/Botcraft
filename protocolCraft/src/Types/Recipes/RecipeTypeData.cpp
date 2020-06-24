#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"

#include "protocolCraft/Types/Recipes/RecipeTypeDataNone.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataBlasting.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataCampfireCooking.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataShaped.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataShapeless.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmelting.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmoking.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataStoneCutting.hpp"

namespace ProtocolCraft
{
    std::shared_ptr<RecipeTypeData> RecipeTypeData::CreateRecipeTypeData(const std::string& recipe_type)
    {
        if (recipe_type == "minecraft:crafting_shapeless")
        {
            return std::shared_ptr<RecipeTypeDataShapeless>(new RecipeTypeDataShapeless);
        }
        else if (recipe_type == "minecraft:crafting_shaped")
        {
            return std::shared_ptr<RecipeTypeDataShaped>(new RecipeTypeDataShaped);
        }
        else if (recipe_type == "minecraft:smelting")
        {
            return std::shared_ptr<RecipeTypeDataSmelting>(new RecipeTypeDataSmelting);
        }
#if PROTOCOL_VERSION > 572
        else if (recipe_type == "minecraft:blasting")
        {
            return std::shared_ptr<RecipeTypeDataBlasting>(new RecipeTypeDataBlasting);
        }
        else if (recipe_type == "minecraft:smoking")
        {
            return std::shared_ptr<RecipeTypeDataSmoking>(new RecipeTypeDataSmoking);
        }
        else if (recipe_type == "minecraft:campfire_cooking")
        {
            return std::shared_ptr<RecipeTypeDataCampfireCooking>(new RecipeTypeDataCampfireCooking);
        }
        else if (recipe_type == "minecraft:stonecutting")
        {
            return std::shared_ptr<RecipeTypeDataStoneCutting>(new RecipeTypeDataStoneCutting);
        }
#endif
        else
        {
            return std::shared_ptr<RecipeTypeDataNone>(new RecipeTypeDataNone);
        }
    }
}
#endif

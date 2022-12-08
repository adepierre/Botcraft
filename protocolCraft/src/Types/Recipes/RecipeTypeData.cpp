#if PROTOCOL_VERSION > 347
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
#if PROTOCOL_VERSION > 452
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
#if PROTOCOL_VERSION > 732
        else if (recipe_type.GetFull() == "minecraft:smithing")
        {
            return std::make_shared<RecipeTypeDataSmithing>();
        }
#endif
        else
        {
            return std::make_shared<RecipeTypeDataNone>();
        }
    }
}
#endif

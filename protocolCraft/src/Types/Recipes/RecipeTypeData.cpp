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
            return std::shared_ptr<RecipeTypeDataShapeless>(new RecipeTypeDataShapeless);
        }
        else if (recipe_type.GetFull() == "minecraft:crafting_shaped")
        {
            return std::shared_ptr<RecipeTypeDataShaped>(new RecipeTypeDataShaped);
        }
        else if (recipe_type.GetFull() == "minecraft:smelting")
        {
            return std::shared_ptr<RecipeTypeDataSmelting>(new RecipeTypeDataSmelting);
        }
#if PROTOCOL_VERSION > 452
        else if (recipe_type.GetFull() == "minecraft:blasting")
        {
            return std::shared_ptr<RecipeTypeDataBlasting>(new RecipeTypeDataBlasting);
        }
        else if (recipe_type.GetFull() == "minecraft:smoking")
        {
            return std::shared_ptr<RecipeTypeDataSmoking>(new RecipeTypeDataSmoking);
        }
        else if (recipe_type.GetFull() == "minecraft:campfire_cooking")
        {
            return std::shared_ptr<RecipeTypeDataCampfireCooking>(new RecipeTypeDataCampfireCooking);
        }
        else if (recipe_type.GetFull() == "minecraft:stonecutting")
        {
            return std::shared_ptr<RecipeTypeDataStoneCutting>(new RecipeTypeDataStoneCutting);
        }
#endif
#if PROTOCOL_VERSION > 732
        else if (recipe_type.GetFull() == "minecraft:smithing")
        {
            return std::shared_ptr<RecipeTypeDataSmithing>(new RecipeTypeDataSmithing);
        }
#endif
        else
        {
            return std::shared_ptr<RecipeTypeDataNone>(new RecipeTypeDataNone);
        }
    }
}
#endif

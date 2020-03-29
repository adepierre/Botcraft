#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"

#include "protocolCraft/Types/Recipes/RecipeTypeDataNone.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataShaped.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataShapeless.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeDataSmelting.hpp"

namespace ProtocolCraft
{
    std::shared_ptr<RecipeTypeData> RecipeTypeData::CreateRecipeTypeData(const std::string& recipe_type)
    {
        if (recipe_type == "crafting_shapeless")
        {
            return std::shared_ptr<RecipeTypeDataShapeless>(new RecipeTypeDataShapeless);
        }
        else if (recipe_type == "crafting_shaped")
        {
            return std::shared_ptr<RecipeTypeDataShaped>(new RecipeTypeDataShaped);
        }
        else if (recipe_type == "smelting")
        {
            return std::shared_ptr<RecipeTypeDataSmelting>(new RecipeTypeDataSmelting);
        }
        else
        {
            return std::shared_ptr<RecipeTypeDataNone>(new RecipeTypeDataNone);
        }
    }
}
#endif

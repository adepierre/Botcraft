#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Recipes/RecipeDisplay.hpp"

#include "protocolCraft/Types/Recipes/FurnaceRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/ShapedCraftingRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/ShapelessCraftingRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/SmithingRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/StonecutterRecipeDisplay.hpp"

#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"


namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(FurnaceRecipeDisplay);
    DEFINE_NETWORK_TYPE(ShapedCraftingRecipeDisplay);
    DEFINE_NETWORK_TYPE(ShapelessCraftingRecipeDisplay);
    DEFINE_NETWORK_TYPE(SmithingRecipeDisplay);
    DEFINE_NETWORK_TYPE(StonecutterRecipeDisplay);

    std::shared_ptr<RecipeDisplayData> RecipeDisplay::CreateRecipeDisplayData(const RecipeDisplayDataType type)
    {
        switch (type)
        {
        case RecipeDisplayDataType::CraftingShapeless:
            return std::make_shared<ShapelessCraftingRecipeDisplay>();
        case RecipeDisplayDataType::CraftingShaped:
            return std::make_shared<ShapedCraftingRecipeDisplay>();
        case RecipeDisplayDataType::Furnace:
            return std::make_shared<FurnaceRecipeDisplay>();
        case RecipeDisplayDataType::Stonecutter:
            return std::make_shared<StonecutterRecipeDisplay>();
        case RecipeDisplayDataType::Smithing:
            return std::make_shared<SmithingRecipeDisplay>();
        default:
            // This should not happen
            throw std::runtime_error("Unable to create RecipeDisplayData with id: " + std::to_string(static_cast<int>(type)) + ".");
            return nullptr;
        }
    }

    DEFINE_NETWORK_TYPE(RecipeDisplay);
}
#endif

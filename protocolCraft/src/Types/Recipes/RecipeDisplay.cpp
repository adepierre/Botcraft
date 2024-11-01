#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Recipes/RecipeDisplay.hpp"

#include "protocolCraft/Types/Recipes/FurnaceRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/RecipeDisplayData.hpp"
#include "protocolCraft/Types/Recipes/ShapedCraftingRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/ShapelessCraftingRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/SmithingRecipeDisplay.hpp"
#include "protocolCraft/Types/Recipes/StonecutterRecipeDisplay.hpp"

#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"


namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(FurnaceRecipeDisplay);
    DEFINE_NETWORK_TYPE(RecipeDisplayData);
    DEFINE_NETWORK_TYPE(ShapedCraftingRecipeDisplay);
    DEFINE_NETWORK_TYPE(ShapelessCraftingRecipeDisplay);
    DEFINE_NETWORK_TYPE(SmithingRecipeDisplay);
    DEFINE_NETWORK_TYPE(StonecutterRecipeDisplay);

    RecipeDisplay& RecipeDisplay::SetType(const RecipeDisplayDataType type)
    {
        if (type <= RecipeDisplayDataType::None || type >= RecipeDisplayDataType::NUM_RECIPE_DISPLAY_DATA_TYPES)
        {
            throw std::runtime_error("Unable to create RecipeDisplayData with id: " + std::to_string(static_cast<int>(type)) + ".");
        }
        Type = type;

        switch (Type)
        {
        case RecipeDisplayDataType::CraftingShapeless:
            Data = std::make_shared<ShapelessCraftingRecipeDisplay>();
            break;
        case RecipeDisplayDataType::CraftingShaped:
            Data = std::make_shared<ShapedCraftingRecipeDisplay>();
            break;
        case RecipeDisplayDataType::Furnace:
            Data = std::make_shared<FurnaceRecipeDisplay>();
            break;
        case RecipeDisplayDataType::Stonecutter:
            Data = std::make_shared<StonecutterRecipeDisplay>();
            break;
        case RecipeDisplayDataType::Smithing:
            Data = std::make_shared<SmithingRecipeDisplay>();
            break;
        default:
            // This should not happen
            throw std::runtime_error("Unable to create RecipeDisplayData with id: " + std::to_string(static_cast<int>(Type)) + ".");
            Data = nullptr;
            break;
        }
        return *this;
    }


    void RecipeDisplay::ReadImpl(ReadIterator& iter, size_t& length)
    {
        SetType(ReadData<RecipeDisplayDataType, VarInt>(iter, length));
        if (GetData() != nullptr)
        {
            GetData()->Read(iter, length);
        }
    }

    void RecipeDisplay::WriteImpl(WriteContainer& container) const
    {
        WriteData<RecipeDisplayDataType, VarInt>(GetType(), container);
        if (GetData() != nullptr)
        {
            GetData()->Write(container);
        }
    }

    Json::Value RecipeDisplay::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<Type_index>)] = GetType();
        output[std::string(field_name<Data_index>)] = GetData() == nullptr ? Json::Object() : GetData()->Serialize();

        return output;
    }
}
#endif

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

    Recipe::~Recipe()
    {

    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    Recipe& Recipe::SetType(const Identifier& Type_)
    {
        Type = Type_;
        const std::string full = Type.GetFull();

        if (full == "minecraft:crafting_shapeless")
        {
            Data = std::make_shared<RecipeDataCraftingShapeless>();
        }
        else if (full == "minecraft:crafting_shaped")
        {
            Data = std::make_shared<RecipeDataCraftingShaped>();
        }
        else if (full == "minecraft:smelting")
        {
            Data = std::make_shared<RecipeDataSimpleCooking>();
        }
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        else if (full == "minecraft:blasting")
        {
            Data = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:smoking")
        {
            Data = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:campfire_cooking")
        {
            Data = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:stonecutting")
        {
            Data = std::make_shared<RecipeDataSingleItem>();
        }
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        else if (full == "minecraft:smithing")
        {
            Data = std::make_shared<RecipeDataSmithing>();
        }
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        else if (full == "minecraft:smithing_transform")
        {
            Data = std::make_shared<RecipeDataSmithingTransform>();
        }
        else if (full == "minecraft:smithing_trim")
        {
            Data = std::make_shared<RecipeDataSmithingTrim>();
        }
#endif
        else
        {
            Data = std::make_shared<RecipeDataSimpleCrafting>();
        }
        return *this;
    }
#else
    Recipe& Recipe::SetType(const RecipeDataType Type_)
    {
        if (Type_ <= RecipeDataType::None || Type_ >= RecipeDataType::NUM_RECIPE_DATA_TYPES)
        {
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(Type_)) + ".");
        }
        Type = Type_;

        switch (Type_)
        {
        case RecipeDataType::CraftingShaped:
            Data = std::make_shared<RecipeDataCraftingShaped>();
            break;
        case RecipeDataType::CraftingShapeless:
            Data = std::make_shared<RecipeDataCraftingShapeless>();
            break;
        case RecipeDataType::Smelting:
        case RecipeDataType::Blasting:
        case RecipeDataType::Smoking:
        case RecipeDataType::CampfireCooking:
            Data = std::make_shared<RecipeDataSimpleCooking>();
            break;
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
            Data = std::make_shared<RecipeDataSimpleCrafting>();
            break;
        case RecipeDataType::Stonecutting:
            Data = std::make_shared<RecipeDataSingleItem>();
            break;
        case RecipeDataType::SmithingTransform:
            Data = std::make_shared<RecipeDataSmithingTransform>();
            break;
        case RecipeDataType::SmithingTrim:
            Data = std::make_shared<RecipeDataSmithingTrim>();
            break;
        default:
            // This should not happen
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(Type_)) + ".");
            Data = nullptr;
            break;
        }
        return *this;
    }
#endif



#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    std::string_view Recipe::GetName() const
    {
        static constexpr std::array<std::string_view, static_cast<size_t>(RecipeDataType::NUM_RECIPE_DATA_TYPES)> recipe_names = {
            "crafting_shaped",
            "crafting_shapeless",
            "crafting_special_armordye",
            "crafting_special_bookcloning",
            "crafting_special_mapcloning",
            "crafting_special_mapextending",
            "crafting_special_firework_rocket",
            "crafting_special_firework_star",
            "crafting_special_firework_star_fade",
            "crafting_special_tippedarrow",
            "crafting_special_bannerduplicate",
            "crafting_special_shielddecoration",
            "crafting_special_shulkerboxcoloring",
            "crafting_special_suspiciousstew",
            "crafting_special_repairitem",
            "smelting",
            "blasting",
            "smoking",
            "campfire_cooking",
            "stonecutting",
            "smithing_transform",
            "smithing_trim",
            "crafting_decorated_pot",
        };
        if (GetType() <= RecipeDataType::None || GetType() >= RecipeDataType::NUM_RECIPE_DATA_TYPES)
        {
            return "";
        }
        return recipe_names[static_cast<size_t>(GetType())];
    }
#endif

    void Recipe::ReadImpl(ReadIterator& iter, size_t& length)
    {
#if PROTOCOL_VERSION < 453 /* < 1.14 */
        SetRecipeId(ReadData<Identifier>(iter, length));
        SetType(ReadData<Identifier>(iter, length));
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetType(ReadData<Identifier>(iter, length));
        SetRecipeId(ReadData<Identifier>(iter, length));
#else
        SetRecipeId(ReadData<Identifier>(iter, length));
        SetType(ReadData<RecipeDataType, VarInt>(iter, length));
#endif
        if (GetData() != nullptr)
        {
            GetData()->Read(iter, length);
        }
    }

    void Recipe::WriteImpl(WriteContainer& container) const
    {
#if PROTOCOL_VERSION < 453 /* < 1.14 */
        WriteData<Identifier>(GetRecipeId(), container);
        WriteData<Identifier>(GetType(), container);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        WriteData<Identifier>(GetType(), container);
        WriteData<Identifier>(GetRecipeId(), container);
#else
        WriteData<Identifier>(GetRecipeId(), container);
        WriteData<RecipeDataType, VarInt>(GetType(), container);
#endif
        if (GetData() != nullptr)
        {
            GetData()->Write(container);
        }
    }

    Json::Value Recipe::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<RecipeId_index>)] = GetRecipeId();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output[std::string(field_name<Type_index>)] = GetType().GetFull();
#else
        output[std::string(field_name<Type_index>)] = GetName();
#endif
        output[std::string(field_name<Data_index>)] = GetData() == nullptr ? Json::Object() : GetData()->Serialize();

        return output;
    }
}
#endif

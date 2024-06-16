#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
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
#include "protocolCraft/Utilities/PrivateTemplates.hpp"

namespace ProtocolCraft
{
    DEFINE_SERIALIZE(RecipeDataCraftingShaped);
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
    Recipe& Recipe::SetType(const Identifier& type_)
    {
        std::get<static_cast<size_t>(FieldsEnum::Type)>(fields) = type_;
        const std::string full = type_.GetFull();

        if (full == "minecraft:crafting_shapeless")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataCraftingShapeless>();
        }
        else if (full == "minecraft:crafting_shaped")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataCraftingShaped>();
        }
        else if (full == "minecraft:smelting")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCooking>();
        }
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        else if (full == "minecraft:blasting")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:smoking")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:campfire_cooking")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:stonecutting")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSingleItem>();
        }
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        else if (full == "minecraft:smithing")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSmithing>();
        }
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        else if (full == "minecraft:smithing_transform")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSmithingTransform>();
        }
        else if (full == "minecraft:smithing_trim")
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSmithingTrim>();
        }
#endif
        else
        {
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCrafting>();
        }
        return *this;
    }
#else
    Recipe& Recipe::SetType(const RecipeDataType type_)
    {
        if (type_ <= RecipeDataType::None || type_ >= RecipeDataType::NUM_RECIPE_DATA_TYPES)
        {
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(type_)) + ".");
        }
        std::get<static_cast<size_t>(FieldsEnum::Type)>(fields) = type_;

        switch (type_)
        {
        case RecipeDataType::CraftingShaped:
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataCraftingShaped>();
            break;
        case RecipeDataType::CraftingShapeless:
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataCraftingShapeless>();
            break;
        case RecipeDataType::Smelting:
        case RecipeDataType::Blasting:
        case RecipeDataType::Smoking:
        case RecipeDataType::CampfireCooking:
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCooking>();
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
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSimpleCrafting>();
            break;
        case RecipeDataType::Stonecutting:
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSingleItem>();
            break;
        case RecipeDataType::SmithingTransform:
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSmithingTransform>();
            break;
        case RecipeDataType::SmithingTrim:
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = std::make_shared<RecipeDataSmithingTrim>();
            break;
        default:
            // This should not happen
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(type_)) + ".");
            std::get<static_cast<size_t>(FieldsEnum::Data)>(fields) = nullptr;
            break;
        }
        return *this;
    }
#endif


#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    const Identifier& Recipe::GetType() const
    {
        return std::get<static_cast<size_t>(FieldsEnum::Type)>(fields);
    }
#else
    RecipeDataType Recipe::GetType() const
    {
        return std::get<static_cast<size_t>(FieldsEnum::Type)>(fields);
    }

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

    const std::shared_ptr<RecipeData>& Recipe::GetData() const
    {
        return std::get<static_cast<size_t>(FieldsEnum::Data)>(fields);
    }

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

        output[std::string(json_names[static_cast<size_t>(FieldsEnum::RecipeId)])] = GetRecipeId();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output[std::string(json_names[static_cast<size_t>(FieldsEnum::Type)])] = GetType().GetFull();
#else
        output[std::string(json_names[static_cast<size_t>(FieldsEnum::Type)])] = GetName();
#endif
        output[std::string(json_names[static_cast<size_t>(FieldsEnum::Data)])] = GetData() == nullptr ? Json::Object() : GetData()->Serialize();

        return output;
    }
}
#endif

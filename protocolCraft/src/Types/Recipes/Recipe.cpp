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

namespace ProtocolCraft
{

    Recipe::~Recipe()
    {

    }

    void Recipe::SetRecipeId(const Identifier& recipe_id_)
    {
        recipe_id = recipe_id_;
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void Recipe::SetType(const Identifier& type_)
    {
        type = type_;
        const std::string full = type.GetFull();

        if (full == "minecraft:crafting_shapeless")
        {
            data = std::make_shared<RecipeDataCraftingShapeless>();
        }
        else if (full == "minecraft:crafting_shaped")
        {
            data = std::make_shared<RecipeDataCraftingShaped>();
        }
        else if (full == "minecraft:smelting")
        {
            data = std::make_shared<RecipeDataSimpleCooking>();
        }
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        else if (full == "minecraft:blasting")
        {
            data = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:smoking")
        {
            data = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:campfire_cooking")
        {
            data = std::make_shared<RecipeDataSimpleCooking>();
        }
        else if (full == "minecraft:stonecutting")
        {
            data = std::make_shared<RecipeDataSingleItem>();
        }
#endif
#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        else if (full == "minecraft:smithing")
        {
            data = std::make_shared<RecipeDataSmithing>();
        }
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        else if (full == "minecraft:smithing_transform")
        {
            data = std::make_shared<RecipeDataSmithingTransform>();
        }
        else if (full == "minecraft:smithing_trim")
        {
            data = std::make_shared<RecipeDataSmithingTrim>();
        }
#endif
        else
        {
            data = std::make_shared<RecipeDataSimpleCrafting>();
        }
    }
#else
    void Recipe::SetType(const RecipeDataType type_)
    {
        if (type_ <= RecipeDataType::None || type_ >= RecipeDataType::NUM_RECIPE_DATA_TYPES)
        {
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(type_)) + ".");
        }
        type = type_;

        switch (type)
        {
        case RecipeDataType::CraftingShaped:
            data = std::make_shared<RecipeDataCraftingShaped>();
            break;
        case RecipeDataType::CraftingShapeless:
            data = std::make_shared<RecipeDataCraftingShapeless>();
            break;
        case RecipeDataType::Smelting:
        case RecipeDataType::Blasting:
        case RecipeDataType::Smoking:
        case RecipeDataType::CampfireCooking:
            data = std::make_shared<RecipeDataSimpleCooking>();
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
            data = std::make_shared<RecipeDataSimpleCrafting>();
            break;
        case RecipeDataType::Stonecutting:
            data = std::make_shared<RecipeDataSingleItem>();
            break;
        case RecipeDataType::SmithingTransform:
            data = std::make_shared<RecipeDataSmithingTransform>();
            break;
        case RecipeDataType::SmithingTrim:
            data = std::make_shared<RecipeDataSmithingTrim>();
            break;
        default:
            // This should not happen
            throw std::runtime_error("Unable to create recipe with id: " + std::to_string(static_cast<int>(type)) + ".");
            data = nullptr;
            break;
        }
    }
#endif


    const Identifier& Recipe::GetRecipeId() const
    {
        return recipe_id;
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    const Identifier& Recipe::GetType() const
    {
        return type;
    }
#else
    std::string_view Recipe::GetName() const
    {
        static constexpr std::array<std::string_view, static_cast<size_t>(RecipeDataType::NUM_RECIPE_DATA_TYPES)> names = {
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
        if (type <= RecipeDataType::None || type >= RecipeDataType::NUM_RECIPE_DATA_TYPES)
        {
            return "";
        }
        return names[static_cast<size_t>(type)];
    }
#endif

    std::shared_ptr<RecipeData> Recipe::GetData() const
    {
        return data;
    }

    void Recipe::ReadImpl(ReadIterator& iter, size_t& length)
    {
#if PROTOCOL_VERSION < 453 /* < 1.14 */
        recipe_id = ReadData<Identifier>(iter, length);
        SetType(ReadData<Identifier>(iter, length));
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetType(ReadData<Identifier>(iter, length));
        recipe_id = ReadData<Identifier>(iter, length);
#else
        recipe_id = ReadData<Identifier>(iter, length);
        SetType(static_cast<RecipeDataType>(static_cast<int>(ReadData<VarInt>(iter, length))));
#endif
        if (data != nullptr)
        {
            data->Read(iter, length);
        }
    }

    void Recipe::WriteImpl(WriteContainer& container) const
    {
#if PROTOCOL_VERSION < 453 /* < 1.14 */
        WriteData<Identifier>(recipe_id, container);
        WriteData<Identifier>(type, container);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        WriteData<Identifier>(type, container);
        WriteData<Identifier>(recipe_id, container);
#else
        WriteData<Identifier>(recipe_id, container);
        WriteData<VarInt>(static_cast<int>(type), container);
#endif
        if (data != nullptr)
        {
            data->Write(container);
        }
    }

    Json::Value Recipe::SerializeImpl() const
    {
        Json::Value output;

        output["recipe_id"] = recipe_id;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output["type"] = type;
#else
        output["type"] = GetName();
#endif
        output["data"] = data == nullptr ? Json::Object() : data->Serialize();

        return output;
    }
}
#endif

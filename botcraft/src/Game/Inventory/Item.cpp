#include "botcraft/Game/Inventory/Item.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    Item::Item(const ItemProperties& props)
    {
        id = props.id;
        name = props.name;
        stack_size = props.stack_size;
        durability = props.durability;
        LoadTypeAndMaterialFromName();
    }

    ItemId Item::GetId() const
    {
        return id;
    }

    const std::string& Item::GetName() const
    {
        return name;
    }

    unsigned char Item::GetStackSize() const
    {
        return stack_size;
    }

    ToolType Item::GetToolType() const
    {
        return tool_type;
    }

    ToolMaterial Item::GetToolMaterial() const
    {
        return tool_material;
    }

    int Item::GetMaxDurability() const
    {
        return durability;
    }

    void Item::LoadTypeAndMaterialFromName()
    {
        if (!Utilities::StartsWith(name, "minecraft:"))
        {
            if (name != "default")
            {
                LOG_WARNING("Unexpected item name format: " << name);
            }
            tool_type = ToolType::None;
            tool_material = ToolMaterial::None;
            return;
        }

        const std::string without_minecraft = name.substr(10);
        const std::vector<std::string> sub_parts = Utilities::SplitString(without_minecraft, '_');

        if (sub_parts.size() == 1 && sub_parts[0] == "shears")
        {
            tool_type = ToolType::Shears;
            tool_material = ToolMaterial::None;
            return;
        }

        if (sub_parts.size() == 1 || sub_parts.size() > 2)
        {
            tool_type = ToolType::None;
            tool_material = ToolMaterial::None;
            return;
        }

        if (sub_parts[1] == "axe")
        {
            tool_type = ToolType::Axe;
        }
        else if (sub_parts[1] == "hoe")
        {
            tool_type = ToolType::Hoe;
        }
        else if (sub_parts[1] == "pickaxe")
        {
            tool_type = ToolType::Pickaxe;
        }
        else if (sub_parts[1] == "shovel")
        {
            tool_type = ToolType::Shovel;
        }
        else if (sub_parts[1] == "sword")
        {
            tool_type = ToolType::Sword;
        }
        // Not a tool
        else
        {
            tool_type = ToolType::None;
            tool_material = ToolMaterial::None;
            return;
        }

        // If we're here, it's a tool, so extract the material
        if (sub_parts[0] == "wooden")
        {
            tool_material = ToolMaterial::Wood;
        }
        else if (sub_parts[0] == "golden")
        {
            tool_material = ToolMaterial::Gold;
        }
        else if (sub_parts[0] == "stone")
        {
            tool_material = ToolMaterial::Stone;
        }
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        else if (sub_parts[0] == "copper")
        {
            tool_material = ToolMaterial::Copper;
        }
#endif
        else if (sub_parts[0] == "iron")
        {
            tool_material = ToolMaterial::Iron;
        }
        else if (sub_parts[0] == "diamond")
        {
            tool_material = ToolMaterial::Diamond;
        }
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        else if (sub_parts[0] == "netherite")
        {
            tool_material = ToolMaterial::Netherite;
        }
#endif
        else
        {
            tool_material = ToolMaterial::None;
            LOG_WARNING("Unknown material for tool: " << name);
        }
    }

} //Botcraft

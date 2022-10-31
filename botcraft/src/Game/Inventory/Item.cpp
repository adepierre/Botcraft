#include "botcraft/Game/Inventory/Item.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    Item::Item(const ItemProperties& props)
    {
        id = props.id;
#if PROTOCOL_VERSION < 347
        damage_id = props.damage_id;
#endif
        name = props.name;
        stack_size = props.stack_size;
        LoadTypeAndMaterialFromName();
    }

    const int Item::GetId() const
    {
        return id;
    }

#if PROTOCOL_VERSION < 347
    const unsigned char Item::GetDamageId() const
    {
        return damage_id;
    }
#endif

    const std::string& Item::GetName() const
    {
        return name;
    }

    const unsigned char Item::GetStackSize() const
    {
        return stack_size;
    }

    const ToolType Item::GetToolType() const
    {
        return tool_type;
    }

    const ToolMaterial Item::GetToolMaterial() const
    {
        return tool_material;
    }

    void Item::LoadTypeAndMaterialFromName()
    {
        if (!StartsWith(name, "minecraft:"))
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
        const std::vector<std::string> sub_parts = SplitString(without_minecraft, '_');

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
        else if (sub_parts[0] == "iron")
        {
            tool_material = ToolMaterial::Iron;
        }
        else if (sub_parts[0] == "diamond")
        {
            tool_material = ToolMaterial::Diamond;
        }
#if PROTOCOL_VERSION > 578 // > 1.15.2
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

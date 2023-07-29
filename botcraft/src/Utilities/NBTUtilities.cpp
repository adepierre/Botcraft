#include "botcraft/Utilities/NBTUtilities.hpp"

#include "protocolCraft/Types/NBT/NBT.hpp"

using namespace ProtocolCraft;

namespace Botcraft::Utilities
{
    short GetEnchantmentLvl(const NBT::Value& item_nbt, const std::string& enchantment_name)
    {
        if (!item_nbt.HasData())
        {
            return 0;
        }

        if (!item_nbt.contains("Enchantments") ||
            !item_nbt["Enchantments"].is_list_of<NBT::TagCompound>())
        {
            return 0;
        }

        for (const auto& enchantment_tag : item_nbt["Enchantments"].as_list_of<NBT::TagCompound>())
        {
            if (!enchantment_tag.contains("id") ||
                !enchantment_tag.contains("lvl") ||
                !enchantment_tag["id"].is<NBT::TagString>() ||
                !enchantment_tag["lvl"].is<NBT::TagShort>())
            {
                continue;
            }

            if (enchantment_tag["id"].get<NBT::TagString>() == enchantment_name)
            {
                return enchantment_tag["lvl"].get<NBT::TagShort>();
            }
        }

        return 0;
    }

    int GetDamageCount(const NBT::Value& item_nbt)
    {
        if (!item_nbt.HasData())
        {
            return 0;
        }

        if (!item_nbt.contains("Damage") ||
            !item_nbt["Damage"].is<NBT::TagInt>())
        {
            return 0;
        }

        return item_nbt["Damage"].get<NBT::TagInt>();
    }
}

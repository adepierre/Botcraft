#include "botcraft/Utilities/NBTUtilities.hpp"

#include "protocolCraft/Types/NBT/NBT.hpp"

using namespace ProtocolCraft;

namespace Botcraft::Utilities
{
#if PROTOCOL_VERSION < 393 /* < 1.13 */
    short GetEnchantmentLvl(const NBT::Value& item_nbt, const Botcraft::EnchantmentID enchantment_id)
#else
    short GetEnchantmentLvl(const NBT::Value& item_nbt, const std::string& enchantment_name)
#endif
    {
        if (!item_nbt.HasData())
        {
            return 0;
        }

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        const std::string enchantment_key = "ench";
#else
        const std::string enchantment_key = "Enchantments";
#endif
        if (!item_nbt.contains(enchantment_key) ||
            !item_nbt[enchantment_key].is_list_of<NBT::TagCompound>())
        {
            return 0;
        }

        for (const auto& enchantment_tag : item_nbt[enchantment_key].as_list_of<NBT::TagCompound>())
        {
            if (!enchantment_tag.contains("id") ||
                !enchantment_tag.contains("lvl") ||
#if PROTOCOL_VERSION < 393 /* < 1.13 */
                !enchantment_tag["id"].is<NBT::TagInt>() ||
#else
                !enchantment_tag["id"].is<NBT::TagString>() ||
#endif
                (!enchantment_tag["lvl"].is<NBT::TagShort>() && !enchantment_tag["lvl"].is<NBT::TagInt>()))
            {
                continue;
            }

#if PROTOCOL_VERSION < 393 /* < 1.13 */
            if (enchantment_tag["id"].get<NBT::TagInt>() == static_cast<int>(enchantment_id))
#else
            if (enchantment_tag["id"].get<NBT::TagString>() == enchantment_name)
#endif
            {
                if (enchantment_tag["lvl"].is<NBT::TagShort>())
                {
                    return enchantment_tag["lvl"].get<NBT::TagShort>();
                }
                else if (enchantment_tag["lvl"].is<NBT::TagInt>())
                {
                    return enchantment_tag["lvl"].get<NBT::TagInt>();
                }
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

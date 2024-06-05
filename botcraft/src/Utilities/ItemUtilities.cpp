#include "botcraft/Utilities/ItemUtilities.hpp"

#include "protocolCraft/Types/Item/Slot.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentTypeInteger.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemEnchantments.hpp"
#endif

using namespace ProtocolCraft;

namespace Botcraft::Utilities
{
    std::string_view EnchantmentToString(const Botcraft::Enchantment enchantment)
    {
        switch (enchantment)
        {
        case Enchantment::Protection:
            return "protection";
        case Enchantment::FireProtection:
            return "fire_protection";
        case Enchantment::FeatherFalling:
            return "feather_falling";
        case Enchantment::BlastProtection:
            return "blast_protection";
        case Enchantment::ProjectileProtection:
            return "projectile_protection";
        case Enchantment::Respiration:
            return "respiration";
        case Enchantment::AquaAffinity:
            return "aqua_affinity";
        case Enchantment::Thorns:
            return "thorns";
        case Enchantment::DepthStrider:
            return "depth_strider";
        case Enchantment::FrostWalker:
            return "frost_walker";
        case Enchantment::BindingCurse:
            return "binding_curse";
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        case Enchantment::SoulSpeed:
            return "soul_speed";
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case Enchantment::SwiftSneak:
            return "swift_sneak";
#endif
        case Enchantment::Sharpness:
            return "sharpness";
        case Enchantment::Smite:
            return "smite";
        case Enchantment::BaneOfArthropods:
            return "bane_of_arthropods";
        case Enchantment::Knockback:
            return "knockback";
        case Enchantment::FireAspect:
            return "fire_aspect";
        case Enchantment::Looting:
            return "looting";
        case Enchantment::SweepingEdge:
            return "sweeping_edge";
        case Enchantment::Efficiency:
            return "efficiency";
        case Enchantment::SilkTouch:
            return "silk_touch";
        case Enchantment::Unbreaking:
            return "unbreaking";
        case Enchantment::Fortune:
            return "fortune";
        case Enchantment::Power:
            return "power";
        case Enchantment::Punch:
            return "punch";
        case Enchantment::Flame:
            return "flame";
        case Enchantment::Infinity:
            return "infinity";
        case Enchantment::LuckOfTheSea:
            return "luck_of_the_sea";
        case Enchantment::Lure:
            return "lure";
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        case Enchantment::Loyalty:
            return "loyalty";
        case Enchantment::Impaling:
            return "impaling";
        case Enchantment::Riptide:
            return "riptide";
        case Enchantment::Channeling:
            return "channeling";
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        case Enchantment::Multishot:
            return "multishot";
        case Enchantment::QuickCharge:
            return "quick_charge";
        case Enchantment::Piercing:
            return "piercing";
#endif
        case Enchantment::Mending:
            return "mending";
        case Enchantment::VanishingCurse:
            return "vanishing_curse";
        default:
            return "";
        }
    }

    short GetEnchantmentLvl(const Slot& item, const Enchantment enchantment)
    {
        if (item.IsEmptySlot())
        {
            return 0;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const NBT::Value& item_nbt = item.GetNbt();
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
            if (enchantment_tag["id"].get<NBT::TagInt>() == static_cast<int>(enchantment))
#else
            if (enchantment_tag["id"].get<NBT::TagString>() == EnchantmentToString(enchantment))
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
#else
        const auto& components = item.GetComponents().GetMap();
        auto c = components.find(Components::DataComponentTypes::Enchantments);
        if (c == components.end())
        {
            return 0;
        }

        const std::map<int, int>& enchantments = std::static_pointer_cast<Components::DataComponentTypeItemEnchantments>(c->second)->GetEnchantments();

        auto it = enchantments.find(static_cast<int>(enchantment));
        if (it == enchantments.end())
        {
            return 0;
        }

        return it->second;
#endif
    }

    int GetDamageCount(const Slot& item)
    {
        if (item.IsEmptySlot())
        {
            return 0;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const NBT::Value& item_nbt = item.GetNbt();
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
#else
        const auto& components = item.GetComponents().GetMap();
        auto it = components.find(Components::DataComponentTypes::Damage);
        if (it == components.end())
        {
            return 0;
        }

        std::shared_ptr<Components::DataComponentTypeInteger> damage = std::static_pointer_cast<Components::DataComponentTypeInteger>(it->second);
        return damage->GetValue();

#endif
    }
}

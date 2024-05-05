#include "botcraft/Utilities/ItemUtilities.hpp"

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/NBT/NBT.hpp"
#else
#include "protocolCraft/Types/Components/DataComponentPatch.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeInteger.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemEnchantments.hpp"
#endif

using namespace ProtocolCraft;

namespace Botcraft::Utilities
{
    short GetEnchantmentLvl(const Slot& item, const Enchantment enchantment)
    {
        if (item.IsEmptySlot())
        {
            return 0;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
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

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        std::string enchantment_name;
        switch (enchantment)
        {
        case Enchantment::Protection:
            enchantment_name = "protection";
            break;
        case Enchantment::FireProtection:
            enchantment_name = "fire_protection";
            break;
        case Enchantment::FeatherFalling:
            enchantment_name = "feather_falling";
            break;
        case Enchantment::BlastProtection:
            enchantment_name = "blast_protection";
            break;
        case Enchantment::ProjectileProtection:
            enchantment_name = "projectile_protection";
            break;
        case Enchantment::Respiration:
            enchantment_name = "respiration";
            break;
        case Enchantment::AquaAffinity:
            enchantment_name = "aqua_affinity";
            break;
        case Enchantment::Thorns:
            enchantment_name = "thorns";
            break;
        case Enchantment::DepthStrider:
            enchantment_name = "depth_strider";
            break;
        case Enchantment::FrostWalker:
            enchantment_name = "frost_walker";
            break;
        case Enchantment::BindingCurse:
            enchantment_name = "binding_curse";
            break;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        case Enchantment::SoulSpeed:
            enchantment_name = "soul_speed";
            break;
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case Enchantment::SwiftSneak:
            enchantment_name = "swift_sneak";
            break;
#endif
        case Enchantment::Sharpness:
            enchantment_name = "sharpness";
            break;
        case Enchantment::Smite:
            enchantment_name = "smite";
            break;
        case Enchantment::BaneOfArthropods:
            enchantment_name = "bane_of_arthropods";
            break;
        case Enchantment::Knockback:
            enchantment_name = "knockback";
            break;
        case Enchantment::FireAspect:
            enchantment_name = "fire_aspect";
            break;
        case Enchantment::Looting:
            enchantment_name = "looting";
            break;
        case Enchantment::SweepingEdge:
            enchantment_name = "sweeping_edge";
            break;
        case Enchantment::Efficiency:
            enchantment_name = "efficiency";
            break;
        case Enchantment::SilkTouch:
            enchantment_name = "silk_touch";
            break;
        case Enchantment::Unbreaking:
            enchantment_name = "unbreaking";
            break;
        case Enchantment::Fortune:
            enchantment_name = "fortune";
            break;
        case Enchantment::Power:
            enchantment_name = "power";
            break;
        case Enchantment::Punch:
            enchantment_name = "punch";
            break;
        case Enchantment::Flame:
            enchantment_name = "flame";
            break;
        case Enchantment::Infinity:
            enchantment_name = "infinity";
            break;
        case Enchantment::LuckOfTheSea:
            enchantment_name = "luck_of_the_sea";
            break;
        case Enchantment::Lure:
            enchantment_name = "lure";
            break;
        case Enchantment::Loyalty:
            enchantment_name = "loyalty";
            break;
        case Enchantment::Impaling:
            enchantment_name = "impaling";
            break;
        case Enchantment::Riptide:
            enchantment_name = "riptide";
            break;
        case Enchantment::Channeling:
            enchantment_name = "channeling";
            break;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        case Enchantment::Multishot:
            enchantment_name = "multishot";
            break;
        case Enchantment::QuickCharge:
            enchantment_name = "quick_charge";
            break;
        case Enchantment::Piercing:
            enchantment_name = "piercing";
            break;
#endif
        case Enchantment::Mending:
            enchantment_name = "mending";
            break;
        case Enchantment::VanishingCurse:
            enchantment_name = "vanishing_curse";
            break;
        default:
            enchantment_name = "";
            break;
        }
#endif

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
#else
        const Components::DataComponentPatch& components = item.GetComponents();
        if (!components.contains(Components::DataComponentTypes::Enchantments))
        {
            return 0;
        }

        const std::map<int, int>& enchantments = std::static_pointer_cast<Components::DataComponentTypeItemEnchantments>(components.GetComponent(Components::DataComponentTypes::Enchantments))->GetEnchantments();
        
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
        const NBT::Value& item_nbt = item.GetNBT();
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
        const Components::DataComponentPatch& components = item.GetComponents();
        if (!components.contains(Components::DataComponentTypes::Damage))
        {
            return 0;
        }

        std::shared_ptr<Components::DataComponentTypeInteger> damage = std::static_pointer_cast<Components::DataComponentTypeInteger>(components.GetComponent(Components::DataComponentTypes::Damage));
        return damage->GetValue();

#endif
    }
}

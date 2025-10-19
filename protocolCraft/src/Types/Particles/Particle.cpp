#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Particles/ParticleOption.hpp"
#include "protocolCraft/Types/Particles/BlockParticleOption.hpp"
#include "protocolCraft/Types/Particles/EmptyParticleOption.hpp"

#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/DustParticleOption.hpp"
#include "protocolCraft/Types/Particles/ItemParticleOption.hpp"
#else
#include "protocolCraft/Types/Particles/IconcrackParticleOption.hpp"
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/DustColorTransitionOption.hpp"
#include "protocolCraft/Types/Particles/VibrationParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Particles/SculkChargeParticleOption.hpp"
#include "protocolCraft/Types/Particles/ShriekParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Particles/ColorParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Particles/TrailParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Particles/PowerParticleOption.hpp"
#include "protocolCraft/Types/Particles/SpellParticleOption.hpp"
#endif

#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Particles/ExplosionParticleInfo.hpp" // Not a particle info type, used in ClientboundExplodePacket
#endif

#include <array>
#include <stdexcept>

namespace ProtocolCraft
{
    // ParticlesOption subtypes
    DEFINE_NETWORK_TYPE(BlockParticleOption);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_NETWORK_TYPE(ColorParticleOption);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_NETWORK_TYPE(DustColorTransitionOption);
#endif
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(DustParticleOption);
#endif
    DEFINE_NETWORK_TYPE(EmptyParticleOption);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
    DEFINE_NETWORK_TYPE(IconcrackParticleOption);
#endif
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(ItemParticleOption);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(SculkChargeParticleOption);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(ShriekParticleOption);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    DEFINE_NETWORK_TYPE(TrailParticleOption);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
    DEFINE_NETWORK_TYPE(PowerParticleOption);
    DEFINE_NETWORK_TYPE(SpellParticleOption);
#endif

#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
    DEFINE_NETWORK_TYPE(ExplosionParticleInfo); // Not a particle info type, used in ClientboundExplodePacket
#endif

    Particle::Particle()
    {

    };

    Particle::~Particle()
    {

    }

    std::string_view Particle::GetName() const
    {
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
        static constexpr std::array<std::string_view, static_cast<size_t>(ParticleType::NUM_PARTICLE_TYPES)> names = {
    #if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            "ambient_entity_effect",
    #endif
            "angry_villager",
    #if PROTOCOL_VERSION < 757 /* < 1.18 */
            "barrier",
    #endif
    #if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 757 /* < 1.18 */
            "light",
    #endif
            "block",
    #if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            "block_marker",
    #endif
            "bubble",
            "cloud",
    #if PROTOCOL_VERSION > 772 /* > 1.21.8 */
            "copper_fire_flame",
    #endif
            "crit",
            "damage_indicator",
            "dragon_breath",
            "dripping_lava",
    #if PROTOCOL_VERSION > 476 /* > 1.13.2 */
            "falling_lava",
            "landing_lava",
    #endif
            "dripping_water",
    #if PROTOCOL_VERSION > 476 /* > 1.13.2 */
            "falling_water",
    #endif
            "dust",
    #if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            "dust_color_transition",
    #endif
            "effect",
            "elder_guardian",
            "enchanted_hit",
            "enchant",
            "end_rod",
            "entity_effect",
            "explosion_emitter",
            "explosion",
    #if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            "gust",
    #if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            "gust_emitter",
    #endif
    #endif
    #if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            "small_gust",
            "gust_emitter_large",
            "gust_emitter_small",
    #endif
    #if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            "sonic_boom",
    #endif
            "falling_dust",
            "firework",
            "fishing",
            "flame",
    #if PROTOCOL_VERSION > 761 /* > 1.19.3 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
            "dripping_cherry_leaves",
            "falling_cherry_leaves",
            "landing_cherry_leaves",
    #endif
    #if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            "infested",
    #endif
    #if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            "cherry_leaves",
    #endif
    #if PROTOCOL_VERSION > 768 /* > 1.21.3 */
            "pale_oak_leaves",
    #endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            "tinted_leaves",
#endif
    #if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            "sculk_soul",
            "sculk_charge",
            "sculk_charge_pop",
    #endif
    #if PROTOCOL_VERSION > 734 /* > 1.15.2 */
            "soul_fire_flame",
            "soul",
    #endif
    #if PROTOCOL_VERSION > 476 /* > 1.13.2 */
            "flash",
    #endif
            "happy_villager",
    #if PROTOCOL_VERSION > 476 /* > 1.13.2 */
            "composter",
    #endif
            "heart",
            "instant_effect",
            "item",
    #if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            "vibration",
    #endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            "trail",
#endif
            "item_slime",
    #if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            "item_cobweb",
    #endif
            "item_snowball",
            "large_smoke",
            "lava",
            "mycelium",
            "note",
            "poof",
            "portal",
            "rain",
            "smoke",
    #if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            "white_smoke",
    #endif
    #if PROTOCOL_VERSION > 476 /* > 1.13.2 */
            "sneeze",
    #endif
            "spit",
            "squid_ink",
            "sweep_attack",
            "totem_of_undying",
            "underwater",
            "splash",
            "witch",
            "bubble_pop",
            "current_down",
            "bubble_column_up",
            "nautilus",
            "dolphin",
    #if PROTOCOL_VERSION > 476 /* > 1.13.2 */
            "campfire_cosy_smoke",
            "campfire_signal_smoke",
    #endif
    #if PROTOCOL_VERSION > 572 /* > 1.14.4 */
            "dripping_honey",
            "falling_honey",
            "landing_honey",
            "falling_nectar",
    #endif
    #if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            "falling_spore_blossom",
    #endif
    #if PROTOCOL_VERSION > 734 /* > 1.15.2 */
            "ash",
            "crimson_spore",
            "warped_spore",
    #endif
    #if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            "spore_blossom_air",
    #endif
    #if PROTOCOL_VERSION > 734 /* > 1.15.2 */
            "dripping_obsidian_tear",
            "falling_obsidian_tear",
            "landing_obsidian_tear",
            "reverse_portal",
            "white_ash",
    #endif
    #if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            "small_flame",
            "snowflake",
            "dripping_dripstone_lava",
            "falling_dripstone_lava",
            "dripping_dripstone_water",
            "falling_dripstone_water",
            "glow_squid_ink",
            "glow",
            "wax_on",
            "wax_off",
            "electric_spark",
            "scrape",
    #endif
    #if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            "shriek",
    #endif
    #if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            "egg_crack",
    #endif
    #if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            "dust_plume",
    #if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            "gust_dust",
    #endif
            "trial_spawner_detection",
    #endif
    #if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            "trial_spawner_detection_ominous",
            "vault_connection",
            "dust_pillar",
            "ominous_spawning",
            "raid_omen",
            "trial_omen",
    #endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            "block_crumble",
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            "firefly",
#endif
        };
#else
        static constexpr std::array<std::string_view, static_cast<size_t>(ParticleType::NUM_PARTICLE_TYPES)> names = {
            "explode",
            "largeexplode",
            "hugeexplosion",
            "fireworksSpark",
            "bubble",
            "splash",
            "wake",
            "suspended",
            "depthsuspend",
            "crit",
            "magicCrit",
            "smoke",
            "largesmoke",
            "spell",
            "instantSpell",
            "mobSpell",
            "mobSpellAmbient",
            "witchMagic",
            "dripWater",
            "dripLava",
            "angryVillager",
            "happyVillager",
            "townaura",
            "note",
            "portal",
            "enchantmenttable",
            "flame",
            "lava",
            "footstep",
            "cloud",
            "reddust",
            "snowballpoof",
            "snowshovel",
            "slime",
            "heart",
            "barrier",
            "iconcrack",
            "blockcrack",
            "blockdust",
            "droplet",
            "take",
            "mobappearance",
            "dragonbreath",
            "endRod",
            "damageIndicator",
            "sweepAttack",
            "fallingdust",
            "totem",
            "spit",
        };
#endif
        if (ParticleType <= ParticleType::None || ParticleType >= ParticleType::NUM_PARTICLE_TYPES)
        {
            return "";
        }
        return names[static_cast<size_t>(ParticleType)];
    }

    Particle& Particle::SetParticleType(const ProtocolCraft::ParticleType particle_type_)
    {
        if (particle_type_ <= ParticleType::None || particle_type_ >= ParticleType::NUM_PARTICLE_TYPES)
        {
            throw std::runtime_error("Unable to create particle with id: " + std::to_string(static_cast<int>(particle_type_)) + ".");
        }
        ParticleType = particle_type_;

        switch (ParticleType)
        {
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
        case ParticleType::Block:
        case ParticleType::FallingDust:
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        case ParticleType::BlockMarker:
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        case ParticleType::DustPillar:
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        case ParticleType::BlockCrumble:
#endif
            Option = std::make_shared<BlockParticleOption>();
            break;
        case ParticleType::Dust:
            Option = std::make_shared<DustParticleOption>();
            break;
        case ParticleType::Item:
            Option = std::make_shared<ItemParticleOption>();
            break;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::DustColorTransition:
            Option = std::make_shared<DustColorTransitionOption>();
            break;
        case ParticleType::Vibration:
            Option = std::make_shared<VibrationParticleOption>();
            break;
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case ParticleType::SculkCharge:
            Option = std::make_shared<SculkChargeParticleOption>();
            break;
        case ParticleType::Shriek:
            Option = std::make_shared<ShriekParticleOption>();
            break;
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        case ParticleType::EntityEffect:
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        case ParticleType::TintedLeaves:
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        case ParticleType::Flash:
#endif
            Option = std::make_shared<ColorParticleOption>();
            break;
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        case ParticleType::Trail:
            Option = std::make_shared<TrailParticleOption>();
            break;
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        case ParticleType::DragonBreath:
            Option = std::make_shared<PowerParticleOption>();
            break;
        case ParticleType::Effect:
        case ParticleType::InstantEffect:
            Option = std::make_shared<SpellParticleOption>();
            break;
#endif
#else //1.12.2
        case ParticleType::Blockcrack:
        case ParticleType::Blockdust:
        case ParticleType::FallingDust:
            Option = std::make_shared<BlockParticleOption>();
            break;
        case ParticleType::Iconcrack:
            Option = std::make_shared<IconcrackParticleOption>();
            break;
#endif
        default:
            Option = std::make_shared<EmptyParticleOption>();
            break;
        }
        return *this;
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void Particle::ReadOption(ReadIterator& iter, size_t& length)
    {
        if (Option != nullptr)
        {
            Option->Read(iter, length);
        }
    }

    void Particle::WriteOption(WriteContainer& container) const
    {
        if (Option != nullptr)
        {
            Option->Write(container);
        }
    }
#endif

    void Particle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        ParticleType = ReadData<ProtocolCraft::ParticleType, VarInt>(iter, length);
        SetParticleType(ParticleType);
        if (Option != nullptr)
        {
            Option->Read(iter, length);
        }
    }

    void Particle::WriteImpl(WriteContainer& container) const
    {
        WriteData<ProtocolCraft::ParticleType, VarInt>(ParticleType, container);
        if (Option != nullptr)
        {
            Option->Write(container);
        }
    }

    Json::Value Particle::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<ParticleType_index>)] = GetName();
        output[std::string(field_name<Option_index>)] = Option == nullptr ? Json::Object() : Option->Serialize();

        return output;
    }
}

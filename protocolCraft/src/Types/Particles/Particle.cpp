#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"
#include "protocolCraft/Types/Particles/BlockParticleOptions.hpp"
#include "protocolCraft/Types/Particles/EmptyParticleOptions.hpp"

#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/DustParticleOptions.hpp"
#include "protocolCraft/Types/Particles/ItemParticleOptions.hpp"
#else
#include "protocolCraft/Types/Particles/IconcrackParticleOptions.hpp"
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/DustColorTransitionOptions.hpp"
#include "protocolCraft/Types/Particles/VibrationParticleOptions.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Particles/SculkChargeParticleOptions.hpp"
#include "protocolCraft/Types/Particles/ShriekParticleOptions.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Particles/ColorParticleOptions.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Particles/TrailParticleOptions.hpp"
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
    // ParticlesOptions
    DEFINE_NETWORK_TYPE(BlockParticleOptions);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_NETWORK_TYPE(ColorParticleOptions);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_NETWORK_TYPE(DustColorTransitionOptions);
#endif
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(DustParticleOptions);
#endif
    DEFINE_NETWORK_TYPE(EmptyParticleOptions);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
    DEFINE_NETWORK_TYPE(IconcrackParticleOptions);
#endif
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(ItemParticleOptions);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(SculkChargeParticleOptions);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(ShriekParticleOptions);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    DEFINE_NETWORK_TYPE(TrailParticleOptions);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
    DEFINE_NETWORK_TYPE(PowerParticleOptions);
    DEFINE_NETWORK_TYPE(SpellParticleOptions);
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
            Options = std::make_shared<BlockParticleOptions>();
            break;
        case ParticleType::Dust:
            Options = std::make_shared<DustParticleOptions>();
            break;
        case ParticleType::Item:
            Options = std::make_shared<ItemParticleOptions>();
            break;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::DustColorTransition:
            Options = std::make_shared<DustColorTransitionOptions>();
            break;
        case ParticleType::Vibration:
            Options = std::make_shared<VibrationParticleOptions>();
            break;
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case ParticleType::SculkCharge:
            Options = std::make_shared<SculkChargeParticleOptions>();
            break;
        case ParticleType::Shriek:
            Options = std::make_shared<ShriekParticleOptions>();
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
            Options = std::make_shared<ColorParticleOptions>();
            break;
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        case ParticleType::Trail:
            Options = std::make_shared<TrailParticleOptions>();
            break;
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        case ParticleType::DragonBreath:
            Options = std::make_shared<PowerParticleOptions>();
            break;
        case ParticleType::Effect:
        case ParticleType::InstantEffect:
            Options = std::make_shared<SpellParticleOptions>();
            break;
#endif
#else //1.12.2
        case ParticleType::Blockcrack:
        case ParticleType::Blockdust:
        case ParticleType::FallingDust:
            Options = std::make_shared<BlockParticleOptions>();
            break;
        case ParticleType::Iconcrack:
            Options = std::make_shared<IconcrackParticleOptions>();
            break;
#endif
        default:
            Options = std::make_shared<EmptyParticleOptions>();
            break;
        }
        return *this;
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void Particle::ReadOptions(ReadIterator& iter, size_t& length)
    {
        if (Options != nullptr)
        {
            Options->Read(iter, length);
        }
    }

    void Particle::WriteOptions(WriteContainer& container) const
    {
        if (Options != nullptr)
        {
            Options->Write(container);
        }
    }
#endif

    void Particle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        ParticleType = ReadData<ProtocolCraft::ParticleType, VarInt>(iter, length);
        SetParticleType(ParticleType);
        if (Options != nullptr)
        {
            Options->Read(iter, length);
        }
    }

    void Particle::WriteImpl(WriteContainer& container) const
    {
        WriteData<ProtocolCraft::ParticleType, VarInt>(ParticleType, container);
        if (Options != nullptr)
        {
            Options->Write(container);
        }
    }

    Json::Value Particle::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<ParticleType_index>)] = GetName();
        output[std::string(field_name<Options_index>)] = Options == nullptr ? Json::Object() : Options->Serialize();

        return output;
    }
}

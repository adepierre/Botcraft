#pragma once

#include <memory>
#include <string_view>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    enum class ParticleType
    {
        None = -1,
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        AmbientEntityEffect,
#endif
        AngryVillager,
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        Barrier,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 757 /* < 1.18 */
        Light,
#endif
        Block,
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        BlockMarker,
#endif
        Bubble,
        Cloud,
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        CopperFireFlame,
#endif
        Crit,
        DamageIndicator,
        DragonBreath,
        DrippingLava,
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        FallingLava,
        LandingLava,
#endif
        DrippingWater,
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        FallingWater,
#endif
        Dust,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        DustColorTransition,
#endif
        Effect,
        ElderGuardian,
        EnchantedHit,
        Enchant,
        EndRod,
        EntityEffect,
        ExplosionEmitter,
        Explosion,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        Gust,
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GustEmitter,
#endif
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SmallGust,
        GustEmitterLarge,
        GustEmitterSmall,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SonicBoom,
#endif
        FallingDust,
        Firework,
        Fishing,
        Flame,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        DrippingCherryLeaves,
        FallingCherryLeaves,
        LandingCherryLeaves,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        Infested,
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        CherryLeaves,
#endif
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        PaleOakLeaves,
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        TintedLeaves,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SculkSoul,
        SculkCharge,
        SculkChargePop,
#endif
#if PROTOCOL_VERSION > 734 /* > 1.15.2 */
        SoulFireFlame,
        Soul,
#endif
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        Flash,
#endif
        HappyVillager,
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        Composter,
#endif
        Heart,
        InstantEffect,
        Item,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        Vibration,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        Trail,
#endif
        ItemSlime,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        ItemCobweb,
#endif
        ItemSnowball,
        LargeSmoke,
        Lava,
        Mycelium,
        Note,
        Poof,
        Portal,
        Rain,
        Smoke,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        WhiteSmoke,
#endif
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        Sneeze,
#endif
        Spit,
        SquidInk,
        SweepAttack,
        TotemOfUndying,
        Underwater,
        Splash,
        Witch,
        BubblePop,
        CurrentDown,
        BubbleColumnUp,
        Nautilus,
        Dolphin,
#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
        CampfireCosySmoke,
        CampfireSignalSmoke,
#endif
#if PROTOCOL_VERSION > 572 /* > 1.14.4 */
        DrippingHoney,
        FallingHoney,
        LandingHoney,
        FallingNectar,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        FallingSporeBlossom,
#endif
#if PROTOCOL_VERSION > 734 /* > 1.15.2 */
        Ash,
        CrimsonSpore,
        WarpedSpore,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SporeBlossomAir,
#endif
#if PROTOCOL_VERSION > 734 /* > 1.15.2 */
        DrippingObsidianTear,
        FallingObsidianTear,
        LandingObsidianTear,
        ReversePortal,
        WhiteAsh,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SmallFlame,
        Snowflake,
        DrippingDripstoneLava,
        FallingDripstoneLava,
        DrippingDripstoneWater,
        FallingDripstoneWater,
        GlowSquidInk,
        Glow,
        WaxOn,
        WaxOff,
        ElectricSpark,
        Scrape,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Shriek,
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        EggCrack,
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        DustPlume,
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GustDust,
#endif
        TrialSpawnerDetection,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        TrialSpawnerDetectionOminous,
        VaultConnection,
        DustPillar,
        OminousSpawning,
        RaidOmen,
        TrialOmen,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        BlockCrumble,
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        Firefly,
#endif
        NUM_PARTICLE_TYPES
    };
#else
    enum class ParticleType
    {
        None = -1,
        Explode,
        LargeExplode,
        HugeExplosion,
        FireworksSpark,
        Bubble,
        Splash,
        Wake,
        Suspended,
        Depthsuspend,
        Crit,
        MagicCrit,
        Smoke,
        LargeSmoke,
        Spell,
        InstantSpell,
        MobSpell,
        MobSpellAmbient,
        WitchMagic,
        DripWater,
        DripLava,
        AngryVillager,
        HappyVillager,
        Townaura,
        Note,
        Portal,
        EnchantmentTable,
        Flame,
        Lava,
        Footstep,
        Cloud,
        Reddust,
        Snowballpoof,
        Snowshovel,
        Slime,
        Heart,
        Barrier,
        Iconcrack,
        Blockcrack,
        Blockdust,
        Droplet,
        Take,
        MobAppearance,
        DragonBreath,
        EndRod,
        DamageIndicator,
        SweepAttack,
        FallingDust,
        Totem,
        Spit,
        NUM_PARTICLE_TYPES
    };
#endif

    class ParticleOptions;

    class Particle : public NetworkType
    {
    public:
        Particle();
        virtual ~Particle();
        std::string_view GetName() const;

        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ParticleType, Internal::DiffType<ProtocolCraft::ParticleType, VarInt>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Options, std::shared_ptr<ParticleOptions>);

        GETTER(ParticleType);
        GETTER(Options);

        Particle& SetParticleType(const ProtocolCraft::ParticleType particle_type_);

        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    public:
        void ReadOptions(ReadIterator& iter, size_t& length);
        void WriteOptions(WriteContainer& container) const;
#endif
    };
}

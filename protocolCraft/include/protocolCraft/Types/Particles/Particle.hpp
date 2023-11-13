#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    enum class ParticleType
    {
        None = -1,
        AmbientEntityEffect,
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
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        CherryLeaves,
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
        ItemSlime,
        ItemSnowball,
        LargeSmoke,
        Lava,
        Mycelium,
        Note,
        Poof,
        Portal,
        Rain,
        Smoke,
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
    };
#endif

    class Particle : public NetworkType
    {
    public:
        
        Particle();
        
        virtual ~Particle();
        
        virtual std::string GetName() const = 0;
        
        virtual ParticleType GetType() const = 0;
        
        static std::shared_ptr<Particle> CreateParticle(const ParticleType type);
    };
}

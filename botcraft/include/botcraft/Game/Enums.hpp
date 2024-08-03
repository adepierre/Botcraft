#pragma once

// To make gcc happy about std::ostream
#include <iosfwd>

namespace Botcraft
{
    enum class ChatMode
    {
        Enabled,
        CommandsOnly,
        Hidden
    };

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    enum class Dimension
    {
        None = -2,
        Nether,
        Overworld,
        End
    };
#endif

    enum class Difficulty
    {
        None = -1,
        Peaceful,
        Easy,
        Normal,
        Hard
    };

    enum class SoundSource
    {
        Null = -1,
        Master = 0,
        Music,
        Records,
        Weather,
        Blocks,
        Hostile,
        Neutral,
        Players,
        Ambient,
        Voice
    };

    enum class GameType
    {
        None = -1,
        Survival,
        Creative,
        Adventure,
        Spectator
    };

#if PROTOCOL_VERSION < 393 /* < 1.13 */
    enum class Enchantment
    {
        Protection = 0,
        FireProtection = 1,
        FeatherFalling = 2,
        BlastProtection = 3,
        ProjectileProtection = 4,
        Respiration = 5,
        AquaAffinity = 6,
        Thorns = 7,
        DepthStrider = 8,
        FrostWalker = 9,
        BindingCurse = 10,
        Sharpness = 16,
        Smite = 17,
        BaneOfArthropods = 18,
        Knockback = 19,
        FireAspect = 20,
        Looting = 21,
        SweepingEdge = 22,
        Efficiency = 32,
        SilkTouch = 33,
        Unbreaking = 34,
        Fortune = 35,
        Power = 48,
        Punch = 49,
        Flame = 50,
        Infinity = 51,
        LuckOfTheSea = 61,
        Lure = 62,
        Mending = 70,
        VanishingCurse = 71,
    };
#else
    enum class Enchantment
    {
        None = -1,
        Protection,
        FireProtection,
        FeatherFalling,
        BlastProtection,
        ProjectileProtection,
        Respiration,
        AquaAffinity,
        Thorns,
        DepthStrider,
        FrostWalker,
        BindingCurse,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        SoulSpeed,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SwiftSneak,
#endif
        Sharpness,
        Smite,
        BaneOfArthropods,
        Knockback,
        FireAspect,
        Looting,
        SweepingEdge,
        Efficiency,
        SilkTouch,
        Unbreaking,
        Fortune,
        Power,
        Punch,
        Flame,
        Infinity,
        LuckOfTheSea,
        Lure,
        Loyalty,
        Impaling,
        Riptide,
        Channeling,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        Multishot,
        QuickCharge,
        Piercing,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        Density,
        Breach,
        WindBurst,
#endif
        Mending,
        VanishingCurse,
    };
#endif

    enum class Hand
    {
        Right = 0,
        Main = 0,
        Left = 1,
        Off = 1
    };
    std::ostream& operator<<(std::ostream& os, const Hand v);

    enum class TintType: char
    {
        None,
        Water,
        Redstone,
        Grass,
        Leaves
    };

    enum class Orientation
    {
        None = -1,
        /// @brief y = -1
        Bottom = 0,
        /// @brief z = -1
        North,
        /// @brief x = -1
        West,
        /// @brief x = 1
        East,
        /// @brief z = 1
        South,
        /// @brief y = 1
        Top
    };

    enum class PlayerDiggingStatus
    {
        StartDigging = 0,
        CancelDigging,
        FinishDigging,
        DropItemStack,
        DropItem,
        ShootArrow,
        FinishEating = ShootArrow,
        SwapItemHand
    };

    enum class Direction
    {
        /// @brief -Y
        Down = 0,
        /// @brief +Y
        Up,
        /// @brief -Z
        North,
        /// @brief +Z
        South,
        /// @brief -X
        West,
        /// @brief +X
        East
    };
    typedef Direction PlayerDiggingFace;
    std::ostream& operator<<(std::ostream& os, const Direction v);

    // Types are detailed in registries, see https://wiki.vg/Inventory

    enum class InventoryType
    {
        PlayerInventory = -2,
        Default = -1,
        Generic9x1 = 0,
        Generic9x2,
        Generic9x3,
        Generic9x4,
        Generic9x5,
        Generic9x6,
        Generic3x3,
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        Crafter3x3,
#endif
        Anvil,
        Beacon,
        BlastFurnace,
        BrewingStand,
        Crafting,
        Enchantment,
        Furnace,
        Grindstone,
        Hopper,
        Lectern,
        Loom,
        Merchant,
        ShulkerBox,
        Smithing,
        Smoker,
        CartographyTable,
        StoneCutter
    };

    enum class Pose
    {
        Standing,
        FallFlying,
        Sleeping,
        Swimming,
        SpinAttack,
        Crouching,
        LongJumping,
        Dying,
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Croaking,
        UsingTongue,
        Sitting,
        Roaring,
        Sniffing,
        Emerging,
        Digging,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        Sliding,
        Shooting,
        Inhaling,
#endif
    };

    enum class EquipmentSlot
    {
        MainHand = 0,
        OffHand,
        Boots,
        Leggings,
        ChestPlate,
        Helmet
    };

    enum class ToolMaterial: char
    {
        None = 0,
        Wood,
        Gold,
        Stone,
        Iron,
        Diamond,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Netherite,
#endif
        NUM_TOOL_MATERIAL
    };

    enum class ToolType: char
    {
        None = 0,
        Axe,
        Hoe,
        Pickaxe,
        Shears,
        Shovel,
        Sword,
        NUM_TOOL_TYPE
    };

    enum class EntityEffectType
    {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        None = 0,
#else
        None = -1,
#endif
        Speed,
        Slowness,
        Haste,
        MiningFatigue,
        Strength,
        InstantHealth,
        InstantDamage,
        JumpBoost,
        Nausea,
        Regeneration,
        Resistance,
        FireResistance,
        WaterBreathing,
        Invisibility,
        Blindness,
        NightVision,
        Hunger,
        Weakness,
        Poison,
        Wither,
        HealthBoost,
        Absorption,
        Saturation,
        Glowing,
        Levitation,
        Luck,
        Unluck,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        SlowFalling,
        ConduitPower,
        DolphinsGrace,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        BadOmen,
        HeroOfTheVillage,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Darkness,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        TrialOmen,
        RaidOmen,
        WindCharged,
        Weaving,
        Oozing,
        Infested,
#endif
    };

    enum class PlayerCommandAction
    {
        PressShiftKey,
        ReleaseShifKey,
        StopSleeping,
        StartSprinting,
        StopSprinting,
        StartRidingJump,
        StopRidingJump,
        OpenInventory,
        StartFallFlying
    };
} // Botcraft

#pragma once

namespace Botcraft
{
    enum class ChatMode
    {
        Enabled,
        CommandsOnly,
        Hidden
    };

#if PROTOCOL_VERSION < 719
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

    enum class Hand
    {
        Right = 0,
        Main = 0,
        Left = 1,
        Off = 1
    };
    std::ostream& operator<<(std::ostream& os, const Hand v);

    enum class TintType
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
        Bottom = 0, // y = -1
        North,      // z = -1
        West,       // x = -1
        East,       // x = 1
        South,      // z = 1
        Top         // y = 1
    };

    enum class PlayerDiggingStatus
    {
        StartDigging = 0,
        CancelDigging,
        FinishDigging,
        DropItemStack,
        DropItem,
        ShootArrow_FinishEating,
        SwapItemHand
    };

    enum class Direction
    {
        Down = 0, // -Y
        Up,        // +Y
        North,      // -Z
        South,      // +Z
        West,       // -X
        East        // +X
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
        Dying
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

    enum class ToolMaterial
    {
        None = 0,
        Wood,
        Gold,
        Stone,
        Iron,
        Diamond,
#if PROTOCOL_VERSION > 578 // > 1.15.2
        Netherite,
#endif
        NUM_TOOL_MATERIAL
    };

    enum class ToolType
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
        None = 0,
        Speed = 1,
        Slowness = 2,
        Haste = 3,
        MiningFatigue = 4,
        Strength = 5,
        InstantHealth = 6,
        InstantDamage = 7,
        JumpBoost = 8,
        Nausea = 9,
        Regeneration = 10,
        Resistance = 11,
        FireResistance = 12,
        WaterBreathing = 13,
        Invisibility = 14,
        Blindness = 15,
        NightVision = 16,
        Hunger = 17,
        Weakness = 18,
        Poison = 19,
        Wither = 20,
        HealthBoost = 21,
        Absorption = 22,
        Saturation = 23,
        Glowing = 24,
        Levitation = 25,
        Luck = 26,
        Unluck = 27,
#if PROTOCOL_VERSION > 340 // 1.13
        SlowFalling = 28,
        ConduitPower = 29,
        DolphinsGrace = 30,
#endif
#if PROTOCOL_VERSION > 404 //1.14
        BadOmen = 31,
        HeroOfTheVillage = 32,
#endif
#if PROTOCOL_VERSION > 758 // 1.19
        Darkness = 33,
#endif
    };
} // Botcraft

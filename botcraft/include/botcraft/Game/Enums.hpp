#pragma once
#include <unordered_map>

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

    enum class PlayerDiggingFace
    {
        Bottom = 0, // -Y
        Top,        // +Y
        North,      // -Z
        South,      // +Z
        West,       // -X
        East        // +X
    };

    // Types are detailed in registries, see https://wiki.vg/Inventory

    enum class InventoryType
    {
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

    enum class EntityType
    {
        Entity = 0,
        Player,
        LocalPlayer
    };
} // Botcraft
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

// Use map instead of unordered to avoid another include everywhere
#include <map>
#include <memory>
#include <string_view>

namespace ProtocolCraft
{
    namespace Components
    {
        enum class DataComponentTypes
        {
            None = -1,
            CustomData,
            MaxStackSize,
            MaxDamage,
            Damage,
            Unbreakable,
            CustomName,
            ItemName,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            ItemModel,
#endif
            Lore,
            Rarity,
            Enchantments,
            CanPlaceOn,
            CanBreak,
            AttributeModifiers,
            CustomModelData,
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            HideAdditionalTooltip,
            HideTooltip,
#else
            TooltipDisplay,
#endif
            RepairCost,
            CreativeSlotLock,
            EnchantmentGlintOverride,
            IntangibleProjectile,
            Food,
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            FireResistant,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            Consumable,
            UseRemainder,
            UseCooldown,
            DamageResistant,
#endif
            Tool,
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            Weapon,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            Enchantable,
            Equippable,
            Repairable,
            Glider,
            TooltipStyle,
            DeathProtection,
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            BlocksAttacks,
#endif
            StoredEnchantments,
            DyedColor,
            MapColor,
            MapId,
            MapDecorations,
            MapPostProcessing,
            ChargedProjectiles,
            BundleContents,
            PotionContents,
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            PotionDurationScale,
#endif
            SuspiciousStewEffects,
            WritableBookContent,
            WrittenBookContent,
            Trim,
            DebugStickState,
            EntityData,
            BucketEntityData,
            BlockEntityData,
            Instrument,
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            ProvidesTrimMaterial,
#endif
            OminousBottleAmplifier,
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
            JukeboxPlayable,
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            ProvidesBannerPatterns,
#endif
            Recipes,
            LodestoneTracker,
            FireworkExplosion,
            Fireworks,
            Profile,
            NoteBlockSound,
            BannerPatterns,
            BaseColor,
            PotDecorations,
            Container,
            BlockState,
            Bees,
            Lock,
            ContainerLoot,
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            BreakSound,
            Villager_Variant,
            Wolf_Variant,
            Wolf_SoundVariant,
            Wolf_Collar,
            Fox_Variant,
            Salmon_Size,
            Parrot_Variant,
            TropicalFish_Pattern,
            TropicalFish_BaseColor,
            TropicalFish_PatternColor,
            Mooshroom_Variant,
            Rabbit_Variant,
            Pig_Variant,
            Cow_Variant,
            Chicken_Variant,
            Frog_Variant,
            Horse_Variant,
            Painting_Variant,
            Llama_Variant,
            Axolotl_Variant,
            Cat_Variant,
            Cat_Collar,
            Sheep_Color,
            Shulker_Color,
#endif
            NUM_DATA_COMPONENT_TYPES
        };

        std::string_view DataComponentTypesToString(const DataComponentTypes type);

        class DataComponentType;

        class DataComponentPredicate : public NetworkType
        {
        public:
            virtual ~DataComponentPredicate() override;

            const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& GetMap() const;
            DataComponentPredicate& SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            std::map<DataComponentTypes, std::shared_ptr<DataComponentType>> map;

        };

        class DataComponentPatch : public NetworkType
        {
        public:
            virtual ~DataComponentPatch() override;

            const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& GetMap() const;
            DataComponentPatch& SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            std::map<DataComponentTypes, std::shared_ptr<DataComponentType>> map;

        };

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        class HashedDataComponentPatch : public NetworkType
        {
        public:
            HashedDataComponentPatch() = default;
            HashedDataComponentPatch(const DataComponentPatch& patch);

            SERIALIZED_FIELD(AddedComponents, Internal::DiffType<std::map<DataComponentTypes, int>, std::map<VarInt, int>>);
            SERIALIZED_FIELD(RemovedComponents, Internal::DiffType<std::vector<DataComponentTypes>, std::vector<VarInt>>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
#endif
    }
}
#endif

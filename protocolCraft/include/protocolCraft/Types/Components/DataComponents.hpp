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
            Lore,
            Rarity,
            Enchantments,
            CanPlaceOn,
            CanBreak,
            AttributeModifiers,
            CustomModelData,
            HideAdditionalTooltip,
            HideTooltip,
            RepairCost,
            CreativeSlotLock,
            EnchantmentGlintOverride,
            IntangibleProjectile,
            Food,
            FireResistant,
            Tool,
            StoredEnchantments,
            DyedColor,
            MapColor,
            MapId,
            MapDecorations,
            MapPostProcessing,
            ChargedProjectiles,
            BundleContents,
            PotionContents,
            SuspiciousStewEffects,
            WritableBookContent,
            WrittenBookContent,
            Trim,
            DebugStickState,
            EntityData,
            BucketEntityData,
            BlockEntityData,
            Instrument,
            OminousBottleAmplifier,
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
            JukeboxPlayable,
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
            NUM_DATA_COMPONENT_TYPES
        };

        std::string_view DataComponentTypesToString(const DataComponentTypes type);

        class DataComponentType;

        class DataComponentPredicate : public NetworkType
        {
        public:
            virtual ~DataComponentPredicate() override;

            const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& GetMap() const;
            void SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_);

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
            void SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            std::map<DataComponentTypes, std::shared_ptr<DataComponentType>> map;

        };
    }
}
#endif

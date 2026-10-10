#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponents.hpp"
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include "protocolCraft/Types/Components/DataComponentTypeAdventureModePredicate.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeArmorTrim.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBannerPatternLayers.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBlockItemStateProperties.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBoolean.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBundleContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeChargedProjectiles.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeComponent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomData.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomModelData.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDefault.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyeColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyedItemColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworkExplosion.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworks.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFoodProperties.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeInstrument.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeInteger.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemAttributeModifiers.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemContainerContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemEnchantments.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemLore.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeListBeehiveBlockEntityOccupant.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeLodestoneTracker.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapId.hpp"
#if PROTOCOL_VERSION < 777 /* < 26.3 */
#include "protocolCraft/Types/Components/DataComponentTypeMapItemColor.hpp"
#endif
#include "protocolCraft/Types/Components/DataComponentTypeMapPostProcessing.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePotDecorations.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePotionContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeRarity.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeResolvableProfile.hpp"
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
#include "protocolCraft/Types/Components/DataComponentTypeResourceLocation.hpp"
#endif
#include "protocolCraft/Types/Components/DataComponentTypeSuspiciousStewEffects.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeTool.hpp"
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#include "protocolCraft/Types/Components/DataComponentTypeUnbreakable.hpp"
#endif
#include "protocolCraft/Types/Components/DataComponentTypeUnit.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWritableBookContent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWrittenBookContent.hpp"
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Types/Components/DataComponentTypeJukeboxPlayable.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Components/DataComponentTypeConsumable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDamageResistant.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDeathProtection.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeEquippable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeRepairable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUseCooldown.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUseRemainder.hpp"
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "protocolCraft/Types/Components/DataComponentTypeBlocksAttacks.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBreakSound.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeEitherRegistryVarint.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFloat.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePaintingVariant.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeProvidesBannerPattern.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeProvidesTrimMaterial.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeTooltipDisplay.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeVariantEnum.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWeapon.hpp"
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Components/DataComponentTypeTypedEntityData.hpp"
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "protocolCraft/Types/Components/DataComponentTypeAttackRange.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeIdentifier.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeKineticWeapon.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePiercingWeapon.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeSwingAnimation.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUseEffects.hpp"
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "protocolCraft/Types/Components/DataComponentTypeSulfurCubeContent.hpp"
#endif
#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include "protocolCraft/Types/Components/DataComponentTypeBrewingFuel.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCompostable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCookingFuel.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMobVisibility.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeSignText.hpp"
#endif

#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include <stdexcept>

namespace ProtocolCraft
{
    namespace Components
    {
        DEFINE_NETWORK_TYPE(ExactMatcher);
        DEFINE_NETWORK_TYPE(RangedMatcher);
        DEFINE_NETWORK_TYPE(AttributeModifier);
        DEFINE_NETWORK_TYPE(BannerPattern);
        DEFINE_NETWORK_TYPE(BannerPatternLayer);
        DEFINE_NETWORK_TYPE(BeehiveBlockEntityOccupant);
        DEFINE_NETWORK_TYPE(BlockPredicate);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        DEFINE_NETWORK_TYPE(DamageReduction);
        DEFINE_NETWORK_TYPE(DataComponentMatchers);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        DEFINE_NETWORK_TYPE(Instrument);
#endif
        DEFINE_NETWORK_TYPE(ItemAttributeModifiersEntry);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        DEFINE_NETWORK_TYPE(ItemDamageFunction);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        DEFINE_NETWORK_TYPE(JukeboxSong);
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        DEFINE_NETWORK_TYPE(KineticWeaponCondition);
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */ && PROTOCOL_VERSION < 777 /* < 26.3 */
        DEFINE_NETWORK_TYPE(AssetInfo);
        DEFINE_NETWORK_TYPE(MaterialAssetGroup);
#endif
        DEFINE_NETWORK_TYPE(MobEffectInstance);
        DEFINE_NETWORK_TYPE(MobEffectInstanceDetails);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        DEFINE_NETWORK_TYPE(PaintingVariant);
        DEFINE_NETWORK_TYPE(PartialDataComponentPredicate);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        DEFINE_NETWORK_TYPE(PartialResolvableProfile);
        DEFINE_NETWORK_TYPE(PlayerSkinPatch);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        DEFINE_NETWORK_TYPE(PossibleEffect);
#endif
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        DEFINE_NETWORK_TYPE(ResolvableFloat);
        DEFINE_NETWORK_TYPE(ResolvableInt);
#endif
        DEFINE_NETWORK_TYPE(StatePropertiesPredicate);
        DEFINE_NETWORK_TYPE(SuspiciousStewEntry);
        DEFINE_NETWORK_TYPE(ToolRule);
        DEFINE_NETWORK_TYPE(PropertyMatcher);
        DEFINE_NETWORK_TYPE(TrimMaterial);
        DEFINE_NETWORK_TYPE(TrimPattern);

        DEFINE_NETWORK_TYPE(DataComponentTypeAdventureModePredicate);
        DEFINE_NETWORK_TYPE(DataComponentTypeArmorTrim);
        DEFINE_NETWORK_TYPE(DataComponentTypeBannerPatternLayers);
        DEFINE_NETWORK_TYPE(DataComponentTypeBlockItemStateProperties);
        DEFINE_NETWORK_TYPE(DataComponentTypeBoolean);
        DEFINE_NETWORK_TYPE(DataComponentTypeBundleContents);
        DEFINE_NETWORK_TYPE(DataComponentTypeChargedProjectiles);
        DEFINE_NETWORK_TYPE(DataComponentTypeComponent);
        DEFINE_NETWORK_TYPE(DataComponentTypeCustomData);
        DEFINE_NETWORK_TYPE(DataComponentTypeCustomModelData);
        DEFINE_NETWORK_TYPE(DataComponentTypeDefault);
        DEFINE_NETWORK_TYPE(DataComponentTypeDyeColor);
        DEFINE_NETWORK_TYPE(DataComponentTypeDyedItemColor);
        DEFINE_NETWORK_TYPE(DataComponentTypeFireworkExplosion);
        DEFINE_NETWORK_TYPE(DataComponentTypeFireworks);
        DEFINE_NETWORK_TYPE(DataComponentTypeFoodProperties);
        DEFINE_NETWORK_TYPE(DataComponentTypeInstrument);
        DEFINE_NETWORK_TYPE(DataComponentTypeInteger);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemAttributeModifiers);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemContainerContents);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemEnchantments);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemLore);
        DEFINE_NETWORK_TYPE(DataComponentTypeListBeehiveBlockEntityOccupant);
        DEFINE_NETWORK_TYPE(DataComponentTypeLodestoneTracker);
        DEFINE_NETWORK_TYPE(DataComponentTypeMapId);
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        DEFINE_NETWORK_TYPE(DataComponentTypeMapItemColor);
#endif
        DEFINE_NETWORK_TYPE(DataComponentTypeMapPostProcessing);
        DEFINE_NETWORK_TYPE(DataComponentTypePotDecorations);
        DEFINE_NETWORK_TYPE(DataComponentTypePotionContents);
        DEFINE_NETWORK_TYPE(DataComponentTypeRarity);
        DEFINE_NETWORK_TYPE(DataComponentTypeResolvableProfile);
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        DEFINE_NETWORK_TYPE(DataComponentTypeResourceLocation);
#endif
        DEFINE_NETWORK_TYPE(DataComponentTypeSuspiciousStewEffects);
        DEFINE_NETWORK_TYPE(DataComponentTypeTool);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        DEFINE_NETWORK_TYPE(DataComponentTypeUnbreakable);
#endif
        DEFINE_NETWORK_TYPE(DataComponentTypeUnit);
        DEFINE_NETWORK_TYPE(DataComponentTypeWritableBookContent);
        DEFINE_NETWORK_TYPE(DataComponentTypeWrittenBookContent);
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        DEFINE_NETWORK_TYPE(DataComponentTypeJukeboxPlayable);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        DEFINE_NETWORK_TYPE(DataComponentTypeConsumable);
        DEFINE_NETWORK_TYPE(DataComponentTypeDamageResistant);
        DEFINE_NETWORK_TYPE(DataComponentTypeDeathProtection);
        DEFINE_NETWORK_TYPE(DataComponentTypeEquippable);
        DEFINE_NETWORK_TYPE(DataComponentTypeRepairable);
        DEFINE_NETWORK_TYPE(DataComponentTypeUseCooldown);
        DEFINE_NETWORK_TYPE(DataComponentTypeUseRemainder);
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        DEFINE_NETWORK_TYPE(DataComponentTypeBlocksAttacks);
        DEFINE_NETWORK_TYPE(DataComponentTypeBreakSound);
        DEFINE_NETWORK_TYPE(DataComponentTypeEitherRegistryVarint);
        DEFINE_NETWORK_TYPE(DataComponentTypeFloat);
        DEFINE_NETWORK_TYPE(DataComponentTypePaintingVariant);
        DEFINE_NETWORK_TYPE(DataComponentTypeProvidesBannerPattern);
        DEFINE_NETWORK_TYPE(DataComponentTypeProvidesTrimMaterial);
        DEFINE_NETWORK_TYPE(DataComponentTypeTooltipDisplay);
        DEFINE_NETWORK_TYPE(DataComponentTypeVariantEnum);
        DEFINE_NETWORK_TYPE(DataComponentTypeWeapon);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        DEFINE_NETWORK_TYPE(DataComponentTypeTypedEntityData);
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        DEFINE_NETWORK_TYPE(DataComponentTypeAttackRange);
        DEFINE_NETWORK_TYPE(DataComponentTypeIdentifier);
        DEFINE_NETWORK_TYPE(DataComponentTypeKineticWeapon);
        DEFINE_NETWORK_TYPE(DataComponentTypePiercingWeapon);
        DEFINE_NETWORK_TYPE(DataComponentTypeSwingAnimation);
        DEFINE_NETWORK_TYPE(DataComponentTypeUseEffects);
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
        DEFINE_NETWORK_TYPE(DataComponentTypeSulfurCubeContent);
#endif
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        DEFINE_NETWORK_TYPE(DataComponentTypeBrewingFuel);
        DEFINE_NETWORK_TYPE(DataComponentTypeCompostable);
        DEFINE_NETWORK_TYPE(DataComponentTypeCookingFuel);
        DEFINE_NETWORK_TYPE(DataComponentTypeMobVisibility);
        DEFINE_NETWORK_TYPE(DataComponentTypeSignText);
#endif

        std::shared_ptr<DataComponentType> CreateComponentType(const DataComponentTypes type)
        {
            if (type <= DataComponentTypes::None || type >= DataComponentTypes::NUM_DATA_COMPONENT_TYPES)
            {
                throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
            }

            switch (type)
            {
            case DataComponentTypes::CanPlaceOn:
            case DataComponentTypes::CanBreak:
                return std::make_shared<DataComponentTypeAdventureModePredicate>();
            case DataComponentTypes::Trim:
                return std::make_shared<DataComponentTypeArmorTrim>();
            case DataComponentTypes::BannerPatterns:
                return std::make_shared<DataComponentTypeBannerPatternLayers>();
            case DataComponentTypes::BlockState:
                return std::make_shared<DataComponentTypeBlockItemStateProperties>();
            case DataComponentTypes::EnchantmentGlintOverride:
                return std::make_shared<DataComponentTypeBoolean>();
            case DataComponentTypes::BundleContents:
                return std::make_shared<DataComponentTypeBundleContents>();
            case DataComponentTypes::ChargedProjectiles:
                return std::make_shared<DataComponentTypeChargedProjectiles>();
            case DataComponentTypes::CustomName:
            case DataComponentTypes::ItemName:
                return std::make_shared<DataComponentTypeComponent>();
            case DataComponentTypes::BucketEntityData:
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
            case DataComponentTypes::BlockEntityData:
            case DataComponentTypes::EntityData:
#endif
                return std::make_shared<DataComponentTypeCustomData>();
            case DataComponentTypes::CustomModelData:
                return std::make_shared<DataComponentTypeCustomModelData>();
            case DataComponentTypes::CustomData:
            case DataComponentTypes::IntangibleProjectile:
            case DataComponentTypes::MapDecorations:
            case DataComponentTypes::DebugStickState:
            case DataComponentTypes::Recipes:
            case DataComponentTypes::Lock:
            case DataComponentTypes::ContainerLoot:
                // Component with no network serializer specified fallback to NBT
                return std::make_shared<DataComponentTypeDefault>();
            case DataComponentTypes::BaseColor:
                return std::make_shared<DataComponentTypeDyeColor>();
            case DataComponentTypes::DyedColor:
                return std::make_shared<DataComponentTypeDyedItemColor>();
            case DataComponentTypes::FireworkExplosion:
                return std::make_shared<DataComponentTypeFireworkExplosion>();
            case DataComponentTypes::Fireworks:
                return std::make_shared<DataComponentTypeFireworks>();
            case DataComponentTypes::Food:
                return std::make_shared<DataComponentTypeFoodProperties>();
            case DataComponentTypes::Instrument:
                return std::make_shared<DataComponentTypeInstrument>();
            case DataComponentTypes::MaxStackSize:
            case DataComponentTypes::MaxDamage:
            case DataComponentTypes::Damage:
            case DataComponentTypes::RepairCost:
            case DataComponentTypes::OminousBottleAmplifier:
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::Enchantable:
#endif
                return std::make_shared<DataComponentTypeInteger>();
            case DataComponentTypes::AttributeModifiers:
                return std::make_shared<DataComponentTypeItemAttributeModifiers>();
            case DataComponentTypes::Container:
                return std::make_shared<DataComponentTypeItemContainerContents>();
            case DataComponentTypes::Enchantments:
            case DataComponentTypes::StoredEnchantments:
                return std::make_shared<DataComponentTypeItemEnchantments>();
            case DataComponentTypes::Lore:
                return std::make_shared<DataComponentTypeItemLore>();
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
            case DataComponentTypes::JukeboxPlayable:
                return std::make_shared<DataComponentTypeJukeboxPlayable>();
#endif
            case DataComponentTypes::Bees:
                return std::make_shared<DataComponentTypeListBeehiveBlockEntityOccupant>();
            case DataComponentTypes::LodestoneTracker:
                return std::make_shared<DataComponentTypeLodestoneTracker>();
            case DataComponentTypes::MapId:
                return std::make_shared<DataComponentTypeMapId>();
#if PROTOCOL_VERSION < 777 /* < 26.3 */
            case DataComponentTypes::MapColor:
                return std::make_shared<DataComponentTypeMapItemColor>();
#endif
            case DataComponentTypes::MapPostProcessing:
                return std::make_shared<DataComponentTypeMapPostProcessing>();
            case DataComponentTypes::PotDecorations:
                return std::make_shared<DataComponentTypePotDecorations>();
            case DataComponentTypes::PotionContents:
                return std::make_shared<DataComponentTypePotionContents>();
            case DataComponentTypes::Rarity:
                return std::make_shared<DataComponentTypeRarity>();
            case DataComponentTypes::Profile:
                return std::make_shared<DataComponentTypeResolvableProfile>();
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::DamageResistant:
                return std::make_shared<DataComponentTypeDamageResistant>();
            case DataComponentTypes::ItemModel:
            case DataComponentTypes::TooltipStyle:
#endif
            case DataComponentTypes::NoteBlockSound:
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
                return std::make_shared<DataComponentTypeResourceLocation>();
#else
                return std::make_shared<DataComponentTypeIdentifier>();
#endif
            case DataComponentTypes::SuspiciousStewEffects:
                return std::make_shared<DataComponentTypeSuspiciousStewEffects>();
            case DataComponentTypes::Tool:
                return std::make_shared<DataComponentTypeTool>();
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            case DataComponentTypes::Unbreakable:
                return std::make_shared<DataComponentTypeUnbreakable>();
#else
            // From custom Unbreakable to Unit in 1.21.5
            case DataComponentTypes::Unbreakable:
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            case DataComponentTypes::HideAdditionalTooltip:
            case DataComponentTypes::HideTooltip:
#endif
            case DataComponentTypes::CreativeSlotLock:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            case DataComponentTypes::FireResistant:
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::Glider:
#endif
                return std::make_shared<DataComponentTypeUnit>();
            case DataComponentTypes::WritableBookContent:
                return std::make_shared<DataComponentTypeWritableBookContent>();
            case DataComponentTypes::WrittenBookContent:
                return std::make_shared<DataComponentTypeWrittenBookContent>();
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::Consumable:
                return std::make_shared<DataComponentTypeConsumable>();
            case DataComponentTypes::DeathProtection:
                return std::make_shared<DataComponentTypeDeathProtection>();
            case DataComponentTypes::Equippable:
                return std::make_shared<DataComponentTypeEquippable>();
            case DataComponentTypes::Repairable:
                return std::make_shared<DataComponentTypeRepairable>();
            case DataComponentTypes::UseCooldown:
                return std::make_shared<DataComponentTypeUseCooldown>();
            case DataComponentTypes::UseRemainder:
                return std::make_shared<DataComponentTypeUseRemainder>();
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            case DataComponentTypes::BlocksAttacks:
                return std::make_shared<DataComponentTypeBlocksAttacks>();
            case DataComponentTypes::BreakSound:
                return std::make_shared<DataComponentTypeBreakSound>();
            case DataComponentTypes::Painting_Variant:
                return std::make_shared<DataComponentTypePaintingVariant>();
            case DataComponentTypes::PotionDurationScale:
                return std::make_shared<DataComponentTypeFloat>();
            case DataComponentTypes::ProvidesBannerPatterns:
                return std::make_shared<DataComponentTypeProvidesBannerPattern>();
            case DataComponentTypes::ProvidesTrimMaterial:
                return std::make_shared<DataComponentTypeProvidesTrimMaterial>();
            case DataComponentTypes::TooltipDisplay:
                return std::make_shared<DataComponentTypeTooltipDisplay>();
            case DataComponentTypes::Weapon:
                return std::make_shared<DataComponentTypeWeapon>();
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            case DataComponentTypes::Chicken_Variant:
                return std::make_shared<DataComponentTypeEitherRegistryVarint>();
#endif
            case DataComponentTypes::Axolotl_Variant:
            case DataComponentTypes::Cat_Variant:
            case DataComponentTypes::Cow_Variant:
            case DataComponentTypes::Fox_Variant:
            case DataComponentTypes::Frog_Variant:
            case DataComponentTypes::Horse_Variant:
            case DataComponentTypes::Llama_Variant:
            case DataComponentTypes::Mooshroom_Variant:
            case DataComponentTypes::Parrot_Variant:
            case DataComponentTypes::Pig_Variant:
            case DataComponentTypes::Rabbit_Variant:
            case DataComponentTypes::Salmon_Size:
            case DataComponentTypes::TropicalFish_Pattern:
            case DataComponentTypes::Villager_Variant:
            case DataComponentTypes::Wolf_SoundVariant:
            case DataComponentTypes::Wolf_Variant:
                return std::make_shared<DataComponentTypeVariantEnum>();
            case DataComponentTypes::Cat_Collar:
            case DataComponentTypes::TropicalFish_BaseColor:
            case DataComponentTypes::TropicalFish_PatternColor:
            case DataComponentTypes::Sheep_Color:
            case DataComponentTypes::Shulker_Color:
            case DataComponentTypes::Wolf_Collar:
                return std::make_shared<DataComponentTypeDyeColor>();
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
            case DataComponentTypes::BlockEntityData:
            case DataComponentTypes::EntityData:
                return std::make_shared<DataComponentTypeTypedEntityData>();
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
            case DataComponentTypes::UseEffects:
                return std::make_shared<DataComponentTypeUseEffects>();
            case DataComponentTypes::MinimumAttackCharge:
                return std::make_shared<DataComponentTypeFloat>();
            case DataComponentTypes::AttackRange:
                return std::make_shared<DataComponentTypeAttackRange>();
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            case DataComponentTypes::DamageType:
            case DataComponentTypes::ZombieNautilus_Variant:
                return std::make_shared<DataComponentTypeEitherRegistryVarint>();
#endif
            case DataComponentTypes::PiercingWeapon:
                return std::make_shared<DataComponentTypePiercingWeapon>();
            case DataComponentTypes::KineticWeapon:
                return std::make_shared<DataComponentTypeKineticWeapon>();
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */ && PROTOCOL_VERSION < 777 /* < 26.3 */
            case DataComponentTypes::SwingAnimation:
                return std::make_shared<DataComponentTypeSwingAnimation>();
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
            case DataComponentTypes::Dye:
                return std::make_shared<DataComponentTypeDyeColor>();
            case DataComponentTypes::Chicken_Variant:
            case DataComponentTypes::DamageType:
            case DataComponentTypes::ZombieNautilus_Variant:
            case DataComponentTypes::Cat_SoundVariant:
            case DataComponentTypes::Chicken_SoundVariant:
            case DataComponentTypes::Cow_SoundVariant:
            case DataComponentTypes::Pig_SoundVariant:
                return std::make_shared<DataComponentTypeVariantEnum>();
            case DataComponentTypes::AdditionalTradeCost:
                return std::make_shared<DataComponentTypeInteger>();
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
            case DataComponentTypes::SulfurCubeContent:
                return std::make_shared<DataComponentTypeSulfurCubeContent>();
#endif
#if PROTOCOL_VERSION > 776 /* > 26.2 */
            case DataComponentTypes::AttackAnimation:
            case DataComponentTypes::InteractAnimation:
                return std::make_shared<DataComponentTypeSwingAnimation>();
            case DataComponentTypes::BrewingFuel:
                return std::make_shared<DataComponentTypeBrewingFuel>();
            case DataComponentTypes::Compostable:
                return std::make_shared<DataComponentTypeCompostable>();
            case DataComponentTypes::CookingFuel:
                return std::make_shared<DataComponentTypeCookingFuel>();
            case DataComponentTypes::BlockTransformer:
            case DataComponentTypes::ProvidesPotteryPattern:
                return std::make_shared<DataComponentTypeVariantEnum>();
            case DataComponentTypes::MobVisibility:
                return std::make_shared<DataComponentTypeMobVisibility>();
            case DataComponentTypes::SignTextBack:
            case DataComponentTypes::SignTextFront:
                return std::make_shared<DataComponentTypeSignText>();
            case DataComponentTypes::VillagerFood:
                return std::make_shared<DataComponentTypeVariantEnum>();
            case DataComponentTypes::Waxed:
                return std::make_shared<DataComponentTypeUnit>();
            case DataComponentTypes::CushionColor:
                return std::make_shared<DataComponentTypeDyeColor>();
#endif
            default:
                // Should never happen but will make the compilers happy
                throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)));
                return nullptr;
            }

            return nullptr;
        }

        DataComponentPredicate::~DataComponentPredicate()
        {

        }

        const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& DataComponentPredicate::GetMap() const
        {
            return map;
        }

        DataComponentPredicate& DataComponentPredicate::SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_)
        {
            map = map_;
            return *this;
        }

        void DataComponentPredicate::ReadImpl(ReadIterator& iter, size_t& length)
        {
            // special case, dynamic factory
            const int map_size = ReadData<VarInt>(iter, length);
            map.clear();
            for (int i = 0; i < map_size; ++i)
            {
                const DataComponentTypes k = ReadData<DataComponentTypes, VarInt>(iter, length);
                std::shared_ptr<DataComponentType> v = CreateComponentType(k);
                if (v != nullptr)
                {
                    v->Read(iter, length);
                }
                map[k] = v;
            }
        }

        void DataComponentPredicate::WriteImpl(WriteContainer& container) const
        {
            // special case, dynamic factory
            WriteData<VarInt>(static_cast<int>(map.size()), container);
            for (const auto& [k, v] : map)
            {
                WriteData<DataComponentTypes, VarInt>(k, container);
                if (v != nullptr)
                {
                    v->Write(container);
                }
            }
        }

        Json::Value DataComponentPredicate::SerializeImpl() const
        {
            Json::Value output;

            output["map"] = Json::Array();
            for (const auto& p : map)
            {
                output["map"].push_back({
                    { "type", p.first },
                    { "data", p.second == nullptr ? nullptr : p.second->Serialize() }
                });
            }

            return output;
        }

        template<bool LengthPrefixed>
        const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& BasicDataComponentPatch<LengthPrefixed>::GetMap() const
        {
            return map;
        }

        template<bool LengthPrefixed>
        BasicDataComponentPatch<LengthPrefixed>& BasicDataComponentPatch<LengthPrefixed>::SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_)
        {
            map = map_;
            return *this;
        }

        template<bool LengthPrefixed>
        void BasicDataComponentPatch<LengthPrefixed>::ReadImpl(ReadIterator& iter, size_t& length)
        {
            const int num_data = ReadData<VarInt>(iter, length);
            const int num_void = ReadData<VarInt>(iter, length);

            map.clear();

            for (int i = 0; i < num_data; ++i)
            {
                const DataComponentTypes type = ReadData<DataComponentTypes, VarInt>(iter, length);
                int data_size = 0;
                if constexpr (LengthPrefixed)
                {
                   data_size = ReadData<VarInt>(iter, length);
                }
                std::shared_ptr<DataComponentType> data = CreateComponentType(type);
                const size_t pre_data_length = length;

                if (data != nullptr)
                {
                    data->Read(iter, length);
                    if constexpr (LengthPrefixed)
                    {
                        if (pre_data_length - length != data_size)
                        {
                            throw std::runtime_error("Wrong data size when reading length prefixed component");
                        }
                    }
                }
                map.insert({ type, data });
            }

            for (int i = 0; i < num_void; ++i)
            {
                const DataComponentTypes type = ReadData<DataComponentTypes, VarInt>(iter, length);
                map.insert({ type, nullptr });
            }
        }

        template<bool LengthPrefixed>
        void BasicDataComponentPatch<LengthPrefixed>::WriteImpl(WriteContainer& container) const
        {
            int num_data = 0;
            for (const auto& p : map)
            {
                num_data += p.second != nullptr;
            }
            const int num_void = static_cast<int>(map.size()) - num_data;

            WriteData<VarInt>(num_data, container);
            WriteData<VarInt>(num_void, container);

            for (const auto& p : map)
            {
                if (p.second == nullptr)
                {
                    continue;
                }

                WriteData<DataComponentTypes, VarInt>(p.first, container);
                if constexpr (LengthPrefixed)
                {
                    WriteContainer temp;
                    p.second->Write(temp);
                    WriteData<VarInt>(static_cast<int>(temp.size()), container);
                    WriteByteArray(temp, container);
                }
                else
                {
                    p.second->Write(container);
                }
            }

            for (const auto& p : map)
            {
                if (p.second != nullptr)
                {
                    continue;
                }
                WriteData<DataComponentTypes, VarInt>(p.first, container);
            }
        }

        template<bool LengthPrefixed>
        Json::Value BasicDataComponentPatch<LengthPrefixed>::SerializeImpl() const
        {
            Json::Value output;

            output["map"] = Json::Array();
            for (const auto& p : map)
            {
                output["map"].push_back({
                    { "type", p.first },
                    { "data", p.second == nullptr ? nullptr : p.second->Serialize() }
                });
            }

            return output;
        }

        template class BasicDataComponentPatch<false>;

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        template class BasicDataComponentPatch<true>;

        HashedDataComponentPatch::HashedDataComponentPatch(const DataComponentPatch& patch)
        {
            for (const auto& [k, v] : patch.GetMap())
            {
                if (v == nullptr)
                {
                    RemovedComponents.push_back(k);
                }
                else
                {
                    // TODO: Fix this, this is *NOT* how the components are serialized to bytes
                    std::vector<unsigned char> serialized;
                    WriteData<DataComponentTypes, VarInt>(k, serialized);
                    v->Write(serialized);
                    // This however should be the right CRC32C hash calculation
                    // CRC32c polynomial, from https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Polynomial_representations
                    // no idea why we need the reversed one but it works
                    constexpr unsigned int polynomial = 0x82F63B78;

                    unsigned int crc = 0xFFFFFFFF;

                    for (const auto byte : serialized)
                    {
                        crc ^= byte;
                        // TODO: replace slow loop with a faster version with lookup table and cool fancy stuff ?
                        for (int i = 0; i < 8; ++i)
                        {
                            // Trick to replace if branch
                            // if (crc & 1) crc = (crc >> 1) ^ polynomial;
                            // else crc = crc >> 1;
                            // Works because a ^ 0 == a
                            crc = (crc >> 1) ^ (crc & 1) * polynomial;
                        }
                    }
                    AddedComponents[k] = static_cast<int>(~crc);
                }
            }
        }

        DEFINE_NETWORK_TYPE(HashedDataComponentPatch);
#endif
    }
}
#endif

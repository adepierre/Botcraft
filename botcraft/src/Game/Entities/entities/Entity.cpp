#include "botcraft/Game/Entities/entities/Entity.hpp"

#include <iostream>

#include "protocolCraft/Types/Slot.hpp"
#include "protocolCraft/Types/Chat.hpp"
#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "botcraft/Game/Entities/VillagerData.hpp"

#include "botcraft/Game/Entities/entities/AreaEffectCloudEntity.hpp"
#include "botcraft/Game/Entities/entities/decoration/ArmorStandEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/ArrowEntity.hpp"
#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/animal/axolotl/AxolotlEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/ambient/BatEntity.hpp"
#if PROTOCOL_VERSION > 498
#include "botcraft/Game/Entities/entities/animal/BeeEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/BlazeEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/BoatEntity.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/CatEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/CaveSpiderEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/ChickenEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/CodEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/CowEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/CreeperEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/DolphinEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/horse/DonkeyEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/DragonFireballEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/monster/DrownedEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/ElderGuardianEntity.hpp"
#include "botcraft/Game/Entities/entities/boss/enderdragon/EndCrystalEntity.hpp"
#include "botcraft/Game/Entities/entities/boss/enderdragon/EnderDragonEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/EnderManEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/EndermiteEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/EvokerEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/EvokerFangsEntity.hpp"
#include "botcraft/Game/Entities/entities/ExperienceOrbEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/EyeOfEnderEntity.hpp"
#include "botcraft/Game/Entities/entities/item/FallingBlockEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/FireworkRocketEntity.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/FoxEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/GhastEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/GiantEntity.hpp"
#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/decoration/GlowItemFrameEntity.hpp"
#include "botcraft/Game/Entities/entities/GlowSquidEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/goat/GoatEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/GuardianEntity.hpp"
#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/hoglin/HoglinEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/horse/HorseEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/HuskEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/IllusionerEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/IronGolemEntity.hpp"
#include "botcraft/Game/Entities/entities/item/ItemEntity.hpp"
#include "botcraft/Game/Entities/entities/decoration/ItemFrameEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/LargeFireballEntity.hpp"
#include "botcraft/Game/Entities/entities/decoration/LeashFenceKnotEntity.hpp"
#include "botcraft/Game/Entities/entities/LightningBoltEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/horse/LlamaEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/LlamaSpitEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/MagmaCubeEntity.hpp"
#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/MarkerEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/vehicle/MinecartEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/MinecartChestEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/MinecartCommandBlockEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/MinecartFurnaceEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/MinecartHopperEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/MinecartSpawnerEntity.hpp"
#include "botcraft/Game/Entities/entities/vehicle/MinecartTNTEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/horse/MuleEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/MushroomCowEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/OcelotEntity.hpp"
#include "botcraft/Game/Entities/entities/decoration/PaintingEntity.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/PandaEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/ParrotEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/monster/PhantomEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/PigEntity.hpp"
#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/PigZombieEntity.hpp"
#endif
#if PROTOCOL_VERSION > 736
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinBruteEntity.hpp"
#endif
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/monster/PillagerEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/PolarBearEntity.hpp"
#include "botcraft/Game/Entities/entities/item/PrimedTntEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/PufferfishEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/RabbitEntity.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/monster/RavagerEntity.hpp"
#endif
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/SalmonEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/animal/SheepEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/ShulkerEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/ShulkerBulletEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/SilverfishEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/SkeletonEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/horse/SkeletonHorseEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/SlimeEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/SmallFireballEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/SnowGolemEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/SnowballEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/SpectralArrowEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/SpiderEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/SquidEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/StrayEntity.hpp"
#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/StriderEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/projectile/ThrownEggEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/ThrownEnderpearlEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/ThrownExperienceBottleEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/ThrownPotionEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/projectile/ThrownTridentEntity.hpp"
#endif
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/horse/TraderLlamaEntity.hpp"
#endif

#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/TropicalFishEntity.hpp"
#endif
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/TurtleEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/VexEntity.hpp"
#include "botcraft/Game/Entities/entities/npc/VillagerEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/VindicatorEntity.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/npc/WanderingTraderEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/WitchEntity.hpp"
#include "botcraft/Game/Entities/entities/boss/wither/WitherBossEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/WitherSkeletonEntity.hpp"
#include "botcraft/Game/Entities/entities/projectile/WitherSkullEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/WolfEntity.hpp"
#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/ZoglinEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/monster/ZombieEntity.hpp"
#include "botcraft/Game/Entities/entities/animal/horse/ZombieHorseEntity.hpp"
#include "botcraft/Game/Entities/entities/monster/ZombieVillagerEntity.hpp"
#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/ZombifiedPiglinEntity.hpp"
#endif
#include "botcraft/Game/Entities/entities/player/PlayerEntity.hpp"
#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/projectile/FishingHookEntity.hpp"
#endif

namespace Botcraft
{
    const std::array<std::string, Entity::metadata_count> Entity::metadata_names{ {
        "data_shared_flags_id",
        "data_air_supply_id",
        "data_custom_name",
        "data_custom_name_visible",
        "data_silent",
        "data_no_gravity",
#if PROTOCOL_VERSION > 404
        "data_pose",
#endif
#if PROTOCOL_VERSION > 754
        "data_ticks_frozen",
#endif
    } };

    Entity::Entity()
    {
        // Initialize base stuff
        entity_id = 0;
        position = Vector3<double>(0.0, 0.0, 0.0);
        yaw = 0.0f;
        pitch = 0.0f;
        speed = Vector3<double>(0.0, 0.0, 0.0);
        on_ground = false;
        equipments = {
            { EquipmentSlot::MainHand, ProtocolCraft::Slot() },
            { EquipmentSlot::OffHand, ProtocolCraft::Slot() },
            { EquipmentSlot::Boots, ProtocolCraft::Slot() },
            { EquipmentSlot::Leggings, ProtocolCraft::Slot() },
            { EquipmentSlot::ChestPlate, ProtocolCraft::Slot() },
            { EquipmentSlot::Helmet, ProtocolCraft::Slot() }
        };

        // Initialize all metadata with default values
        SetDataSharedFlagsId(0);
        SetDataAirSupplyId(300);
#if PROTOCOL_VERSION > 340
        SetDataCustomName(std::optional<ProtocolCraft::Chat>());
#else
        SetDataCustomName("");
#endif
        SetDataCustomNameVisible(false);
        SetDataSilent(false);
        SetDataNoGravity(false);
#if PROTOCOL_VERSION > 404
        SetDataPose(Pose::Standing);
#endif
#if PROTOCOL_VERSION > 754
        SetDataTicksFrozen(0);
#endif
    }

    Entity::~Entity()
    {

    }


    void Entity::LoadMetadataFromRawArray(const std::vector<unsigned char>& data)
    {
        if (data.size() == 0)
        {
            return;
        }

        ProtocolCraft::ReadIterator iter = data.begin();
        size_t length = data.size();

        while (true)
        {
            const unsigned char index = ProtocolCraft::ReadData<unsigned char>(iter, length);
            if (index == 0xFF)
            {
                break;
            }

            const int type = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length);
            std::any value;

            switch (type)
            {
            case 0:
                value = ProtocolCraft::ReadData<char>(iter, length);
                break;
            case 1:
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
            case 2:
                value = ProtocolCraft::ReadData<float>(iter, length);
                break;
            case 3:
                value = ProtocolCraft::ReadData<std::string>(iter, length);
                break;
            case 4:
                value = ProtocolCraft::Chat();
                std::any_cast<ProtocolCraft::Chat&>(value).Read(iter, length);
                break;
#if PROTOCOL_VERSION > 340
            case 5:
                if (ProtocolCraft::ReadData<bool>(iter, length))
                {
                    value = std::optional<ProtocolCraft::Chat>(ProtocolCraft::Chat());
                    std::any_cast<std::optional<ProtocolCraft::Chat>&>(value).value().Read(iter, length);
                }
                else
                {
                    value = std::optional<ProtocolCraft::Chat>();
                }
                break;
#endif
#if PROTOCOL_VERSION > 340
            case 6:
#else
            case 5:
#endif
                value = ProtocolCraft::Slot();
                std::any_cast<ProtocolCraft::Slot&>(value).Read(iter, length);
                break;
#if PROTOCOL_VERSION > 340
            case 7:
#else
            case 6:
#endif
                value = ProtocolCraft::ReadData<bool>(iter, length);
                break;
#if PROTOCOL_VERSION > 340
            case 8:
#else
            case 7:
#endif
            {
                std::vector<float> rotation = ProtocolCraft::ReadArrayData<float>(iter, length, 3);
                value = Vector3<float>(rotation[0], rotation[1], rotation[2]);
                break;
            }
#if PROTOCOL_VERSION > 340
            case 9:
#else
            case 8:
#endif
            {
                ProtocolCraft::NetworkPosition position;
                position.Read(iter, length);
                value = Position(position);
                break;
            }
#if PROTOCOL_VERSION > 340
            case 10:
#else
            case 9:
#endif
                if (ProtocolCraft::ReadData<bool>(iter, length))
                {
                    ProtocolCraft::NetworkPosition position;
                    position.Read(iter, length);
                    value = std::optional<Position>(position);
                }
                else
                {
                    value = std::optional<Position>();
                }
                break;
#if PROTOCOL_VERSION > 340
            case 11:
#else
            case 10:
#endif
                value = static_cast<Direction>(static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length)));
                break;
#if PROTOCOL_VERSION > 340
            case 12:
#else
            case 11:
#endif
                if (ProtocolCraft::ReadData<bool>(iter, length))
                {
                    value = std::optional<ProtocolCraft::UUID>(ProtocolCraft::ReadData<ProtocolCraft::UUID>(iter, length));
                }
                else
                {
                    value = std::optional<ProtocolCraft::UUID>();
                }
                break;
#if PROTOCOL_VERSION > 340
            case 13:
#else
            case 12:
#endif
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
#if PROTOCOL_VERSION > 340
            case 14:
#else
            case 13:
#endif
                value = ProtocolCraft::NBT();
                std::any_cast<ProtocolCraft::NBT&>(value).Read(iter, length);
                break;
#if PROTOCOL_VERSION > 340
            case 15:
                value = ProtocolCraft::Particle::CreateParticle(static_cast<ProtocolCraft::ParticleType>(static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length))));
                std::any_cast<std::shared_ptr<ProtocolCraft::Particle>&>(value)->Read(iter, length);
                break;
#endif
#if PROTOCOL_VERSION > 404
            case 16:
                value = VillagerData{
                    ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length), // villager_type
                    ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length), // villager_profession
                    ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length) // level
                };
                break;
            case 17:
            {
                const int val = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length);
                value = val > 0 ? std::optional<int>(val - 1) : std::optional<int>();
                break;
            }
            case 18:
                value = static_cast<Pose>(static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length)));
                break;
#endif
            default:
                std::cerr << "WARNING, unknown type in entity metadata: " << type << ". Stopping metadata parsing." << std::endl;
                return;
            }
            SetMetadataValue(index, value);
        }
    }

    void Entity::SetMetadataValue(const int index, const std::any& value)
    {
        assert(index >= 0 && index < metadata_count);
        metadata[metadata_names[index]] = value;
    }


    char Entity::GetDataSharedFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_shared_flags_id"));
    }

    int Entity::GetDataAirSupplyId() const
    {
        return std::any_cast<int>(metadata.at("data_air_supply_id"));
    }

#if PROTOCOL_VERSION > 340
    const std::optional<ProtocolCraft::Chat>& Entity::GetDataCustomName() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::Chat>&>(metadata.at("data_custom_name"));
    }
#else
    const std::string& Entity::GetDataCustomName() const
    {
        return std::any_cast<const std::string&>(metadata.at("data_custom_name"));
    }
#endif

    bool Entity::GetDataCustomNameVisible() const
    {
        return std::any_cast<bool>(metadata.at("data_custom_name_visible"));
    }

    bool Entity::GetDataSilent() const
    {
        return std::any_cast<bool>(metadata.at("data_silent"));
    }

    bool Entity::GetDataNoGravity() const
    {
        return std::any_cast<bool>(metadata.at("data_no_gravity"));
    }

#if PROTOCOL_VERSION > 404
    Pose Entity::GetDataPose() const
    {
        return std::any_cast<Pose>(metadata.at("data_pose"));
    }
#endif

#if PROTOCOL_VERSION > 754
    int Entity::GetDataTicksFrozen() const
    {
        return std::any_cast<int>(metadata.at("data_ticks_frozen"));
    }
#endif


    void Entity::SetDataSharedFlagsId(const char data_shared_flags_id)
    {
        metadata["data_shared_flags_id"] = data_shared_flags_id;
    }

    void Entity::SetDataAirSupplyId(const int data_air_supply_id)
    {
        metadata["data_air_supply_id"] = data_air_supply_id;
    }

#if PROTOCOL_VERSION > 340
    void Entity::SetDataCustomName(const std::optional<ProtocolCraft::Chat>& data_custom_name)
    {
        metadata["data_custom_name"] = data_custom_name;
    }
#else
    void Entity::SetDataCustomName(const std::string& data_custom_name)
    {
        metadata["data_custom_name"] = data_custom_name;
    }
#endif

    void Entity::SetDataCustomNameVisible(const bool data_custom_name_visible)
    {
        metadata["data_custom_name_visible"] = data_custom_name_visible;
    }

    void Entity::SetDataSilent(const bool data_silent)
    {
        metadata["data_silent"] = data_silent;
    }

    void Entity::SetDataNoGravity(const bool data_no_gravity)
    {
        metadata["data_no_gravity"] = data_no_gravity;
    }

#if PROTOCOL_VERSION > 404
    void Entity::SetDataPose(const Pose data_pose)
    {
        metadata["data_pose"] = data_pose;
    }
#endif

#if PROTOCOL_VERSION > 754
    void Entity::SetDataTicksFrozen(const int data_ticks_frozen)
    {
        metadata["data_ticks_frozen"] = data_ticks_frozen;
    }
#endif


    int Entity::GetEntityID() const
    {
        return entity_id;
    }

    const Vector3<double>& Entity::GetPosition() const
    {
        return position;
    }

    double Entity::GetX() const
    {
        return position.x;
    }

    double Entity::GetY() const
    {
        return position.y;
    }

    double Entity::GetZ() const
    {
        return position.z;
    }

    float Entity::GetYaw() const
    {
        return yaw;
    }

    float Entity::GetPitch() const
    {
        return pitch;
    }

    const Vector3<double>& Entity::GetSpeed() const
    {
        return speed;
    }

    double Entity::GetSpeedX() const
    {
        return speed.x;
    }

    double Entity::GetSpeedY() const
    {
        return speed.y;
    }

    double Entity::GetSpeedZ() const
    {
        return speed.z;
    }

    bool Entity::GetOnGround() const
    {
        return on_ground;
    }

    const std::map<EquipmentSlot, ProtocolCraft::Slot>& Entity::GetEquipments() const
    {
        return equipments;
    }

    const ProtocolCraft::Slot& Entity::GetEquipment(const EquipmentSlot slot) const
    {
        return equipments.at(slot);
    }


    void Entity::SetEntityID(const int entity_id_)
    {
        entity_id = entity_id_;
    }

    void Entity::SetPosition(const Vector3<double>& position_)
    {
        position = position_;
    }

    void Entity::SetX(const double x_)
    {
        position.x = x_;
    }

    void Entity::SetY(const double y_)
    {
        position.y = y_;
    }

    void Entity::SetZ(const double z_)
    {
        position.z = z_;
    }

    void Entity::SetYaw(const float yaw_)
    {
        yaw = yaw_;
    }

    void Entity::SetPitch(const float pitch_)
    {
        pitch = pitch_;
    }

    void Entity::SetSpeed(const Vector3<double>& speed_)
    {
        speed = speed_;
    }

    void Entity::SetSpeedX(const double speed_x_)
    {
        speed.x = speed_x_;
    }

    void Entity::SetSpeedY(const double speed_y_)
    {
        speed.y = speed_y_;
    }

    void Entity::SetSpeedZ(const double speed_z_)
    {
        speed.z = speed_z_;
    }

    void Entity::SetOnGround(const bool on_ground_)
    {
        on_ground = on_ground_;
    }

    void Entity::SetEquipment(const EquipmentSlot slot, const ProtocolCraft::Slot& item)
    {
        equipments.at(slot) = item;
    }


    nlohmann::json Entity::Serialize() const
    {
        nlohmann::json output;

        output["data_shared_flags_id"] = GetDataSharedFlagsId();
        output["data_air_supply_id"] = GetDataAirSupplyId();
#if PROTOCOL_VERSION > 340
        output["data_custom_name"] = GetDataCustomName() ? GetDataCustomName().value().Serialize() : nullptr;
#else
        output["data_custom_name"] = GetDataCustomName();
#endif
        output["data_custom_name_visible"] = GetDataCustomNameVisible();
        output["data_silent"] = GetDataSilent();
        output["data_no_gravity"] = GetDataNoGravity();
#if PROTOCOL_VERSION > 404
        output["data_pose"] = static_cast<int>(GetDataPose());
#endif
#if PROTOCOL_VERSION > 754
        output["data_ticks_frozen"] = GetDataTicksFrozen();
#endif

        return output;
    }


    bool Entity::IsLivingEntity() const
    {
        return false;
    }

    bool Entity::IsAbstractArrow() const
    {
        return false;
    }

    bool Entity::IsAnimal() const
    {
        return false;
    }

    bool Entity::IsAmbientCreature() const
    {
        return false;
    }

    bool Entity::IsMonster() const
    {
        return false;
    }

    bool Entity::IsTamableAnimal() const
    {
        return false;
    }

    bool Entity::IsAbstractSchoolingFish() const
    {
        return false;
    }

    bool Entity::IsWaterAnimal() const
    {
        return false;
    }

    bool Entity::IsAbstractChestedHorse() const
    {
        return false;
    }

    bool Entity::IsAbstractHurtingProjectile() const
    {
        return false;
    }

    bool Entity::IsMob() const
    {
        return false;
    }

    bool Entity::IsSpellcasterIllager() const
    {
        return false;
    }

#if PROTOCOL_VERSION > 578
    bool Entity::IsProjectile() const
    {
        return false;
    }
#endif

    bool Entity::IsFlyingMob() const
    {
        return false;
    }

    bool Entity::IsAbstractHorse() const
    {
        return false;
    }

    bool Entity::IsAbstractGolem() const
    {
        return false;
    }

    bool Entity::IsHangingEntity() const
    {
        return false;
    }

    bool Entity::IsFireball() const
    {
        return false;
    }

    bool Entity::IsAbstractMinecart() const
    {
        return false;
    }

    bool Entity::IsAbstractMinecartContainer() const
    {
        return false;
    }

    bool Entity::IsShoulderRidingEntity() const
    {
        return false;
    }

#if PROTOCOL_VERSION > 736
    bool Entity::IsAbstractPiglin() const
    {
        return false;
    }
#endif

    bool Entity::IsAbstractIllager() const
    {
        return false;
    }

    bool Entity::IsAbstractFish() const
    {
        return false;
    }

#if PROTOCOL_VERSION > 404
    bool Entity::IsRaider() const
    {
        return false;
    }
#endif

    bool Entity::IsAbstractSkeleton() const
    {
        return false;
    }

    bool Entity::IsThrowableItemProjectile() const
    {
        return false;
    }

#if PROTOCOL_VERSION > 477
    bool Entity::IsAbstractVillager() const
    {
        return false;
    }
#endif

    bool Entity::IsAgeableMob() const
    {
        return false;
    }

    bool Entity::IsPathfinderMob() const
    {
        return false;
    }

#if PROTOCOL_VERSION > 404
    bool Entity::IsPatrollingMonster() const
    {
        return false;
    }
#endif

    bool Entity::IsThrowableProjectile() const
    {
        return false;
    }


    std::shared_ptr<Entity> Entity::CreateEntity(const EntityType type)
    {
        switch (type)
        {
        case EntityType::None:
            return nullptr;
        case EntityType::AreaEffectCloud:
            return std::make_shared<AreaEffectCloudEntity>();
        case EntityType::ArmorStand:
            return std::make_shared<ArmorStandEntity>();
        case EntityType::Arrow:
            return std::make_shared<ArrowEntity>();
#if PROTOCOL_VERSION > 754
        case EntityType::Axolotl:
            return std::make_shared<AxolotlEntity>();
#endif
        case EntityType::Bat:
            return std::make_shared<BatEntity>();
#if PROTOCOL_VERSION > 498
        case EntityType::Bee:
            return std::make_shared<BeeEntity>();
#endif
        case EntityType::Blaze:
            return std::make_shared<BlazeEntity>();
        case EntityType::Boat:
            return std::make_shared<BoatEntity>();
#if PROTOCOL_VERSION > 404
        case EntityType::Cat:
            return std::make_shared<CatEntity>();
#endif
        case EntityType::CaveSpider:
            return std::make_shared<CaveSpiderEntity>();
        case EntityType::Chicken:
            return std::make_shared<ChickenEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::Cod:
            return std::make_shared<CodEntity>();
#endif
        case EntityType::Cow:
            return std::make_shared<CowEntity>();
        case EntityType::Creeper:
            return std::make_shared<CreeperEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::Dolphin:
            return std::make_shared<DolphinEntity>();
#endif
        case EntityType::Donkey:
            return std::make_shared<DonkeyEntity>();
        case EntityType::DragonFireball:
            return std::make_shared<DragonFireballEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::Drowned:
            return std::make_shared<DrownedEntity>();
#endif
        case EntityType::ElderGuardian:
            return std::make_shared<ElderGuardianEntity>();
        case EntityType::EndCrystal:
            return std::make_shared<EndCrystalEntity>();
        case EntityType::EnderDragon:
            return std::make_shared<EnderDragonEntity>();
        case EntityType::EnderMan:
            return std::make_shared<EnderManEntity>();
        case EntityType::Endermite:
            return std::make_shared<EndermiteEntity>();
        case EntityType::Evoker:
            return std::make_shared<EvokerEntity>();
        case EntityType::EvokerFangs:
            return std::make_shared<EvokerFangsEntity>();
        case EntityType::ExperienceOrb:
            return std::make_shared<ExperienceOrbEntity>();
        case EntityType::EyeOfEnder:
            return std::make_shared<EyeOfEnderEntity>();
        case EntityType::FallingBlockEntity:
            return std::make_shared<FallingBlockEntity>();
        case EntityType::FireworkRocketEntity:
            return std::make_shared<FireworkRocketEntity>();
#if PROTOCOL_VERSION > 404
        case EntityType::Fox:
            return std::make_shared<FoxEntity>();
#endif
        case EntityType::Ghast:
            return std::make_shared<GhastEntity>();
        case EntityType::Giant:
            return std::make_shared<GiantEntity>();
#if PROTOCOL_VERSION > 754
        case EntityType::GlowItemFrame:
            return std::make_shared<GlowItemFrameEntity>();
        case EntityType::GlowSquid:
            return std::make_shared<GlowSquidEntity>();
        case EntityType::Goat:
            return std::make_shared<GoatEntity>();
#endif
        case EntityType::Guardian:
            return std::make_shared<GuardianEntity>();
#if PROTOCOL_VERSION > 578
        case EntityType::Hoglin:
            return std::make_shared<HoglinEntity>();
#endif
        case EntityType::Horse:
            return std::make_shared<HorseEntity>();
        case EntityType::Husk:
            return std::make_shared<HuskEntity>();
        case EntityType::Illusioner:
            return std::make_shared<IllusionerEntity>();
        case EntityType::IronGolem:
            return std::make_shared<IronGolemEntity>();
        case EntityType::ItemEntity:
            return std::make_shared<ItemEntity>();
        case EntityType::ItemFrame:
            return std::make_shared<ItemFrameEntity>();
        case EntityType::LargeFireball:
            return std::make_shared<LargeFireballEntity>();
        case EntityType::LeashFenceKnotEntity:
            return std::make_shared<LeashFenceKnotEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::LightningBolt:
            return std::make_shared<LightningBoltEntity>();
#endif
        case EntityType::Llama:
            return std::make_shared<LlamaEntity>();
        case EntityType::LlamaSpit:
            return std::make_shared<LlamaSpitEntity>();
        case EntityType::MagmaCube:
            return std::make_shared<MagmaCubeEntity>();
#if PROTOCOL_VERSION > 754
        case EntityType::Marker:
            return std::make_shared<MarkerEntity>();
#endif
        case EntityType::Minecart:
            return std::make_shared<MinecartEntity>();
        case EntityType::MinecartChest:
            return std::make_shared<MinecartChestEntity>();
        case EntityType::MinecartCommandBlock:
            return std::make_shared<MinecartCommandBlockEntity>();
        case EntityType::MinecartFurnace:
            return std::make_shared<MinecartFurnaceEntity>();
        case EntityType::MinecartHopper:
            return std::make_shared<MinecartHopperEntity>();
        case EntityType::MinecartSpawner:
            return std::make_shared<MinecartSpawnerEntity>();
        case EntityType::MinecartTNT:
            return std::make_shared<MinecartTNTEntity>();
        case EntityType::Mule:
            return std::make_shared<MuleEntity>();
        case EntityType::MushroomCow:
            return std::make_shared<MushroomCowEntity>();
        case EntityType::Ocelot:
            return std::make_shared<OcelotEntity>();
        case EntityType::Painting:
            return std::make_shared<PaintingEntity>();
#if PROTOCOL_VERSION > 404
        case EntityType::Panda:
            return std::make_shared<PandaEntity>();
#endif
        case EntityType::Parrot:
            return std::make_shared<ParrotEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::Phantom:
            return std::make_shared<PhantomEntity>();
#endif
        case EntityType::Pig:
            return std::make_shared<PigEntity>();
#if PROTOCOL_VERSION > 578
        case EntityType::Piglin:
            return std::make_shared<PiglinEntity>();
#endif
#if PROTOCOL_VERSION > 736
        case EntityType::PiglinBrute:
            return std::make_shared<PiglinBruteEntity>();
#endif
#if PROTOCOL_VERSION > 404
        case EntityType::Pillager:
            return std::make_shared<PillagerEntity>();
#endif
        case EntityType::PolarBear:
            return std::make_shared<PolarBearEntity>();
        case EntityType::PrimedTnt:
            return std::make_shared<PrimedTntEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::Pufferfish:
            return std::make_shared<PufferfishEntity>();
#endif
        case EntityType::Rabbit:
            return std::make_shared<RabbitEntity>();
#if PROTOCOL_VERSION > 404
        case EntityType::Ravager:
            return std::make_shared<RavagerEntity>();
#endif
#if PROTOCOL_VERSION > 340
        case EntityType::Salmon:
            return std::make_shared<SalmonEntity>();
#endif
        case EntityType::Sheep:
            return std::make_shared<SheepEntity>();
        case EntityType::Shulker:
            return std::make_shared<ShulkerEntity>();
        case EntityType::ShulkerBullet:
            return std::make_shared<ShulkerBulletEntity>();
        case EntityType::Silverfish:
            return std::make_shared<SilverfishEntity>();
        case EntityType::Skeleton:
            return std::make_shared<SkeletonEntity>();
        case EntityType::SkeletonHorse:
            return std::make_shared<SkeletonHorseEntity>();
        case EntityType::Slime:
            return std::make_shared<SlimeEntity>();
        case EntityType::SmallFireball:
            return std::make_shared<SmallFireballEntity>();
        case EntityType::SnowGolem:
            return std::make_shared<SnowGolemEntity>();
        case EntityType::Snowball:
            return std::make_shared<SnowballEntity>();
        case EntityType::SpectralArrow:
            return std::make_shared<SpectralArrowEntity>();
        case EntityType::Spider:
            return std::make_shared<SpiderEntity>();
        case EntityType::Squid:
            return std::make_shared<SquidEntity>();
        case EntityType::Stray:
            return std::make_shared<StrayEntity>();
#if PROTOCOL_VERSION > 578
        case EntityType::Strider:
            return std::make_shared<StriderEntity>();
#endif
        case EntityType::ThrownEgg:
            return std::make_shared<ThrownEggEntity>();
        case EntityType::ThrownEnderpearl:
            return std::make_shared<ThrownEnderpearlEntity>();
        case EntityType::ThrownExperienceBottle:
            return std::make_shared<ThrownExperienceBottleEntity>();
        case EntityType::ThrownPotion:
            return std::make_shared<ThrownPotionEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::ThrownTrident:
            return std::make_shared<ThrownTridentEntity>();
#endif
#if PROTOCOL_VERSION > 404
        case EntityType::TraderLlama:
            return std::make_shared<TraderLlamaEntity>();
#endif
#if PROTOCOL_VERSION > 340
        case EntityType::TropicalFish:
            return std::make_shared<TropicalFishEntity>();
#endif
#if PROTOCOL_VERSION > 340
        case EntityType::Turtle:
            return std::make_shared<TurtleEntity>();
#endif
        case EntityType::Vex:
            return std::make_shared<VexEntity>();
        case EntityType::Villager:
            return std::make_shared<VillagerEntity>();
        case EntityType::Vindicator:
            return std::make_shared<VindicatorEntity>();
#if PROTOCOL_VERSION > 404
        case EntityType::WanderingTrader:
            return std::make_shared<WanderingTraderEntity>();
#endif
        case EntityType::Witch:
            return std::make_shared<WitchEntity>();
        case EntityType::WitherBoss:
            return std::make_shared<WitherBossEntity>();
        case EntityType::WitherSkeleton:
            return std::make_shared<WitherSkeletonEntity>();
        case EntityType::WitherSkull:
            return std::make_shared<WitherSkullEntity>();
        case EntityType::Wolf:
            return std::make_shared<WolfEntity>();
#if PROTOCOL_VERSION > 578
        case EntityType::Zoglin:
            return std::make_shared<ZoglinEntity>();
#endif
        case EntityType::Zombie:
            return std::make_shared<ZombieEntity>();
        case EntityType::ZombieHorse:
            return std::make_shared<ZombieHorseEntity>();
        case EntityType::ZombieVillager:
            return std::make_shared<ZombieVillagerEntity>();
#if PROTOCOL_VERSION > 578
        case EntityType::ZombifiedPiglin:
            return std::make_shared<ZombifiedPiglinEntity>();
#else
        case EntityType::PigZombie:
            return std::make_shared<PigZombieEntity>();
#endif
        case EntityType::Player:
            return std::make_shared<PlayerEntity>();
#if PROTOCOL_VERSION > 340
        case EntityType::FishingHook:
            return std::make_shared<FishingHookEntity>();
#endif
        default:
            return nullptr;
        }
    }
}

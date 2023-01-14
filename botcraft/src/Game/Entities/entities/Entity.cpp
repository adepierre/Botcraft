#include "botcraft/Game/Entities/entities/Entity.hpp"

#include "protocolCraft/Types/Slot.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/VillagerData.hpp"
#endif
#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/GlobalPos.hpp"
#endif

#if USE_GUI
#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Renderer/Atlas.hpp"
#endif
#include "botcraft/Utilities/Logger.hpp"

#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/allay/AllayEntity.hpp"
#endif
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
#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/vehicle/ChestBoatEntity.hpp"
#endif
#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/CatEntity.hpp"
#endif
#if PROTOCOL_VERSION > 760
#include "botcraft/Game/Entities/entities/animal/camel/CamelEntity.hpp"
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
#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/frog/FrogEntity.hpp"
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
#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/frog/TadpoleEntity.hpp"
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
#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/monster/warden/WardenEntity.hpp"
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
#include "botcraft/Game/Entities/entities/projectile/FishingHookEntity.hpp"

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


    AABB Entity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2, position.z), Vector3<double>(GetWidth() / 2, GetHeight() / 2, GetWidth() / 2));
    }

    double Entity::GetWidth() const
    {
        return -1.0;
    }

    double Entity::GetHeight() const
    {
        return -1.0;
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

            enum EntityMetadataTypes
            {
                Char = 0,
                Int,
#if PROTOCOL_VERSION > 760
                Long,
#endif
                Float,
                String,
                Chat,
#if PROTOCOL_VERSION > 340
                OptionalChat,
#endif
                Slot,
                Bool,
                Rotations,
                BlockPosition,
                OptionalBlockPosition,
                DirectionType,
                OptionalUUID,
                BlockstateType,
                NBT,
#if PROTOCOL_VERSION > 340
                Particle,
#endif
#if PROTOCOL_VERSION > 404
                VillagerDataTYpe,
                OptionalUint,
                PoseType,
#endif
#if PROTOCOL_VERSION > 758
                CatVariant,
                FrogVariant,
                OptionalGlobalPos,
                PaintingVariant,
#endif
            };

            switch (type)
            {
            case EntityMetadataTypes::Char:
                value = ProtocolCraft::ReadData<char>(iter, length);
                break;
            case EntityMetadataTypes::Int:
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
#if PROTOCOL_VERSION > 760
            case EntityMetadataTypes::Long:
                value = static_cast<long long int>(ProtocolCraft::ReadData<ProtocolCraft::VarLong>(iter, length));
                break;
#endif
            case EntityMetadataTypes::Float:
                value = ProtocolCraft::ReadData<float>(iter, length);
                break;
            case EntityMetadataTypes::String:
                value = ProtocolCraft::ReadData<std::string>(iter, length);
                break;
            case EntityMetadataTypes::Chat:
                value = ProtocolCraft::Chat();
                std::any_cast<ProtocolCraft::Chat&>(value).Read(iter, length);
                break;
#if PROTOCOL_VERSION > 340
            case EntityMetadataTypes::OptionalChat:
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
            case EntityMetadataTypes::Slot:
                value = ProtocolCraft::Slot();
                std::any_cast<ProtocolCraft::Slot&>(value).Read(iter, length);
                break;
            case EntityMetadataTypes::Bool:
                value = ProtocolCraft::ReadData<bool>(iter, length);
                break;
            case EntityMetadataTypes::Rotations:
            {
                Vector3<float> rotation;
                for (int i = 0; i < 3; ++i)
                {
                    rotation[i] = ProtocolCraft::ReadData<float>(iter, length);
                }
                value = rotation;
                break;
            }
            case EntityMetadataTypes::BlockPosition:
            {
                ProtocolCraft::NetworkPosition position;
                position.Read(iter, length);
                value = Position(position);
                break;
            }
            case EntityMetadataTypes::OptionalBlockPosition:
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
            case EntityMetadataTypes::DirectionType:
                value = static_cast<Direction>(static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length)));
                break;
            case EntityMetadataTypes::OptionalUUID:
                if (ProtocolCraft::ReadData<bool>(iter, length))
                {
                    value = std::optional<ProtocolCraft::UUID>(ProtocolCraft::ReadData<ProtocolCraft::UUID>(iter, length));
                }
                else
                {
                    value = std::optional<ProtocolCraft::UUID>();
                }
                break;
            case EntityMetadataTypes::BlockstateType:
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
            case EntityMetadataTypes::NBT:
                value = ProtocolCraft::NBT::Value();
                std::any_cast<ProtocolCraft::NBT::Value&>(value).Read(iter, length);
                break;
#if PROTOCOL_VERSION > 340
            case EntityMetadataTypes::Particle:
                value = ProtocolCraft::Particle::CreateParticle(static_cast<ProtocolCraft::ParticleType>(static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length))));
                std::any_cast<std::shared_ptr<ProtocolCraft::Particle>&>(value)->Read(iter, length);
                break;
#endif
#if PROTOCOL_VERSION > 404
            case EntityMetadataTypes::VillagerDataTYpe:
                value = VillagerData{
                    ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length), // villager_type
                    ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length), // villager_profession
                    ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length) // level
                };
                break;
            case EntityMetadataTypes::OptionalUint:
            {
                const int val = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length);
                value = val > 0 ? std::optional<int>(val - 1) : std::optional<int>();
                break;
            }
            case EntityMetadataTypes::PoseType:
                value = static_cast<Pose>(static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length)));
                break;
#endif
#if PROTOCOL_VERSION > 758
            case EntityMetadataTypes::CatVariant:
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
            case EntityMetadataTypes::FrogVariant:
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
            case EntityMetadataTypes::OptionalGlobalPos:
                if (ProtocolCraft::ReadData<bool>(iter, length))
                {
                    ProtocolCraft::Identifier dimension;
                    dimension.Read(iter, length);
                    ProtocolCraft::NetworkPosition pos;
                    pos.Read(iter, length);
                    
                    value = std::optional<GlobalPos>({
                            dimension,
                            pos
                        });
                }
                else
                {
                    value = std::optional<GlobalPos>();
                }
                break;
            case EntityMetadataTypes::PaintingVariant:
                value = static_cast<int>(ProtocolCraft::ReadData<ProtocolCraft::VarInt>(iter, length));
                break;
#endif
            default:
                LOG_ERROR("Unknown type in entity metadata : " << type << ".Stopping current metadata parsing.");
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

    const std::vector<EntityEffect>& Entity::GetEffects() const
    {
        return effects;
    }

#if USE_GUI
    const std::vector<Renderer::Face>& Entity::GetFaces()
    {
        if (faces.size() == 0)
        {
            InitializeFaces();
        }
        if (!are_rendered_faces_up_to_date)
        {
            for (size_t i = 0; i < faces.size(); ++i)
            {
                faces[i].UpdateMatrix(face_descriptors[i].transformations, face_descriptors[i].orientation);
            }
        }
        return faces;
    }

    bool Entity::GetAreRenderedFacesUpToDate() const
    {
        return are_rendered_faces_up_to_date;
    }
#endif


    void Entity::SetEntityID(const int entity_id_)
    {
        entity_id = entity_id_;
    }

    void Entity::SetPosition(const Vector3<double>& position_)
    {
#if USE_GUI
        if (position_ != position)
        {
            are_rendered_faces_up_to_date = false;
            for (size_t i = 0; i < faces.size(); ++i)
            {
                std::shared_ptr<Renderer::Translation> f = std::static_pointer_cast<Renderer::Translation>(face_descriptors[i].transformations.translations.back());
                f->x = static_cast<float>(position_.x);
                f->y = static_cast<float>(position_.y);
                f->z = static_cast<float>(position_.z);
            }
        }
#endif
        position = position_;
    }

    void Entity::SetX(const double x_)
    {
#if USE_GUI
        if (x_ != position.x)
        {
            are_rendered_faces_up_to_date = false;
            for (size_t i = 0; i < faces.size(); ++i)
            {
                std::static_pointer_cast<Renderer::Translation>(face_descriptors[i].transformations.translations.back())->x = static_cast<float>(x_);
            }
        }
#endif
        position.x = x_;
    }

    void Entity::SetY(const double y_)
    {
#if USE_GUI
        if (y_ != position.y)
        {
            are_rendered_faces_up_to_date = false;
            for (size_t i = 0; i < faces.size(); ++i)
            {
                std::static_pointer_cast<Renderer::Translation>(face_descriptors[i].transformations.translations.back())->y = static_cast<float>(y_);
            }
        }
#endif
        position.y = y_;
    }

    void Entity::SetZ(const double z_)
    {
#if USE_GUI
        if (z_ != position.z)
        {
            are_rendered_faces_up_to_date = false;
            for (size_t i = 0; i < faces.size(); ++i)
            {
                std::static_pointer_cast<Renderer::Translation>(face_descriptors[i].transformations.translations.back())->z = static_cast<float>(z_);
            }
        }
#endif
        position.z = z_;
    }

    void Entity::SetYaw(const float yaw_)
    {
#if USE_GUI
        if (yaw_ != yaw)
        {
            are_rendered_faces_up_to_date = false;
            for (size_t i = 0; i < faces.size(); ++i)
            {
                std::static_pointer_cast<Renderer::Rotation>(face_descriptors[i].transformations.rotations.front())->deg_angle = yaw_;
            }
        }
#endif
        yaw = yaw_;
    }

    void Entity::SetPitch(const float pitch_)
    {
#if USE_GUI
        if (pitch_ != pitch)
        {
            are_rendered_faces_up_to_date = false;
            for (size_t i = 0; i < faces.size(); ++i)
            {
                std::static_pointer_cast<Renderer::Rotation>(face_descriptors[i].transformations.rotations.back())->deg_angle = pitch_; 
            }
        }
#endif
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

    void Entity::SetEffects(const std::vector<EntityEffect>& effects_)
    {
        effects = effects_;
    }

    void Entity::RemoveEffect(const EntityEffectType type)
    {
        for (auto it = effects.begin(); it != effects.end();)
        {
            if (it->type == type)
            {
                it = effects.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void Entity::AddEffect(const EntityEffect& effect)
    {
        // First, remove any instance of this type of effect on the entity
        RemoveEffect(effect.type);

        // Then add the new one
        effects.push_back(effect);
    }

#if USE_GUI
    void Entity::SetAreRenderedFacesUpToDate(const bool should_be_updated_)
    {
        are_rendered_faces_up_to_date = should_be_updated_;
    }
#endif


    ProtocolCraft::Json::Value Entity::Serialize() const
    {
        ProtocolCraft::Json::Value output;

        output["id"] = entity_id;
        output["position"] = position.Serialize();
        output["yaw"] = yaw;
        output["pitch"] = pitch;
        output["speed"] = speed.Serialize();
        output["on_ground"] = on_ground;
        output["equipment"] = ProtocolCraft::Json::Value();
        for (auto& p : equipments)
        {
            output["equipment"][std::to_string(static_cast<int>(p.first))] = p.second.Serialize();
        }

        output["metadata"] = ProtocolCraft::Json::Value();

        output["metadata"]["data_shared_flags_id"] = GetDataSharedFlagsId();
        output["metadata"]["data_air_supply_id"] = GetDataAirSupplyId();
#if PROTOCOL_VERSION > 340
        output["metadata"]["data_custom_name"] = GetDataCustomName() ? GetDataCustomName().value().Serialize() : ProtocolCraft::Json::Value();
#else
        output["metadata"]["data_custom_name"] = GetDataCustomName();
#endif
        output["metadata"]["data_custom_name_visible"] = GetDataCustomNameVisible();
        output["metadata"]["data_silent"] = GetDataSilent();
        output["metadata"]["data_no_gravity"] = GetDataNoGravity();
#if PROTOCOL_VERSION > 404
        output["metadata"]["data_pose"] = static_cast<int>(GetDataPose());
#endif
#if PROTOCOL_VERSION > 754
        output["metadata"]["data_ticks_frozen"] = GetDataTicksFrozen();
#endif

        return output;
    }

    bool Entity::IsLocalPlayer() const
    {
        return false;
    }

    bool Entity::IsRemotePlayer() const
    {
        return false;
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
#if PROTOCOL_VERSION > 758
        case EntityType::Allay:
            return std::make_shared<AllayEntity>();
#endif
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
#if PROTOCOL_VERSION > 758
        case EntityType::ChestBoat:
            return std::make_shared<ChestBoatEntity>();
#endif
#if PROTOCOL_VERSION > 404
        case EntityType::Cat:
            return std::make_shared<CatEntity>();
#endif
#if PROTOCOL_VERSION > 760
        case EntityType::Camel:
            return std::make_shared<CamelEntity>();
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
#if PROTOCOL_VERSION > 758
        case EntityType::Frog:
            return std::make_shared<FrogEntity>();
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
#if PROTOCOL_VERSION > 758
        case EntityType::Tadpole:
            return std::make_shared<TadpoleEntity>();
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
#if PROTOCOL_VERSION > 758
        case EntityType::Warden:
            return std::make_shared<WardenEntity>();
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

#if PROTOCOL_VERSION < 458
    std::shared_ptr<Entity> Entity::CreateObjectEntity(const ObjectEntityType type)
    {
        switch (type)
        {
        case ObjectEntityType::None:
            return nullptr;
        case ObjectEntityType::Boat:
            return std::make_shared<BoatEntity>();
        case ObjectEntityType::ItemEntity:
            return std::make_shared<ItemEntity>();
        case ObjectEntityType::AreaEffectCloud:
            return std::make_shared<AreaEffectCloudEntity>();
        case ObjectEntityType::PrimedTnt:
            return std::make_shared<PrimedTntEntity>();
        case ObjectEntityType::EndCrystal:
            return std::make_shared<EndCrystalEntity>();
        case ObjectEntityType::Arrow:
            return std::make_shared<ArrowEntity>();
        case ObjectEntityType::Snowball:
            return std::make_shared<SnowballEntity>();
        case ObjectEntityType::ThrownEgg:
            return std::make_shared<ThrownEggEntity>();
        case ObjectEntityType::LargeFireball:
            return std::make_shared<LargeFireballEntity>();
        case ObjectEntityType::SmallFireball:
            return std::make_shared<SmallFireballEntity>();
        case ObjectEntityType::ThrownEnderpearl:
            return std::make_shared<ThrownEnderpearlEntity>();
        case ObjectEntityType::WitherSkull:
            return std::make_shared<WitherSkullEntity>();
        case ObjectEntityType::ShulkerBullet:
            return std::make_shared<ShulkerBulletEntity>();
        case ObjectEntityType::LlamaSpit:
            return std::make_shared<LlamaSpitEntity>();
        case ObjectEntityType::FallingBlockEntity:
            return std::make_shared<FallingBlockEntity>();
        case ObjectEntityType::ItemFrame:
            return std::make_shared<ItemFrameEntity>();
        case ObjectEntityType::EyeOfEnder:
            return std::make_shared<EyeOfEnderEntity>();
        case ObjectEntityType::ThrownPotion:
            return std::make_shared<ThrownPotionEntity>();
        case ObjectEntityType::ThrownExperienceBottle:
            return std::make_shared<ThrownExperienceBottleEntity>();
        case ObjectEntityType::FireworkRocketEntity:
            return std::make_shared<FireworkRocketEntity>();
        case ObjectEntityType::LeashFenceKnotEntity:
            return std::make_shared<LeashFenceKnotEntity>();
        case ObjectEntityType::ArmorStand:
            return std::make_shared<ArmorStandEntity>();
        case ObjectEntityType::EvokerFangs:
            return std::make_shared<EvokerFangsEntity>();
        case ObjectEntityType::FishingHook:
            return std::make_shared<FishingHookEntity>();
        case ObjectEntityType::SpectralArrow:
            return std::make_shared<SpectralArrowEntity>();
        case ObjectEntityType::DragonFireball:
            return std::make_shared<DragonFireballEntity>();
#if PROTOCOL_VERSION > 340
        case ObjectEntityType::ThrownTrident:
            return std::make_shared<ThrownTridentEntity>();
#endif
        default:
            return nullptr;
        }
    }
#endif

#if USE_GUI
    void Entity::InitializeFaces()
    {
        const Renderer::Atlas* atlas = AssetsManager::getInstance().GetAtlas();

        // Generate default faces
        face_descriptors = std::vector<FaceDescriptor>(6);
        faces = std::vector<Renderer::Face>(6);
        for (int i = 0; i < 6; ++i)
        {
            face_descriptors[i].orientation = static_cast<Orientation>(i);
            face_descriptors[i].texture_names = { "" };
            face_descriptors[i].cullface_direction = Orientation::None;
            face_descriptors[i].use_tintindexes = { false };

            // Base entity scale
            face_descriptors[i].transformations.scales.push_back(std::make_shared<Renderer::Scale>(
                static_cast<float>(GetWidth()) / 2.0f,
                static_cast<float>(GetHeight()) / 2.0f,
                static_cast<float>(GetWidth()) / 2.0f)
            );
            // Base translation
            face_descriptors[i].transformations.translations.push_back(std::make_shared<Renderer::Translation>(0.0f, static_cast<float>(GetHeight()) / 2.0f, 0.0f));
            // Entity pos translation
            face_descriptors[i].transformations.translations.push_back(std::make_shared<Renderer::Translation>(
                static_cast<float>(position.x),
                static_cast<float>(position.y),
                static_cast<float>(position.z))
            );
            // Entity yaw/pitch rotation
            face_descriptors[i].transformations.rotations.push_back(std::make_shared<Renderer::Rotation>(0.0f, 1.0f, 0.0f, yaw));
            face_descriptors[i].transformations.rotations.push_back(std::make_shared<Renderer::Rotation>(1.0f, 0.0f, 0.0f, pitch));

            face_descriptors[i].transformations.rotation = 0;

            faces[i] = Renderer::Face(face_descriptors[i].transformations, face_descriptors[i].orientation);
            faces[i].SetDisplayBackface(false);
            faces[i].SetTextureMultipliers({ 0xFFFFFFFF, 0xFFFFFFFF });

            // Extract texture info from the atlas
            std::array<unsigned short, 4> texture_pos = { 0, 0, 0, 0 };
            std::array<unsigned short, 4> texture_size = { 0, 0, 0, 0 };
            std::array<Renderer::Transparency, 2> transparencies = { Renderer::Transparency::Opaque, Renderer::Transparency::Opaque };
            std::array<Renderer::Animation, 2> animated = { Renderer::Animation::Static, Renderer::Animation::Static };

            for (int i = 0; i < std::min(2, static_cast<int>(face_descriptors[i].texture_names.size())); ++i)
            {
                const Renderer::TextureData& texture_data = atlas->GetData(face_descriptors[i].texture_names[i]);
                std::tie(texture_pos[2 * i + 0], texture_pos[2 * i + 1]) = texture_data.position;
                std::tie(texture_size[2 * i + 0], texture_size[2 * i + 1]) = texture_data.size;
                transparencies[i] = texture_data.transparency;
                animated[i] = texture_data.animation;
            }

            // Main texture coords in the atlas
            std::array<float, 4> coords = faces[i].GetTextureCoords(false);
            unsigned short height_normalizer = animated[0] == Renderer::Animation::Animated ? texture_size[0] : texture_size[1];
            coords[0] = (texture_pos[0] + coords[0] / 16.0f * texture_size[0]) / atlas->GetWidth();
            coords[1] = (texture_pos[1] + coords[1] / 16.0f * height_normalizer) / atlas->GetHeight();
            coords[2] = (texture_pos[0] + coords[2] / 16.0f * texture_size[0]) / atlas->GetWidth();
            coords[3] = (texture_pos[1] + coords[3] / 16.0f * height_normalizer) / atlas->GetHeight();
            faces[i].SetTextureCoords(coords, false);

            // Overlay texture coords in the atlas if existing
            if (face_descriptors[i].texture_names.size() > 1)
            {
                coords = faces[i].GetTextureCoords(true);
                height_normalizer = animated[1] == Renderer::Animation::Animated ? texture_size[2] : texture_size[3];
                coords[0] = (texture_pos[2] + coords[0] / 16.0f * texture_size[2]) / atlas->GetWidth();
                coords[1] = (texture_pos[3] + coords[1] / 16.0f * height_normalizer) / atlas->GetHeight();
                coords[2] = (texture_pos[2] + coords[2] / 16.0f * texture_size[2]) / atlas->GetWidth();
                coords[3] = (texture_pos[3] + coords[3] / 16.0f * height_normalizer) / atlas->GetHeight();
                faces[i].SetTextureCoords(coords, true);
            }

            faces[i].SetTransparencyData(transparencies[0]);
        }
        are_rendered_faces_up_to_date = false;
    }
#endif
}

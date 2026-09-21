#pragma once

#include <any>
#include <chrono>
#include <map>
#include <memory>
#include <optional>
#include <shared_mutex>

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif
#include "protocolCraft/Types/Item/Slot.hpp"
#include "protocolCraft/Utilities/Json.hpp"

#include "botcraft/Game/Physics/AABB.hpp"

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/Vector3.hpp"

#if USE_GUI
#include "botcraft/Game/Model.hpp"
#endif

namespace Botcraft
{
    enum class EntityType;
#if PROTOCOL_VERSION < 458 /* < 1.14 */
    enum class ObjectEntityType;
#endif

    struct EntityEffect
    {
        EntityEffectType type;
        unsigned char amplifier;
        std::chrono::steady_clock::time_point end;
    };

    enum class EntitySharedFlagsId : char
    {
        OnFire = 0,
        ShiftKeyDown = 1,
        // 2 is unused? Maybe in previous versions
        Sprinting = 3,
        Swimming = 4,
        Invisible = 5,
        Glowing = 6,
        FallFlying = 7
    };

    class Entity
    {
    protected:
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        static constexpr int metadata_count = 8;
#elif PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 7;
#else
        static constexpr int metadata_count = 6;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = 0;

    public:
        Entity();
        virtual ~Entity();

        // Object related stuff
        virtual std::string GetName() const = 0;
        virtual EntityType GetType() const = 0;
        AABB GetCollider() const;
        double GetWidth() const;
        double GetHeight() const;

        // Metadata stuff
        void LoadMetadataFromRawArray(const std::vector<unsigned char>& data);
        virtual void SetMetadataValue(const int index, const std::any& value);

        char GetDataSharedFlagsId() const;
        bool GetDataSharedFlagsId(const EntitySharedFlagsId id) const;
        int GetDataAirSupplyId() const;
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        std::optional<ProtocolCraft::Chat> GetDataCustomName() const;
#else
        std::string GetDataCustomName() const;
#endif
        bool GetDataCustomNameVisible() const;
        bool GetDataSilent() const;
        bool GetDataNoGravity() const;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        Pose GetDataPose() const;
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        int GetDataTicksFrozen() const;
#endif

        void SetDataSharedFlagsId(const char data_shared_flags_id);
        void SetDataSharedFlagsId(const EntitySharedFlagsId id, const bool b);
        void SetDataAirSupplyId(const int data_air_supply_id);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        void SetDataCustomName(const std::optional<ProtocolCraft::Chat>& data_custom_name);
#else
        void SetDataCustomName(const std::string& data_custom_name);
#endif
        void SetDataCustomNameVisible(const bool data_custom_name_visible);
        void SetDataSilent(const bool data_silent);
        void SetDataNoGravity(const bool data_no_gravity);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        void SetDataPose(const Pose data_pose);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        void SetDataTicksFrozen(const int data_ticks_frozen);
#endif

        // Generic properties getter
        int GetEntityID() const;
        ProtocolCraft::UUID GetUUID() const;
        Vector3<double> GetPosition() const;
        double GetX() const;
        double GetY() const;
        double GetZ() const;
        float GetYaw() const;
        float GetPitch() const;
        Vector3<double> GetSpeed() const;
        double GetSpeedX() const;
        double GetSpeedY() const;
        double GetSpeedZ() const;
        bool GetOnGround() const;
        std::map<EquipmentSlot, ProtocolCraft::Slot> GetEquipments() const;
        ProtocolCraft::Slot GetEquipment(const EquipmentSlot slot) const;
        std::vector<EntityEffect> GetEffects() const;
#if USE_GUI
        std::vector<Renderer::Face> GetFaces(const bool reset_uptodate_status);
        bool GetAreRenderedFacesUpToDate() const;
#endif

        // Generic properties setter
        void SetEntityID(const int entity_id_);
        void SetUUID(const ProtocolCraft::UUID& uuid_);
        virtual void SetPosition(const Vector3<double>& position_);
        virtual void SetX(const double x_);
        virtual void SetY(const double y_);
        virtual void SetZ(const double z_);
        virtual void SetYaw(const float yaw_);
        virtual void SetPitch(const float pitch_);
        void SetSpeed(const Vector3<double>& speed_);
        void SetSpeedX(const double speed_x_);
        void SetSpeedY(const double speed_y_);
        void SetSpeedZ(const double speed_z_);
        void SetOnGround(const bool on_ground_);
        void SetEquipment(const EquipmentSlot slot, const ProtocolCraft::Slot& item);
        void SetEffects(const std::vector<EntityEffect>& effects_);
        void AddEffect(const EntityEffect& effect);
        void RemoveEffect(const EntityEffectType type);
#if USE_GUI
        void SetAreRenderedFacesUpToDate(const bool are_rendered_faces_up_to_date_);
#endif

        // In case it's needed one day, could be useful
        virtual ProtocolCraft::Json::Value Serialize() const;

        virtual bool IsLocalPlayer() const;
        virtual bool IsRemotePlayer() const;
        // Can be used to know if an entity has a certain virtual type as ancestor
        virtual bool IsLivingEntity() const;
        virtual bool IsAbstractArrow() const;
        virtual bool IsAnimal() const;
        virtual bool IsAmbientCreature() const;
        virtual bool IsMonster() const;
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        virtual bool IsDisplay() const;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        virtual bool IsVehicle() const;
#endif
        virtual bool IsTamableAnimal() const;
        virtual bool IsAbstractSchoolingFish() const;
        virtual bool IsWaterAnimal() const;
        virtual bool IsAbstractChestedHorse() const;
        virtual bool IsAbstractHurtingProjectile() const;
        virtual bool IsMob() const;
        virtual bool IsSpellcasterIllager() const;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        virtual bool IsProjectile() const;
#endif
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        virtual bool IsFlyingMob() const;
#endif
        virtual bool IsAbstractHorse() const;
        virtual bool IsAbstractGolem() const;
        virtual bool IsHangingEntity() const;
        virtual bool IsFireball() const;
        virtual bool IsAbstractMinecart() const;
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        virtual bool IsAbstractCow() const;
#endif
        virtual bool IsAbstractMinecartContainer() const;
        virtual bool IsShoulderRidingEntity() const;
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        virtual bool IsAbstractPiglin() const;
#endif
        virtual bool IsAbstractIllager() const;
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        virtual bool IsAbstractThrownPotion() const;
#endif
        virtual bool IsAbstractFish() const;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        virtual bool IsRaider() const;
#endif
        virtual bool IsAbstractSkeleton() const;
        virtual bool IsThrowableItemProjectile() const;
#if PROTOCOL_VERSION > 477 /* > 1.14 */
        virtual bool IsAbstractVillager() const;
#endif
        virtual bool IsAgeableMob() const;
        virtual bool IsPathfinderMob() const;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        virtual bool IsPatrollingMonster() const;
#endif
        virtual bool IsThrowableProjectile() const;
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        virtual bool IsAbstractWindCharge() const;
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        virtual bool IsBlockAttachedEntity() const;
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        virtual bool IsAbstractBoat() const;
        virtual bool IsAbstractChestBoat() const;
        virtual bool IsAgeableWaterCreature() const;
        virtual bool IsBoat() const;
        virtual bool IsChestBoat() const;
        virtual bool IsChestRaft() const;
        virtual bool IsRaft() const;
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        virtual bool IsAvatar() const;
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        virtual bool IsAbstractNautilus() const;
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
        virtual bool IsAbstractCubeMob() const;
#endif

        // Factory stuff
        static std::shared_ptr<Entity> CreateEntity(const EntityType type);
#if PROTOCOL_VERSION < 458 /* < 1.14 */
        static std::shared_ptr<Entity> CreateObjectEntity(const ObjectEntityType type);
#endif

    protected:
#if USE_GUI
        virtual void InitializeFaces();
        void OnSizeUpdated();
#endif
        char GetDataSharedFlagsIdImpl() const;
        bool GetDataSharedFlagsIdImpl(const EntitySharedFlagsId id) const;
        void SetDataSharedFlagsIdImpl(const char data_shared_flags_id);
        void SetDataSharedFlagsIdImpl(const EntitySharedFlagsId id, const bool b);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        Pose GetDataPoseImpl() const;
        void SetDataPoseImpl(const Pose data_pose);
#endif
        AABB GetColliderImpl() const;
        virtual double GetWidthImpl() const;
        virtual double GetHeightImpl() const;

    protected:
        mutable std::shared_mutex entity_mutex;

        int entity_id;
        ProtocolCraft::UUID uuid;
        Vector3<double> position;
        float yaw;
        float pitch;
        Vector3<double> speed;
        bool on_ground;
        /// @brief Items on this entity. Note that for the local player
        /// this will **NOT** be populated. Check corresponding
        /// player inventory slots instead.
        std::map<EquipmentSlot, ProtocolCraft::Slot> equipments;
        std::vector<EntityEffect> effects;

        std::map<std::string, std::any> metadata;

#if USE_GUI
        //All the faces of this model
        std::vector<FaceDescriptor> face_descriptors;
        std::vector<Renderer::Face> faces;

        bool are_rendered_faces_up_to_date;
#endif
    };

    enum class EntityType
    {
        None = -1,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        AcaciaBoat,
        AcaciaChestBoat,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Allay,
#endif
        AreaEffectCloud,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        Armadillo,
#endif
        ArmorStand,
        Arrow,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        Axolotl,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        ChestRaft,
        Raft,
#endif
        Bat,
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        Bee,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        BirchBoat,
        BirchChestBoat,
#endif
        Blaze,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        DisplayBlockDisplay,
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        Boat,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        Bogged,
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        Breeze,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        BreezeWindCharge,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        ChestBoat,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        Cat,
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        Camel,
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        CamelHusk,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        Cat,
#endif
        CaveSpider,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        CherryBoat,
        CherryChestBoat,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ChestBoat,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        MinecartChest,
#endif
        Chicken,
        Cod,
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        CopperGolem,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        MinecartCommandBlock,
#endif
        Cow,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        Creaking,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
        CreakingTransient,
#endif
        Creeper,
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        Cushion,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        DarkOakBoat,
        DarkOakChestBoat,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        Donkey,
#endif
        Dolphin,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Donkey,
#endif
        DragonFireball,
        Drowned,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ThrownEgg,
#endif
        ElderGuardian,
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        EndCrystal,
        EnderDragon,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ThrownEnderpearl,
#endif
        EnderMan,
        Endermite,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        EnderDragon,
        ThrownEnderpearl,
        EndCrystal,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        EvokerFangs,
#endif
        Evoker,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        EvokerFangs,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ThrownExperienceBottle,
#endif
        ExperienceOrb,
        EyeOfEnder,
        FallingBlockEntity,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        LargeFireball,
#endif
        FireworkRocketEntity,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        Fox,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Frog,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        MinecartFurnace,
#endif
        Ghast,
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        HappyGhast,
#endif
        Giant,
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        GlowItemFrame,
        GlowSquid,
        Goat,
#endif
        Guardian,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Hoglin,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        MinecartHopper,
#endif
        Horse,
        Husk,
        Illusioner,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        Interaction,
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        IronGolem,
#endif
        ItemEntity,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        DisplayItemDisplay,
#endif
        ItemFrame,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        JungleBoat,
        JungleChestBoat,
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
        OminousItemSpawner,
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        LargeFireball,
#endif
        LeashFenceKnotEntity,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        LightningBolt,
#endif
        Llama,
        LlamaSpit,
        MagmaCube,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        MangroveBoat,
        MangroveChestBoat,
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        Mannequin,
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        Marker,
#endif
        Minecart,
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        MinecartChest,
        MinecartCommandBlock,
        MinecartFurnace,
        MinecartHopper,
        MinecartSpawner,
        MinecartTNT,
        Mule,
#endif
        MushroomCow,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        Mule,
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        Nautilus,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        OakBoat,
        OakChestBoat,
#endif
        Ocelot,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        OminousItemSpawner,
#endif
        Painting,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        PaleOakBoat,
        PaleOakChestBoat,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        Panda,
#endif
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        Parched,
#endif
        Parrot,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Phantom,
#endif
        Pig,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Piglin,
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        PiglinBrute,
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Pillager,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        Pufferfish,
        PigZombie,
#endif
        PolarBear,
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        PoplarBoat,
        PoplarChestBoat,
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        ThrownSplashPotion,
        ThrownLingeringPotion,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */ && PROTOCOL_VERSION < 770 /* < 1.21.5 */
        ThrownPotion,
#endif
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        PrimedTnt,
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Pufferfish,
#endif
        Rabbit,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Ravager,
#endif
        Salmon,
        Sheep,
        Shulker,
        ShulkerBullet,
        Silverfish,
        Skeleton,
        SkeletonHorse,
        Slime,
        SmallFireball,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        Sniffer,
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SnowGolem,
#endif
        Snowball,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SnowGolem,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        MinecartSpawner,
#endif
        SpectralArrow,
        Spider,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SpruceBoat,
        SpruceChestBoat,
#endif
        Squid,
        Stray,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Strider,
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
        SulfurCube,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Tadpole,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        DisplayTextDisplay,
        PrimedTnt,
        MinecartTNT,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 735 /* < 1.16 */
        TraderLlama,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        TropicalFish,
        Turtle,
#endif
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        ThrownEgg,
        ThrownEnderpearl,
        ThrownExperienceBottle,
        ThrownPotion,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        ThrownTrident,
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        TraderLlama,
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        ThrownTrident,
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        TropicalFish,
        Turtle,
#endif
        Vex,
        Villager,
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        IronGolem,
#endif
        Vindicator,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 735 /* < 1.16 */
        Pillager,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        WanderingTrader,
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Warden,
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        WindCharge,
#endif
        Witch,
        WitherBoss,
        WitherSkeleton,
        WitherSkull,
        Wolf,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        Zoglin,
#endif
        Zombie,
        ZombieHorse,
#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
        ZombieNautilus,
#endif
        ZombieVillager,
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        ZombifiedPiglin,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        Phantom,
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 735 /* < 1.16 */
        Ravager,
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        LightningBolt,
#endif
        Player,
        FishingHook,
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        ThrownTrident,
#endif
#else
        FishingHook = -3,
        Player = -2,
        ItemEntity = 1,
        ExperienceOrb = 2,
        AreaEffectCloud = 3,
        ElderGuardian = 4,
        WitherSkeleton = 5,
        Stray = 6,
        ThrownEgg = 7,
        LeashFenceKnotEntity = 8,
        Painting = 9,
        Arrow = 10,
        Snowball = 11,
        LargeFireball = 12,
        SmallFireball = 13,
        ThrownEnderpearl = 14,
        EyeOfEnder = 15,
        ThrownPotion = 16,
        ThrownExperienceBottle = 17,
        ItemFrame = 18,
        WitherSkull = 19,
        PrimedTnt = 20,
        FallingBlockEntity = 21,
        FireworkRocketEntity = 22,
        Husk = 23,
        SpectralArrow = 24,
        ShulkerBullet = 25,
        DragonFireball = 26,
        ZombieVillager = 27,
        SkeletonHorse = 28,
        ZombieHorse = 29,
        ArmorStand = 30,
        Donkey = 31,
        Mule = 32,
        EvokerFangs = 33,
        Evoker = 34,
        Vex = 35,
        Vindicator = 36,
        Illusioner = 37,
        MinecartCommandBlock = 40,
        Boat = 41,
        Minecart = 42,
        MinecartChest = 43,
        MinecartFurnace = 44,
        MinecartTNT = 45,
        MinecartHopper = 46,
        MinecartSpawner = 47,
        Creeper = 50,
        Skeleton = 51,
        Spider = 52,
        Giant = 53,
        Zombie = 54,
        Slime = 55,
        Ghast = 56,
        PigZombie = 57,
        EnderMan = 58,
        CaveSpider = 59,
        Silverfish = 60,
        Blaze = 61,
        MagmaCube = 62,
        EnderDragon = 63,
        WitherBoss = 64,
        Bat = 65,
        Witch = 66,
        Endermite = 67,
        Guardian = 68,
        Shulker = 69,
        Pig = 90,
        Sheep = 91,
        Cow = 92,
        Chicken = 93,
        Squid = 94,
        Wolf = 95,
        MushroomCow = 96,
        SnowGolem = 97,
        Ocelot = 98,
        IronGolem = 99,
        Horse = 100,
        Rabbit = 101,
        PolarBear = 102,
        Llama = 103,
        LlamaSpit = 104,
        Parrot = 105,
        Villager = 120,
        EndCrystal = 200,
#endif
        MaxEntityIndex
    };

#if PROTOCOL_VERSION < 458 /* < 1.14 */
    enum class ObjectEntityType
    {
        None = -1,
        Boat = 1,
        ItemEntity = 2,
        AreaEffectCloud = 3,
        PrimedTnt = 50,
        EndCrystal = 51,
        Arrow = 60,
        Snowball = 61,
        ThrownEgg = 62,
        LargeFireball = 63,
        SmallFireball = 64,
        ThrownEnderpearl = 65,
        WitherSkull = 66,
        ShulkerBullet = 67,
        LlamaSpit = 68,
        FallingBlockEntity = 70,
        ItemFrame = 71,
        EyeOfEnder = 72,
        ThrownPotion = 73,
        ThrownExperienceBottle = 75,
        FireworkRocketEntity = 76,
        LeashFenceKnotEntity = 77,
        ArmorStand = 78,
        EvokerFangs = 79,
        FishingHook = 90,
        SpectralArrow = 91,
        DragonFireball = 93,
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ThrownTrident = 94,
#endif
        MaxEntityIndex
    };
#endif
}

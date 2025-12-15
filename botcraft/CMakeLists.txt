project(botcraft)

set(botcraft_PUBLIC_HDR
    include/botcraft/AI/BaseNode.hpp
    include/botcraft/AI/BehaviourClient.hpp
    include/botcraft/AI/BehaviourTree.hpp
    include/botcraft/AI/Blackboard.hpp
    include/botcraft/AI/SimpleBehaviourClient.hpp
    include/botcraft/AI/Status.hpp
    include/botcraft/AI/TemplatedBehaviourClient.hpp

    include/botcraft/AI/Tasks/AllTasks.hpp
    include/botcraft/AI/Tasks/BaseTasks.hpp
    include/botcraft/AI/Tasks/DigTask.hpp
    include/botcraft/AI/Tasks/EntitiesTasks.hpp
    include/botcraft/AI/Tasks/InventoryTasks.hpp
    include/botcraft/AI/Tasks/PathfindingTask.hpp

    include/botcraft/Game/AssetsManager.hpp
    include/botcraft/Game/ManagersClient.hpp
    include/botcraft/Game/ConnectionClient.hpp
    include/botcraft/Game/Enums.hpp
    include/botcraft/Game/Model.hpp
    include/botcraft/Game/Vector3.hpp

    include/botcraft/Game/World/Biome.hpp
    include/botcraft/Game/World/Blockstate.hpp
    include/botcraft/Game/World/Chunk.hpp
    include/botcraft/Game/World/World.hpp

    include/botcraft/Game/Entities/EntityAttribute.hpp
    include/botcraft/Game/Entities/EntityManager.hpp
    include/botcraft/Game/Entities/GlobalPos.hpp
    include/botcraft/Game/Entities/LocalPlayer.hpp
    include/botcraft/Game/Entities/VillagerData.hpp
    include/botcraft/Game/Entities/entities/UnknownEntity.hpp

    include/botcraft/Game/Entities/entities/animal/allay/AllayEntity.hpp
    include/botcraft/Game/Entities/entities/AreaEffectCloudEntity.hpp
    include/botcraft/Game/Entities/entities/AvatarEntity.hpp
    include/botcraft/Game/Entities/entities/animal/armadillo/ArmadilloEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/ArmorStandEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/BlockAttachedEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/arrow/ArrowEntity.hpp
    include/botcraft/Game/Entities/entities/animal/axolotl/AxolotlEntity.hpp
    include/botcraft/Game/Entities/entities/ambient/BatEntity.hpp
    include/botcraft/Game/Entities/entities/animal/bee/BeeEntity.hpp
    include/botcraft/Game/Entities/entities/monster/BlazeEntity.hpp
    include/botcraft/Game/Entities/entities/monster/skeleton/BoggedEntity.hpp
    include/botcraft/Game/Entities/entities/monster/skeleton/ParchedEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/boat/BoatEntity.hpp
    include/botcraft/Game/Entities/entities/monster/breeze/BreezeEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/boat/ChestBoatEntity.hpp
    include/botcraft/Game/Entities/entities/animal/feline/CatEntity.hpp
    include/botcraft/Game/Entities/entities/animal/camel/CamelEntity.hpp
    include/botcraft/Game/Entities/entities/animal/camel/CamelHuskEntity.hpp
    include/botcraft/Game/Entities/entities/animal/golem/CopperGolemEntity.hpp
    include/botcraft/Game/Entities/entities/monster/spider/CaveSpiderEntity.hpp
    include/botcraft/Game/Entities/entities/animal/chicken/ChickenEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/CodEntity.hpp
    include/botcraft/Game/Entities/entities/animal/cow/CowEntity.hpp
    include/botcraft/Game/Entities/entities/animal/happyghast/HappyGhastEntity.hpp
    include/botcraft/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.hpp
    include/botcraft/Game/Entities/entities/animal/nautilus/NautilusEntity.hpp
    include/botcraft/Game/Entities/entities/animal/nautilus/ZombieNautilusEntity.hpp
    include/botcraft/Game/Entities/entities/monster/CreeperEntity.hpp
    include/botcraft/Game/Entities/entities/animal/dolphin/DolphinEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/DonkeyEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/DragonFireballEntity.hpp
    include/botcraft/Game/Entities/entities/DisplayBlockDisplayEntity.hpp
    include/botcraft/Game/Entities/entities/DisplayEntity.hpp
    include/botcraft/Game/Entities/entities/DisplayItemDisplayEntity.hpp
    include/botcraft/Game/Entities/entities/DisplayTextDisplayEntity.hpp
    include/botcraft/Game/Entities/entities/monster/zombie/DrownedEntity.hpp
    include/botcraft/Game/Entities/entities/monster/ElderGuardianEntity.hpp
    include/botcraft/Game/Entities/entities/boss/enderdragon/EndCrystalEntity.hpp
    include/botcraft/Game/Entities/entities/boss/enderdragon/EnderDragonEntity.hpp
    include/botcraft/Game/Entities/entities/monster/EnderManEntity.hpp
    include/botcraft/Game/Entities/entities/monster/EndermiteEntity.hpp
    include/botcraft/Game/Entities/entities/monster/illager/EvokerEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/EvokerFangsEntity.hpp
    include/botcraft/Game/Entities/entities/ExperienceOrbEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/EyeOfEnderEntity.hpp
    include/botcraft/Game/Entities/entities/item/FallingBlockEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/FireworkRocketEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fox/FoxEntity.hpp
    include/botcraft/Game/Entities/entities/animal/frog/FrogEntity.hpp
    include/botcraft/Game/Entities/entities/monster/GhastEntity.hpp
    include/botcraft/Game/Entities/entities/monster/GiantEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/GlowItemFrameEntity.hpp
    include/botcraft/Game/Entities/entities/animal/squid/GlowSquidEntity.hpp
    include/botcraft/Game/Entities/entities/animal/goat/GoatEntity.hpp
    include/botcraft/Game/Entities/entities/monster/GuardianEntity.hpp
    include/botcraft/Game/Entities/entities/monster/hoglin/HoglinEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/HorseEntity.hpp
    include/botcraft/Game/Entities/entities/monster/zombie/HuskEntity.hpp
    include/botcraft/Game/Entities/entities/monster/illager/IllusionerEntity.hpp
    include/botcraft/Game/Entities/entities/InteractionEntity.hpp
    include/botcraft/Game/Entities/entities/animal/golem/IronGolemEntity.hpp
    include/botcraft/Game/Entities/entities/item/ItemEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/ItemFrameEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/LargeFireballEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/MannequinEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/LeashFenceKnotEntity.hpp
    include/botcraft/Game/Entities/entities/LightningBoltEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/LlamaEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/LlamaSpitEntity.hpp
    include/botcraft/Game/Entities/entities/monster/MagmaCubeEntity.hpp
    include/botcraft/Game/Entities/entities/MarkerEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartChestEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartCommandBlockEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartFurnaceEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartHopperEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartSpawnerEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/MinecartTNTEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/MuleEntity.hpp
    include/botcraft/Game/Entities/entities/animal/cow/MushroomCowEntity.hpp
    include/botcraft/Game/Entities/entities/animal/feline/OcelotEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/painting/PaintingEntity.hpp
    include/botcraft/Game/Entities/entities/animal/panda/PandaEntity.hpp
    include/botcraft/Game/Entities/entities/animal/parrot/ParrotEntity.hpp
    include/botcraft/Game/Entities/entities/monster/PhantomEntity.hpp
    include/botcraft/Game/Entities/entities/monster/zombie/PigZombieEntity.hpp
    include/botcraft/Game/Entities/entities/animal/pig/PigEntity.hpp
    include/botcraft/Game/Entities/entities/monster/piglin/PiglinEntity.hpp
    include/botcraft/Game/Entities/entities/monster/piglin/PiglinBruteEntity.hpp
    include/botcraft/Game/Entities/entities/monster/illager/PillagerEntity.hpp
    include/botcraft/Game/Entities/entities/animal/polarbear/PolarBearEntity.hpp
    include/botcraft/Game/Entities/entities/item/PrimedTntEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/PufferfishEntity.hpp
    include/botcraft/Game/Entities/entities/animal/rabbit/RabbitEntity.hpp
    include/botcraft/Game/Entities/entities/monster/RavagerEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/SalmonEntity.hpp
    include/botcraft/Game/Entities/entities/animal/sheep/SheepEntity.hpp
    include/botcraft/Game/Entities/entities/monster/ShulkerEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/ShulkerBulletEntity.hpp
    include/botcraft/Game/Entities/entities/monster/SilverfishEntity.hpp
    include/botcraft/Game/Entities/entities/monster/skeleton/SkeletonEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/SkeletonHorseEntity.hpp
    include/botcraft/Game/Entities/entities/monster/SlimeEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/SmallFireballEntity.hpp
    include/botcraft/Game/Entities/entities/animal/sniffer/SnifferEntity.hpp
    include/botcraft/Game/Entities/entities/animal/golem/SnowGolemEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/SnowballEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/arrow/SpectralArrowEntity.hpp
    include/botcraft/Game/Entities/entities/monster/spider/SpiderEntity.hpp
    include/botcraft/Game/Entities/entities/animal/squid/SquidEntity.hpp
    include/botcraft/Game/Entities/entities/monster/skeleton/StrayEntity.hpp
    include/botcraft/Game/Entities/entities/monster/StriderEntity.hpp
    include/botcraft/Game/Entities/entities/animal/frog/TadpoleEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownEggEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownEnderpearlEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownExperienceBottleEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownLingeringPotionEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownPotionEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownSplashPotionEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/arrow/ThrownTridentEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/TraderLlamaEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/TropicalFishEntity.hpp
    include/botcraft/Game/Entities/entities/animal/turtle/TurtleEntity.hpp
    include/botcraft/Game/Entities/entities/monster/VexEntity.hpp
    include/botcraft/Game/Entities/entities/npc/villager/VillagerEntity.hpp
    include/botcraft/Game/Entities/entities/monster/illager/VindicatorEntity.hpp
    include/botcraft/Game/Entities/entities/npc/wanderingtrader/WanderingTraderEntity.hpp
    include/botcraft/Game/Entities/entities/monster/warden/WardenEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/windcharge/AbstractWindChargeEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/windcharge/BreezeWindChargeEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/windcharge/WindChargeEntity.hpp
    include/botcraft/Game/Entities/entities/monster/WitchEntity.hpp
    include/botcraft/Game/Entities/entities/boss/wither/WitherBossEntity.hpp
    include/botcraft/Game/Entities/entities/monster/skeleton/WitherSkeletonEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/WitherSkullEntity.hpp
    include/botcraft/Game/Entities/entities/animal/wolf/WolfEntity.hpp
    include/botcraft/Game/Entities/entities/monster/ZoglinEntity.hpp
    include/botcraft/Game/Entities/entities/monster/zombie/ZombieEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/ZombieHorseEntity.hpp
    include/botcraft/Game/Entities/entities/monster/zombie/ZombieVillagerEntity.hpp
    include/botcraft/Game/Entities/entities/monster/zombie/ZombifiedPiglinEntity.hpp
    include/botcraft/Game/Entities/entities/player/PlayerEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/FishingHookEntity.hpp
    include/botcraft/Game/Entities/entities/Entity.hpp
    include/botcraft/Game/Entities/entities/LivingEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/arrow/AbstractArrowEntity.hpp
    include/botcraft/Game/Entities/entities/animal/AnimalEntity.hpp
    include/botcraft/Game/Entities/entities/ambient/AmbientCreatureEntity.hpp
    include/botcraft/Game/Entities/entities/monster/MonsterEntity.hpp
    include/botcraft/Game/Entities/entities/TamableAnimalEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/AbstractSchoolingFishEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/WaterAnimalEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/AbstractChestedHorseEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/AbstractHurtingProjectileEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/AbstractThrownPotionEntity.hpp
    include/botcraft/Game/Entities/entities/MobEntity.hpp
    include/botcraft/Game/Entities/entities/OminousItemSpawnerEntity.hpp
    include/botcraft/Game/Entities/entities/monster/illager/SpellcasterIllagerEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp
    include/botcraft/Game/Entities/entities/FlyingMobEntity.hpp
    include/botcraft/Game/Entities/entities/animal/equine/AbstractHorseEntity.hpp
    include/botcraft/Game/Entities/entities/animal/golem/AbstractGolemEntity.hpp
    include/botcraft/Game/Entities/entities/decoration/HangingEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/hurtingprojectile/FireballEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/AbstractMinecartEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/minecart/AbstractMinecartContainerEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/boat/AbstractBoatEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/boat/AbstractChestBoatEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/boat/ChestRaftEntity.hpp
    include/botcraft/Game/Entities/entities/vehicle/boat/RaftEntity.hpp
    include/botcraft/Game/Entities/entities/animal/parrot/ShoulderRidingEntity.hpp
    include/botcraft/Game/Entities/entities/monster/piglin/AbstractPiglinEntity.hpp
    include/botcraft/Game/Entities/entities/monster/illager/AbstractIllagerEntity.hpp
    include/botcraft/Game/Entities/entities/animal/cow/AbstractCowEntity.hpp
    include/botcraft/Game/Entities/entities/animal/fish/AbstractFishEntity.hpp
    include/botcraft/Game/Entities/entities/raid/RaiderEntity.hpp
    include/botcraft/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrowableItemProjectileEntity.hpp
    include/botcraft/Game/Entities/entities/npc/villager/AbstractVillagerEntity.hpp
    include/botcraft/Game/Entities/entities/AgeableMobEntity.hpp
    include/botcraft/Game/Entities/entities/animal/AgeableWaterCreatureEntity.hpp
    include/botcraft/Game/Entities/entities/PathfinderMobEntity.hpp
    include/botcraft/Game/Entities/entities/monster/PatrollingMonsterEntity.hpp
    include/botcraft/Game/Entities/entities/projectile/ThrowableProjectileEntity.hpp
    include/botcraft/Game/Entities/entities/monster/creaking/CreakingEntity.hpp
    include/botcraft/Game/Entities/entities/monster/creaking/CreakingTransientEntity.hpp

    include/botcraft/Game/Inventory/Window.hpp
    include/botcraft/Game/Inventory/InventoryManager.hpp
    include/botcraft/Game/Inventory/Item.hpp

    include/botcraft/Game/Physics/AABB.hpp
    include/botcraft/Game/Physics/PhysicsManager.hpp

    include/botcraft/Network/NetworkManager.hpp
    include/botcraft/Network/LastSeenMessagesTracker.hpp

    include/botcraft/Utilities/DemanglingUtilities.hpp
    include/botcraft/Utilities/EnumUtilities.hpp
    include/botcraft/Utilities/Logger.hpp
    include/botcraft/Utilities/MiscUtilities.hpp
    include/botcraft/Utilities/ItemUtilities.hpp
    include/botcraft/Utilities/ScopeLockedWrapper.hpp
    include/botcraft/Utilities/SleepUtilities.hpp
    include/botcraft/Utilities/StdAnyUtilities.hpp
    include/botcraft/Utilities/Templates.hpp
)

set(botcraft_PRIVATE_HDR
    private_include/botcraft/Network/Authentifier.hpp
    private_include/botcraft/Network/AESEncrypter.hpp
    private_include/botcraft/Network/Compression.hpp
    private_include/botcraft/Network/TCP_Com.hpp

    private_include/botcraft/Network/DNS/DNSMessage.hpp
    private_include/botcraft/Network/DNS/DNSQuestion.hpp
    private_include/botcraft/Network/DNS/DNSResourceRecord.hpp
    private_include/botcraft/Network/DNS/DNSSrvData.hpp

    private_include/botcraft/Utilities/StringUtilities.hpp

    private_include/botcraft/Game/World/Section.hpp
)

set(botcraft_SRC
    src/AI/BaseNode.cpp
    src/AI/BehaviourClient.cpp
    src/AI/Blackboard.cpp
    src/AI/SimpleBehaviourClient.cpp

    src/AI/Tasks/BaseTasks.cpp
    src/AI/Tasks/DigTask.cpp
    src/AI/Tasks/EntitiesTasks.cpp
    src/AI/Tasks/InventoryTasks.cpp
    src/AI/Tasks/PathfindingTask.cpp

    src/Game/AssetsManager.cpp
    src/Game/ConnectionClient.cpp
    src/Game/Enums.cpp
    src/Game/ManagersClient.cpp
    src/Game/Model.cpp

    src/Game/World/Biome.cpp
    src/Game/World/Blockstate.cpp
    src/Game/World/Chunk.cpp
    src/Game/World/Section.cpp
    src/Game/World/World.cpp

    src/Game/Inventory/Window.cpp
    src/Game/Inventory/InventoryManager.cpp
    src/Game/Inventory/Item.cpp

    src/Game/Entities/EntityAttribute.cpp
    src/Game/Entities/EntityManager.cpp
    src/Game/Entities/LocalPlayer.cpp
    src/Game/Entities/entities/UnknownEntity.cpp

    src/Game/Entities/entities/animal/allay/AllayEntity.cpp
    src/Game/Entities/entities/AreaEffectCloudEntity.cpp
    src/Game/Entities/entities/AvatarEntity.cpp
    src/Game/Entities/entities/animal/armadillo/ArmadilloEntity.cpp
    src/Game/Entities/entities/decoration/ArmorStandEntity.cpp
    src/Game/Entities/entities/decoration/BlockAttachedEntity.cpp
    src/Game/Entities/entities/projectile/arrow/ArrowEntity.cpp
    src/Game/Entities/entities/animal/axolotl/AxolotlEntity.cpp
    src/Game/Entities/entities/ambient/BatEntity.cpp
    src/Game/Entities/entities/animal/bee/BeeEntity.cpp
    src/Game/Entities/entities/monster/BlazeEntity.cpp
    src/Game/Entities/entities/monster/skeleton/BoggedEntity.cpp
    src/Game/Entities/entities/monster/skeleton/ParchedEntity.cpp
    src/Game/Entities/entities/vehicle/boat/BoatEntity.cpp
    src/Game/Entities/entities/monster/breeze/BreezeEntity.cpp
    src/Game/Entities/entities/vehicle/boat/ChestBoatEntity.cpp
    src/Game/Entities/entities/animal/feline/CatEntity.cpp
    src/Game/Entities/entities/animal/camel/CamelEntity.cpp
    src/Game/Entities/entities/animal/camel/CamelHuskEntity.cpp
    src/Game/Entities/entities/animal/golem/CopperGolemEntity.cpp
    src/Game/Entities/entities/monster/spider/CaveSpiderEntity.cpp
    src/Game/Entities/entities/animal/chicken/ChickenEntity.cpp
    src/Game/Entities/entities/animal/fish/CodEntity.cpp
    src/Game/Entities/entities/animal/cow/CowEntity.cpp
    src/Game/Entities/entities/animal/happyghast/HappyGhastEntity.cpp
    src/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.cpp
    src/Game/Entities/entities/animal/nautilus/NautilusEntity.cpp
    src/Game/Entities/entities/animal/nautilus/ZombieNautilusEntity.cpp
    src/Game/Entities/entities/monster/CreeperEntity.cpp
    src/Game/Entities/entities/animal/dolphin/DolphinEntity.cpp
    src/Game/Entities/entities/animal/equine/DonkeyEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/DragonFireballEntity.cpp
    src/Game/Entities/entities/DisplayBlockDisplayEntity.cpp
    src/Game/Entities/entities/DisplayEntity.cpp
    src/Game/Entities/entities/DisplayItemDisplayEntity.cpp
    src/Game/Entities/entities/DisplayTextDisplayEntity.cpp
    src/Game/Entities/entities/monster/zombie/DrownedEntity.cpp
    src/Game/Entities/entities/monster/ElderGuardianEntity.cpp
    src/Game/Entities/entities/boss/enderdragon/EndCrystalEntity.cpp
    src/Game/Entities/entities/boss/enderdragon/EnderDragonEntity.cpp
    src/Game/Entities/entities/monster/EnderManEntity.cpp
    src/Game/Entities/entities/monster/EndermiteEntity.cpp
    src/Game/Entities/entities/monster/illager/EvokerEntity.cpp
    src/Game/Entities/entities/projectile/EvokerFangsEntity.cpp
    src/Game/Entities/entities/ExperienceOrbEntity.cpp
    src/Game/Entities/entities/projectile/EyeOfEnderEntity.cpp
    src/Game/Entities/entities/item/FallingBlockEntity.cpp
    src/Game/Entities/entities/projectile/FireworkRocketEntity.cpp
    src/Game/Entities/entities/animal/fox/FoxEntity.cpp
    src/Game/Entities/entities/animal/frog/FrogEntity.cpp
    src/Game/Entities/entities/monster/GhastEntity.cpp
    src/Game/Entities/entities/monster/GiantEntity.cpp
    src/Game/Entities/entities/decoration/GlowItemFrameEntity.cpp
    src/Game/Entities/entities/animal/squid//GlowSquidEntity.cpp
    src/Game/Entities/entities/animal/goat/GoatEntity.cpp
    src/Game/Entities/entities/monster/GuardianEntity.cpp
    src/Game/Entities/entities/monster/hoglin/HoglinEntity.cpp
    src/Game/Entities/entities/animal/equine/HorseEntity.cpp
    src/Game/Entities/entities/monster/zombie/HuskEntity.cpp
    src/Game/Entities/entities/monster/illager/IllusionerEntity.cpp
    src/Game/Entities/entities/InteractionEntity.cpp
    src/Game/Entities/entities/animal/golem/IronGolemEntity.cpp
    src/Game/Entities/entities/item/ItemEntity.cpp
    src/Game/Entities/entities/decoration/ItemFrameEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/LargeFireballEntity.cpp
    src/Game/Entities/entities/decoration/LeashFenceKnotEntity.cpp
    src/Game/Entities/entities/LightningBoltEntity.cpp
    src/Game/Entities/entities/animal/equine/LlamaEntity.cpp
    src/Game/Entities/entities/projectile/LlamaSpitEntity.cpp
    src/Game/Entities/entities/monster/MagmaCubeEntity.cpp
    src/Game/Entities/entities/MarkerEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartChestEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartCommandBlockEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartFurnaceEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartHopperEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartSpawnerEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/MinecartTNTEntity.cpp
    src/Game/Entities/entities/animal/equine/MuleEntity.cpp
    src/Game/Entities/entities/animal/cow/MushroomCowEntity.cpp
    src/Game/Entities/entities/animal/feline/OcelotEntity.cpp
    src/Game/Entities/entities/decoration/MannequinEntity.cpp
    src/Game/Entities/entities/decoration/painting/PaintingEntity.cpp
    src/Game/Entities/entities/animal/panda/PandaEntity.cpp
    src/Game/Entities/entities/animal/parrot/ParrotEntity.cpp
    src/Game/Entities/entities/monster/PhantomEntity.cpp
    src/Game/Entities/entities/monster/zombie/PigZombieEntity.cpp
    src/Game/Entities/entities/animal/pig/PigEntity.cpp
    src/Game/Entities/entities/monster/piglin/PiglinEntity.cpp
    src/Game/Entities/entities/monster/piglin/PiglinBruteEntity.cpp
    src/Game/Entities/entities/monster/illager/PillagerEntity.cpp
    src/Game/Entities/entities/animal/polarbear/PolarBearEntity.cpp
    src/Game/Entities/entities/item/PrimedTntEntity.cpp
    src/Game/Entities/entities/animal/fish/PufferfishEntity.cpp
    src/Game/Entities/entities/animal/rabbit/RabbitEntity.cpp
    src/Game/Entities/entities/monster/RavagerEntity.cpp
    src/Game/Entities/entities/animal/fish/SalmonEntity.cpp
    src/Game/Entities/entities/animal/sheep/SheepEntity.cpp
    src/Game/Entities/entities/monster/ShulkerEntity.cpp
    src/Game/Entities/entities/projectile/ShulkerBulletEntity.cpp
    src/Game/Entities/entities/monster/SilverfishEntity.cpp
    src/Game/Entities/entities/monster/skeleton/SkeletonEntity.cpp
    src/Game/Entities/entities/animal/equine/SkeletonHorseEntity.cpp
    src/Game/Entities/entities/monster/SlimeEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/SmallFireballEntity.cpp
    src/Game/Entities/entities/animal/sniffer/SnifferEntity.cpp
    src/Game/Entities/entities/animal/golem/SnowGolemEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/SnowballEntity.cpp
    src/Game/Entities/entities/projectile/arrow/SpectralArrowEntity.cpp
    src/Game/Entities/entities/monster/spider/SpiderEntity.cpp
    src/Game/Entities/entities/animal/squid/SquidEntity.cpp
    src/Game/Entities/entities/monster/skeleton/StrayEntity.cpp
    src/Game/Entities/entities/monster/StriderEntity.cpp
    src/Game/Entities/entities/animal/frog/TadpoleEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrownEggEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrownEnderpearlEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrownExperienceBottleEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrownLingeringPotionEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrownPotionEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrownSplashPotionEntity.cpp
    src/Game/Entities/entities/projectile/arrow/ThrownTridentEntity.cpp
    src/Game/Entities/entities/animal/equine/TraderLlamaEntity.cpp
    src/Game/Entities/entities/animal/fish/TropicalFishEntity.cpp
    src/Game/Entities/entities/animal/turtle/TurtleEntity.cpp
    src/Game/Entities/entities/monster/VexEntity.cpp
    src/Game/Entities/entities/npc/villager/VillagerEntity.cpp
    src/Game/Entities/entities/monster/illager/VindicatorEntity.cpp
    src/Game/Entities/entities/npc/wanderingtrader/WanderingTraderEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/windcharge/AbstractWindChargeEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/windcharge/BreezeWindChargeEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/windcharge/WindChargeEntity.cpp
    src/Game/Entities/entities/monster/warden/WardenEntity.cpp
    src/Game/Entities/entities/monster/WitchEntity.cpp
    src/Game/Entities/entities/boss/wither/WitherBossEntity.cpp
    src/Game/Entities/entities/monster/skeleton/WitherSkeletonEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/WitherSkullEntity.cpp
    src/Game/Entities/entities/animal/wolf/WolfEntity.cpp
    src/Game/Entities/entities/monster/ZoglinEntity.cpp
    src/Game/Entities/entities/monster/zombie/ZombieEntity.cpp
    src/Game/Entities/entities/animal/equine/ZombieHorseEntity.cpp
    src/Game/Entities/entities/monster/zombie/ZombieVillagerEntity.cpp
    src/Game/Entities/entities/monster/zombie/ZombifiedPiglinEntity.cpp
    src/Game/Entities/entities/player/PlayerEntity.cpp
    src/Game/Entities/entities/projectile/FishingHookEntity.cpp
    src/Game/Entities/entities/Entity.cpp
    src/Game/Entities/entities/LivingEntity.cpp
    src/Game/Entities/entities/projectile/arrow/AbstractArrowEntity.cpp
    src/Game/Entities/entities/animal/AnimalEntity.cpp
    src/Game/Entities/entities/ambient/AmbientCreatureEntity.cpp
    src/Game/Entities/entities/monster/MonsterEntity.cpp
    src/Game/Entities/entities/TamableAnimalEntity.cpp
    src/Game/Entities/entities/animal/fish/AbstractSchoolingFishEntity.cpp
    src/Game/Entities/entities/animal/fish/WaterAnimalEntity.cpp
    src/Game/Entities/entities/animal/equine/AbstractChestedHorseEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/AbstractHurtingProjectileEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/AbstractThrownPotionEntity.cpp
    src/Game/Entities/entities/MobEntity.cpp
    src/Game/Entities/entities/OminousItemSpawnerEntity.cpp
    src/Game/Entities/entities/monster/illager/SpellcasterIllagerEntity.cpp
    src/Game/Entities/entities/projectile/ProjectileEntity.cpp
    src/Game/Entities/entities/FlyingMobEntity.cpp
    src/Game/Entities/entities/animal/equine/AbstractHorseEntity.cpp
    src/Game/Entities/entities/animal/golem/AbstractGolemEntity.cpp
    src/Game/Entities/entities/decoration/HangingEntity.cpp
    src/Game/Entities/entities/projectile/hurtingprojectile/FireballEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/AbstractMinecartEntity.cpp
    src/Game/Entities/entities/vehicle/minecart/AbstractMinecartContainerEntity.cpp
    src/Game/Entities/entities/vehicle/VehicleEntity.cpp
    src/Game/Entities/entities/animal/parrot/ShoulderRidingEntity.cpp
    src/Game/Entities/entities/monster/piglin/AbstractPiglinEntity.cpp
    src/Game/Entities/entities/monster/illager/AbstractIllagerEntity.cpp
    src/Game/Entities/entities/animal/cow/AbstractCowEntity.cpp
    src/Game/Entities/entities/animal/fish/AbstractFishEntity.cpp
    src/Game/Entities/entities/raid/RaiderEntity.cpp
    src/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.cpp
    src/Game/Entities/entities/projectile/throwableitemprojectile/ThrowableItemProjectileEntity.cpp
    src/Game/Entities/entities/npc/villager/AbstractVillagerEntity.cpp
    src/Game/Entities/entities/AgeableMobEntity.cpp
    src/Game/Entities/entities/animal/AgeableWaterCreatureEntity.cpp
    src/Game/Entities/entities/PathfinderMobEntity.cpp
    src/Game/Entities/entities/monster/PatrollingMonsterEntity.cpp
    src/Game/Entities/entities/projectile/ThrowableProjectileEntity.cpp
    src/Game/Entities/entities/monster/creaking/CreakingEntity.cpp
    src/Game/Entities/entities/monster/creaking/CreakingTransientEntity.cpp
    src/Game/Entities/entities/vehicle/boat/AbstractBoatEntity.cpp
    src/Game/Entities/entities/vehicle/boat/AbstractChestBoatEntity.cpp
    src/Game/Entities/entities/vehicle/boat/ChestRaftEntity.cpp
    src/Game/Entities/entities/vehicle/boat/RaftEntity.cpp

    src/Game/Physics/AABB.cpp
    src/Game/Physics/PhysicsManager.cpp

    src/Network/AESEncrypter.cpp
    src/Network/Authentifier.cpp
    src/Network/Compression.cpp
    src/Network/LastSeenMessagesTracker.cpp
    src/Network/NetworkManager.cpp
    src/Network/TCP_Com.cpp

    src/Utilities/DemanglingUtilities.cpp
    src/Utilities/Logger.cpp
    src/Utilities/ItemUtilities.cpp
    src/Utilities/SleepUtilities.cpp
    src/Utilities/StdAnyUtilities.cpp
    src/Utilities/StringUtilities.cpp
)

if(BOTCRAFT_USE_OPENGL_GUI)
    list(APPEND botcraft_PUBLIC_HDR
            include/botcraft/Renderer/RenderingManager.hpp
            include/botcraft/Renderer/Enums.hpp
            include/botcraft/Renderer/Face.hpp
            include/botcraft/Renderer/Transformation.hpp
    )

    list(APPEND botcraft_PRIVATE_HDR
            private_include/botcraft/Renderer/Atlas.hpp
            private_include/botcraft/Renderer/BehaviourRenderer.hpp
            private_include/botcraft/Renderer/BlockRenderable.hpp
            private_include/botcraft/Renderer/Camera.hpp
            private_include/botcraft/Renderer/Chunk.hpp
            private_include/botcraft/Renderer/Entity.hpp
            private_include/botcraft/Renderer/ImageSaver.hpp
            private_include/botcraft/Renderer/Shader.hpp
            private_include/botcraft/Renderer/TransparentChunk.hpp
            private_include/botcraft/Renderer/WorldRenderer.hpp
    )

    list(APPEND botcraft_SRC
            src/Renderer/Atlas.cpp
            src/Renderer/BehaviourRenderer.cpp
            src/Renderer/BlockRenderable.cpp
            src/Renderer/Camera.cpp
            src/Renderer/Chunk.cpp
            src/Renderer/Entity.cpp
            src/Renderer/RenderingManager.cpp
            src/Renderer/Face.cpp
            src/Renderer/ImageSaver.cpp
            src/Renderer/Shader.cpp
            src/Renderer/Transformation.cpp
            src/Renderer/TransparentChunk.cpp
            src/Renderer/WorldRenderer.cpp
    )
endif(BOTCRAFT_USE_OPENGL_GUI)


# To have a nice files structure in Visual Studio
if(MSVC)
    foreach(source IN LISTS botcraft_PUBLIC_HDR)
        get_filename_component(source_path_header "${source}" PATH)
        string(REPLACE "include/botcraft" "Header Files/public" source_path_header "${source_path_header}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path_header}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()

    foreach(source IN LISTS botcraft_PRIVATE_HDR)
        get_filename_component(source_path_header "${source}" PATH)
        string(REPLACE "private_include/botcraft" "Header Files/private" source_path_header "${source_path_header}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path_header}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()

    foreach(source IN LISTS botcraft_SRC)
        get_filename_component(source_path "${source}" PATH)
        string(REPLACE "src" "Source Files" source_path "${source_path}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
endif()

if(BOTCRAFT_STATIC)
    add_library(botcraft STATIC ${botcraft_SRC} ${botcraft_PUBLIC_HDR} ${botcraft_PRIVATE_HDR})
else()
    add_library(botcraft SHARED ${botcraft_SRC} ${botcraft_PUBLIC_HDR} ${botcraft_PRIVATE_HDR})
endif(BOTCRAFT_STATIC)
set_property(TARGET botcraft PROPERTY CXX_STANDARD 17)
set_target_properties(botcraft PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(botcraft PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
# Add special $ORIGIN to rpath so Linux can find shared libraries in same folder
set_target_properties(botcraft PROPERTIES INSTALL_RPATH "$ORIGIN")

# Enable precompiled headers, except on GCC because it's hurting performances
if (BOTCRAFT_USE_PRECOMPILED_HEADERS AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_precompile_headers(botcraft PRIVATE
        include/botcraft/Game/Entities/entities/Entity.hpp
        ${protocolCraft_SOURCE_DIR}/include/protocolCraft/AllPackets.hpp
    )
endif()

if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/lib")
else()
    set_target_properties(botcraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(botcraft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/lib")
endif(MSVC)

if (MSVC)
    target_compile_options(botcraft PRIVATE "/bigobj")
    set_target_properties(botcraft PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif (MSVC)

# Set version header
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/include/botcraft/Version.hpp")

if (WIN32)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/download_mc_assets.bat.in" "${CMAKE_CURRENT_BINARY_DIR}/download_mc_assets.bat")
else()
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/download_mc_assets.sh.in" "${CMAKE_CURRENT_BINARY_DIR}/download_mc_assets.sh")
endif (WIN32)

# Add include folders
target_include_directories(botcraft
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
    PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private_include>"
)

target_compile_definitions(botcraft PRIVATE ASSETS_PATH="${ASSET_DIR}")

if (NOT BOTCRAFT_STATIC)
    # Add DL lib for linux compilation
    target_link_libraries(botcraft PUBLIC ${CMAKE_DL_LIBS})
endif()

# Add protocolCraft
target_link_libraries(botcraft PUBLIC protocolCraft)

if (WIN32 AND BOTCRAFT_WINDOWS_BETTER_SLEEP)
    target_link_libraries(botcraft PRIVATE winmm.lib)
    target_compile_definitions(botcraft PRIVATE BETTER_SLEEP=1)
endif()

# Add Asio
target_link_libraries(botcraft PRIVATE asio)
target_compile_definitions(botcraft PRIVATE ASIO_STANDALONE)

# Add threads support
target_link_libraries(botcraft PUBLIC Threads::Threads)

# Add graphical dependencies
if(BOTCRAFT_USE_OPENGL_GUI)
    target_link_libraries(botcraft PRIVATE glfw glad glm rectpack2D OpenGL::GL stb_image)
    if(BOTCRAFT_USE_IMGUI)
        target_link_libraries(botcraft PRIVATE imgui)
        target_compile_definitions(botcraft PRIVATE USE_IMGUI=1)
    endif()
    target_compile_definitions(botcraft PUBLIC USE_GUI=1)
endif(BOTCRAFT_USE_OPENGL_GUI)

if(BOTCRAFT_COMPRESSION)
    target_link_libraries(botcraft PRIVATE ZLIB::ZLIB)
    target_compile_definitions(botcraft PRIVATE USE_COMPRESSION=1)
endif(BOTCRAFT_COMPRESSION)

if(BOTCRAFT_ENCRYPTION)
    target_link_libraries(botcraft PRIVATE OpenSSL::SSL)
    target_link_libraries(botcraft PRIVATE OpenSSL::Crypto)
    target_compile_definitions(botcraft PRIVATE USE_ENCRYPTION=1)
endif(BOTCRAFT_ENCRYPTION)

if(WIN32 AND MINGW)
    target_link_libraries(botcraft PRIVATE ws2_32 crypt32)
    # Copy dll from the compiler folder
    get_filename_component(COMPILER_FOLDER ${CMAKE_CXX_COMPILER} DIRECTORY)
    add_custom_command(TARGET botcraft POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${COMPILER_FOLDER}/libstdc++-6.dll"
            $<TARGET_FILE_DIR:botcraft>)
endif()

# Installation stuff
include(GNUInstallDirs)

install(TARGETS botcraft
    EXPORT botcraft-targets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

if (NOT BOTCRAFT_INSTALL_MC_ASSETS)
    if (WIN32)
        install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/download_mc_assets.bat"
            DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
    else()
        install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/download_mc_assets.sh"
            DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
    endif (WIN32)
endif(NOT BOTCRAFT_INSTALL_MC_ASSETS)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/botcraft"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/include/botcraft/Version.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/botcraft"
)

install(EXPORT botcraft-targets
    FILE botcraft-targets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/botcraft"
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/botcraft-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/botcraft"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-config.cmake"
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/botcraft"
)

export(EXPORT botcraft-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/botcraft-targets.cmake"
)

# Copy asset files into install binary folder
if (BOTCRAFT_INSTALL_MC_ASSETS)
    install(DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${BOTCRAFT_GAME_VERSION}"
        DESTINATION "${CMAKE_INSTALL_BINDIR}/Assets"
    )
else()
    install(DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${BOTCRAFT_GAME_VERSION}"
        DESTINATION "${CMAKE_INSTALL_BINDIR}/Assets"
        PATTERN "minecraft" EXCLUDE
    )
endif(BOTCRAFT_INSTALL_MC_ASSETS)

# Copy Mingw libstdc++ dll
if(WIN32 AND MINGW)
    install(FILES
        "${BOTCRAFT_OUTPUT_DIR}/bin/libstdc++-6.dll"
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )
endif()

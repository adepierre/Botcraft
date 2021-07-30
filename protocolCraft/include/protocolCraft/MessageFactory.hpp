#pragma once

#include <memory>

#include "protocolCraft/AllMessages.hpp"
#include "protocolCraft/enums.hpp"

namespace ProtocolCraft
{
    class MessageFactory
    {
    public:
        static std::shared_ptr<Message> CreateMessageClientbound(const int id, const ConnectionState state)
        {
            switch (state)
            {
            case ConnectionState::None:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Handshake:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Status:
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<ClientboundStatusResponsePacket>(new ClientboundStatusResponsePacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundPongResponsePacket>(new ClientboundPongResponsePacket);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Login: // Login
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<ClientboundLoginDisconnectPacket>(new ClientboundLoginDisconnectPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundHelloPacket>(new ClientboundHelloPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundGameProfilePacket>(new ClientboundGameProfilePacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundLoginCompressionPacket>(new ClientboundLoginCompressionPacket);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Play:
                switch (id)
                {
#if PROTOCOL_VERSION == 340 // 1.12.2
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddGlobalEntityPacket>(new ClientboundAddGlobalEntityPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ClientboundContainerAckPacket>(new ClientboundContainerAckPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ClientboundMoveEntityPacket>(new ClientboundMoveEntityPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x27:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ClientboundPlayerCombatPacket>(new ClientboundPlayerCombatPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundUseBedPacket>(new ClientboundUseBedPacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x32:
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
                    break;
                case 0x33:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x34:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
                case 0x35:
                    return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
                    break;
                case 0x36:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x37:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundSetBorderPacket>(new ClientboundSetBorderPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
                case 0x3A:
                    return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
                    break;
                case 0x3B:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x3C:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x40:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetTitlesPacket>(new ClientboundSetTitlesPacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x4F:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddGlobalEntityPacket>(new ClientboundAddGlobalEntityPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
				case 0x09:
					return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
					break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
				case 0x0B:
                    return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ClientboundCommandsPacket>(new ClientboundCommandsPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundContainerAckPacket>(new ClientboundContainerAckPacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundTagQueryPacket>(new ClientboundTagQueryPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ClientboundMoveEntityPacket>(new ClientboundMoveEntityPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundPlayerCombatPacket>(new ClientboundPlayerCombatPacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundPlayerLookAtPacket>(new ClientboundPlayerLookAtPacket);
                    break;
                case 0x32:
                    return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
                    break;
                case 0x33:
                    return std::shared_ptr<ClientboundUseBedPacket>(new ClientboundUseBedPacket);
                    break;
                case 0x34:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x35:
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
                    break;
                case 0x36:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x37:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x3A:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x3B:
                    return std::shared_ptr<ClientboundSetBorderPacket>(new ClientboundSetBorderPacket);
                    break;
                case 0x3C:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x40:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundSetTitlesPacket>(new ClientboundSetTitlesPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundStopSoundPacket>(new ClientboundStopSoundPacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x4F:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
                case 0x50:
                    return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
                    break;
                case 0x51:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x52:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x53:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
                case 0x54:
                    return std::shared_ptr<ClientboundUpdateRecipesPacket>(new ClientboundUpdateRecipesPacket);
                    break;
                case 0x55:
                    return std::shared_ptr<ClientboundUpdateTagsPacket>(new ClientboundUpdateTagsPacket);
                    break;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddGlobalEntityPacket>(new ClientboundAddGlobalEntityPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
				case 0x09:
					return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
				    break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
				case 0x0B:
                    return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ClientboundCommandsPacket>(new ClientboundCommandsPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundContainerAckPacket>(new ClientboundContainerAckPacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ClientboundHorseScreenOpenPacket>(new ClientboundHorseScreenOpenPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundLightUpdatePacket>(new ClientboundLightUpdatePacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ClientboundMerchantOffersPacket>(new ClientboundMerchantOffersPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundMoveEntityPacket>(new ClientboundMoveEntityPacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ClientboundOpenBookPacket>(new ClientboundOpenBookPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
                    break;
                case 0x32:
                    return std::shared_ptr<ClientboundPlayerCombatPacket>(new ClientboundPlayerCombatPacket);
                    break;
                case 0x33:
                    return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
                    break;
                case 0x34:
                    return std::shared_ptr<ClientboundPlayerLookAtPacket>(new ClientboundPlayerLookAtPacket);
                    break;
                case 0x35:
                    return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
                    break;
                case 0x36:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x37:
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
                case 0x3A:
                    return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
                    break;
                case 0x3B:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x3C:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundSetBorderPacket>(new ClientboundSetBorderPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
                    break;
                case 0x40:
                    return std::shared_ptr<ClientboundSetChunkCacheCenterPacket>(new ClientboundSetChunkCacheCenterPacket);
                    break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetChunkCacheRadiusPacket>(new ClientboundSetChunkCacheRadiusPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
                    break;
                case 0x4F:
                    return std::shared_ptr<ClientboundSetTitlesPacket>(new ClientboundSetTitlesPacket);
                    break;
                case 0x50:
                    return std::shared_ptr<ClientboundSoundEntityPacket>(new ClientboundSoundEntityPacket);
                    break;
                case 0x51:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x52:
                    return std::shared_ptr<ClientboundStopSoundPacket>(new ClientboundStopSoundPacket);
                    break;
                case 0x53:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x54:
                    return std::shared_ptr<ClientboundTagQueryPacket>(new ClientboundTagQueryPacket);
                    break;
                case 0x55:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
                case 0x56:
                    return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
                    break;
                case 0x57:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x58:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x59:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
                case 0x5A:
                    return std::shared_ptr<ClientboundUpdateRecipesPacket>(new ClientboundUpdateRecipesPacket);
                    break;
                case 0x5B:
                    return std::shared_ptr<ClientboundUpdateTagsPacket>(new ClientboundUpdateTagsPacket);
                    break;
#if PROTOCOL_VERSION > 493
                case 0x5C:
                    return std::shared_ptr<ClientboundBlockBreakAckPacket>(new ClientboundBlockBreakAckPacket);
                    break;
#endif
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddGlobalEntityPacket>(new ClientboundAddGlobalEntityPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
				case 0x08:
					return std::shared_ptr<ClientboundBlockBreakAckPacket>(new ClientboundBlockBreakAckPacket);
					break;
                case 0x09:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
				case 0x0C:
					return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
					break;
                case 0x0D:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
				case 0x0E:
					return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
					break;
				case 0x0F:
					return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
					break;
				case 0x10:
					return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
					break;
                case 0x11:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundCommandsPacket>(new ClientboundCommandsPacket);
                    break;
				case 0x13:
					return std::shared_ptr<ClientboundContainerAckPacket>(new ClientboundContainerAckPacket);
					break;
                case 0x14:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
				case 0x15:
					return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
					break;
                case 0x16:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
				case 0x17:
					return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
					break;
                case 0x18:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
				case 0x1B:
					return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
					break;
                case 0x1C:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
				case 0x1E:
					return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
					break;
                case 0x1F:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundHorseScreenOpenPacket>(new ClientboundHorseScreenOpenPacket);
                    break;
				case 0x21:
					return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
					break;
				case 0x22:
					return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
					break;
                case 0x23:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
				case 0x25:
					return std::shared_ptr<ClientboundLightUpdatePacket>(new ClientboundLightUpdatePacket);
					break;
				case 0x26:
					return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
					break;
                case 0x27:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMerchantOffersPacket>(new ClientboundMerchantOffersPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
				case 0x2C:
					return std::shared_ptr<ClientboundMoveEntityPacket>(new ClientboundMoveEntityPacket);
					break;
                case 0x2D:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundOpenBookPacket>(new ClientboundOpenBookPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
				case 0x32:
					return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
					break;
                case 0x33:
                    return std::shared_ptr<ClientboundPlayerCombatPacket>(new ClientboundPlayerCombatPacket);
                    break;
				case 0x34:
					return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
					break;
                case 0x35:
                    return std::shared_ptr<ClientboundPlayerLookAtPacket>(new ClientboundPlayerLookAtPacket);
                    break;
				case 0x36:
					return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
					break;
                case 0x37:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x3A:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
				case 0x3B:
					return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
					break;
                case 0x3C:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundSetBorderPacket>(new ClientboundSetBorderPacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
				case 0x40:
					return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
					break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetChunkCacheCenterPacket>(new ClientboundSetChunkCacheCenterPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetChunkCacheRadiusPacket>(new ClientboundSetChunkCacheRadiusPacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
				case 0x4F:
					return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
					break;
                case 0x50:
                    return std::shared_ptr<ClientboundSetTitlesPacket>(new ClientboundSetTitlesPacket);
                    break;
                case 0x51:
                    return std::shared_ptr<ClientboundSoundEntityPacket>(new ClientboundSoundEntityPacket);
                    break;
                case 0x52:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x53:
                    return std::shared_ptr<ClientboundStopSoundPacket>(new ClientboundStopSoundPacket);
                    break;
                case 0x54:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x55:
                    return std::shared_ptr<ClientboundTagQueryPacket>(new ClientboundTagQueryPacket);
                    break;
                case 0x56:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
				case 0x57:
					return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
					break;
                case 0x58:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x59:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x5A:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
                case 0x5B:
                    return std::shared_ptr<ClientboundUpdateRecipesPacket>(new ClientboundUpdateRecipesPacket);
                    break;
                case 0x5C:
                    return std::shared_ptr<ClientboundUpdateTagsPacket>(new ClientboundUpdateTagsPacket);
                    break;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 // 1.16.0 or 1.16.1
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundBlockBreakAckPacket>(new ClientboundBlockBreakAckPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ClientboundCommandsPacket>(new ClientboundCommandsPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundContainerAckPacket>(new ClientboundContainerAckPacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ClientboundHorseScreenOpenPacket>(new ClientboundHorseScreenOpenPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundLightUpdatePacket>(new ClientboundLightUpdatePacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ClientboundMerchantOffersPacket>(new ClientboundMerchantOffersPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundMoveEntityPacket>(new ClientboundMoveEntityPacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ClientboundOpenBookPacket>(new ClientboundOpenBookPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
                    break;
                case 0x32:
                    return std::shared_ptr<ClientboundPlayerCombatPacket>(new ClientboundPlayerCombatPacket);
                    break;
                case 0x33:
                    return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
                    break;
                case 0x34:
                    return std::shared_ptr<ClientboundPlayerLookAtPacket>(new ClientboundPlayerLookAtPacket);
                    break;
                case 0x35:
                    return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
                    break;
                case 0x36:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x37:
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
                case 0x3A:
                    return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
                    break;
                case 0x3B:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x3C:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundSetBorderPacket>(new ClientboundSetBorderPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
                    break;
                case 0x40:
                    return std::shared_ptr<ClientboundSetChunkCacheCenterPacket>(new ClientboundSetChunkCacheCenterPacket);
                    break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetChunkCacheRadiusPacket>(new ClientboundSetChunkCacheRadiusPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
                    break;
                case 0x4F:
                    return std::shared_ptr<ClientboundSetTitlesPacket>(new ClientboundSetTitlesPacket);
                    break;
                case 0x50:
                    return std::shared_ptr<ClientboundSoundEntityPacket>(new ClientboundSoundEntityPacket);
                    break;
                case 0x51:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x52:
                    return std::shared_ptr<ClientboundStopSoundPacket>(new ClientboundStopSoundPacket);
                    break;
                case 0x53:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x54:
                    return std::shared_ptr<ClientboundTagQueryPacket>(new ClientboundTagQueryPacket);
                    break;
                case 0x55:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
                case 0x56:
                    return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
                    break;
                case 0x57:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x58:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x59:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
                case 0x5A:
                    return std::shared_ptr<ClientboundUpdateRecipesPacket>(new ClientboundUpdateRecipesPacket);
                    break;
                case 0x5B:
                    return std::shared_ptr<ClientboundUpdateTagsPacket>(new ClientboundUpdateTagsPacket);
                    break;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundBlockBreakAckPacket>(new ClientboundBlockBreakAckPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ClientboundCommandsPacket>(new ClientboundCommandsPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ClientboundContainerAckPacket>(new ClientboundContainerAckPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ClientboundHorseScreenOpenPacket>(new ClientboundHorseScreenOpenPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ClientboundLightUpdatePacket>(new ClientboundLightUpdatePacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ClientboundMerchantOffersPacket>(new ClientboundMerchantOffersPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundMoveEntityPacket>(new ClientboundMoveEntityPacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ClientboundOpenBookPacket>(new ClientboundOpenBookPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundPlayerCombatPacket>(new ClientboundPlayerCombatPacket);
                    break;
                case 0x32:
                    return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
                    break;
                case 0x33:
                    return std::shared_ptr<ClientboundPlayerLookAtPacket>(new ClientboundPlayerLookAtPacket);
                    break;
                case 0x34:
                    return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
                    break;
                case 0x35:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x36:
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
                    break;
                case 0x37:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
                    break;
                case 0x3A:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x3B:
                    return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
                    break;
                case 0x3C:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundSetBorderPacket>(new ClientboundSetBorderPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
                    break;
                case 0x40:
                    return std::shared_ptr<ClientboundSetChunkCacheCenterPacket>(new ClientboundSetChunkCacheCenterPacket);
                    break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetChunkCacheRadiusPacket>(new ClientboundSetChunkCacheRadiusPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
                    break;
                case 0x4F:
                    return std::shared_ptr<ClientboundSetTitlesPacket>(new ClientboundSetTitlesPacket);
                    break;
                case 0x50:
                    return std::shared_ptr<ClientboundSoundEntityPacket>(new ClientboundSoundEntityPacket);
                    break;
                case 0x51:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x52:
                    return std::shared_ptr<ClientboundStopSoundPacket>(new ClientboundStopSoundPacket);
                    break;
                case 0x53:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x54:
                    return std::shared_ptr<ClientboundTagQueryPacket>(new ClientboundTagQueryPacket);
                    break;
                case 0x55:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
                case 0x56:
                    return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
                    break;
                case 0x57:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x58:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x59:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
                case 0x5A:
                    return std::shared_ptr<ClientboundUpdateRecipesPacket>(new ClientboundUpdateRecipesPacket);
                    break;
                case 0x5B:
                    return std::shared_ptr<ClientboundUpdateTagsPacket>(new ClientboundUpdateTagsPacket);
                    break;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
                case 0x00:
                    return std::shared_ptr<ClientboundAddEntityPacket>(new ClientboundAddEntityPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ClientboundAddExperienceOrbPacket>(new ClientboundAddExperienceOrbPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ClientboundAddMobPacket>(new ClientboundAddMobPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ClientboundAddPaintingPacket>(new ClientboundAddPaintingPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ClientboundAddPlayerPacket>(new ClientboundAddPlayerPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ClientboundAddVibrationSignalPacket>(new ClientboundAddVibrationSignalPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ClientboundAnimatePacket>(new ClientboundAnimatePacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ClientboundAwardStatsPacket>(new ClientboundAwardStatsPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ClientboundBlockBreakAckPacket>(new ClientboundBlockBreakAckPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ClientboundBlockDestructionPacket>(new ClientboundBlockDestructionPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ClientboundBlockEntityDataPacket>(new ClientboundBlockEntityDataPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ClientboundBlockEventPacket>(new ClientboundBlockEventPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ClientboundBlockUpdatePacket>(new ClientboundBlockUpdatePacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ClientboundBossEventPacket>(new ClientboundBossEventPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ClientboundChangeDifficultyPacket>(new ClientboundChangeDifficultyPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ClientboundChatPacket>(new ClientboundChatPacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ClientboundClearTitlesPacket>(new ClientboundClearTitlesPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ClientboundCommandSuggestionsPacket>(new ClientboundCommandSuggestionsPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ClientboundCommandsPacket>(new ClientboundCommandsPacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ClientboundContainerClosePacket>(new ClientboundContainerClosePacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ClientboundContainerSetContentPacket>(new ClientboundContainerSetContentPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ClientboundContainerSetDataPacket>(new ClientboundContainerSetDataPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ClientboundContainerSetSlotPacket>(new ClientboundContainerSetSlotPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ClientboundCooldownPacket>(new ClientboundCooldownPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ClientboundCustomPayloadPacket>(new ClientboundCustomPayloadPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ClientboundCustomSoundPacket>(new ClientboundCustomSoundPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ClientboundDisconnectPacket>(new ClientboundDisconnectPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ClientboundEntityEventPacket>(new ClientboundEntityEventPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ClientboundExplodePacket>(new ClientboundExplodePacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ClientboundForgetLevelChunkPacket>(new ClientboundForgetLevelChunkPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ClientboundGameEventPacket>(new ClientboundGameEventPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ClientboundHorseScreenOpenPacket>(new ClientboundHorseScreenOpenPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ClientboundInitializeBorderPacket>(new ClientboundInitializeBorderPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ClientboundKeepAlivePacket>(new ClientboundKeepAlivePacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ClientboundLevelChunkPacket>(new ClientboundLevelChunkPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ClientboundLevelEventPacket>(new ClientboundLevelEventPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ClientboundLevelParticlesPacket>(new ClientboundLevelParticlesPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ClientboundLightUpdatePacket>(new ClientboundLightUpdatePacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ClientboundLoginPacket>(new ClientboundLoginPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ClientboundMapItemDataPacket>(new ClientboundMapItemDataPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ClientboundMerchantOffersPacket>(new ClientboundMerchantOffersPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ClientboundMoveEntityPacketPos>(new ClientboundMoveEntityPacketPos);
                    break;
                case 0x2A:
                    return std::shared_ptr<ClientboundMoveEntityPacketPosRot>(new ClientboundMoveEntityPacketPosRot);
                    break;
                case 0x2B:
                    return std::shared_ptr<ClientboundMoveEntityPacketRot>(new ClientboundMoveEntityPacketRot);
                    break;
                case 0x2C:
                    return std::shared_ptr<ClientboundMoveVehiclePacket>(new ClientboundMoveVehiclePacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ClientboundOpenBookPacket>(new ClientboundOpenBookPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ClientboundOpenScreenPacket>(new ClientboundOpenScreenPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ClientboundOpenSignEditorPacket>(new ClientboundOpenSignEditorPacket);
                    break;
                case 0x30:
                    return std::shared_ptr<ClientboundPingPacket>(new ClientboundPingPacket);
                    break;
                case 0x31:
                    return std::shared_ptr<ClientboundPlaceGhostRecipePacket>(new ClientboundPlaceGhostRecipePacket);
                    break;
                case 0x32:
                    return std::shared_ptr<ClientboundPlayerAbilitiesPacket>(new ClientboundPlayerAbilitiesPacket);
                    break;
                case 0x33:
                    return std::shared_ptr<ClientboundPlayerCombatEndPacket>(new ClientboundPlayerCombatEndPacket);
                    break;
                case 0x34:
                    return std::shared_ptr<ClientboundPlayerCombatEnterPacket>(new ClientboundPlayerCombatEnterPacket);
                    break;
                case 0x35:
                    return std::shared_ptr<ClientboundPlayerCombatKillPacket>(new ClientboundPlayerCombatKillPacket);
                    break;
                case 0x36:
                    return std::shared_ptr<ClientboundPlayerInfoPacket>(new ClientboundPlayerInfoPacket);
                    break;
                case 0x37:
                    return std::shared_ptr<ClientboundPlayerLookAtPacket>(new ClientboundPlayerLookAtPacket);
                    break;
                case 0x38:
                    return std::shared_ptr<ClientboundPlayerPositionPacket>(new ClientboundPlayerPositionPacket);
                    break;
                case 0x39:
                    return std::shared_ptr<ClientboundRecipePacket>(new ClientboundRecipePacket);
                    break;
                case 0x3A:
#if PROTOCOL_VERSION < 756
                    return std::shared_ptr<ClientboundRemoveEntityPacket>(new ClientboundRemoveEntityPacket);
#else
                    return std::shared_ptr<ClientboundRemoveEntitiesPacket>(new ClientboundRemoveEntitiesPacket);
#endif
                    break;
                case 0x3B:
                    return std::shared_ptr<ClientboundRemoveMobEffectPacket>(new ClientboundRemoveMobEffectPacket);
                    break;
                case 0x3C:
                    return std::shared_ptr<ClientboundResourcePackPacket>(new ClientboundResourcePackPacket);
                    break;
                case 0x3D:
                    return std::shared_ptr<ClientboundRespawnPacket>(new ClientboundRespawnPacket);
                    break;
                case 0x3E:
                    return std::shared_ptr<ClientboundRotateHeadPacket>(new ClientboundRotateHeadPacket);
                    break;
                case 0x3F:
                    return std::shared_ptr<ClientboundSectionBlocksUpdatePacket>(new ClientboundSectionBlocksUpdatePacket);
                    break;
                case 0x40:
                    return std::shared_ptr<ClientboundSelectAdvancementsTabPacket>(new ClientboundSelectAdvancementsTabPacket);
                    break;
                case 0x41:
                    return std::shared_ptr<ClientboundSetActionBarTextPacket>(new ClientboundSetActionBarTextPacket);
                    break;
                case 0x42:
                    return std::shared_ptr<ClientboundSetBorderCenterPacket>(new ClientboundSetBorderCenterPacket);
                    break;
                case 0x43:
                    return std::shared_ptr<ClientboundSetBorderLerpSizePacket>(new ClientboundSetBorderLerpSizePacket);
                    break;
                case 0x44:
                    return std::shared_ptr<ClientboundSetBorderSizePacket>(new ClientboundSetBorderSizePacket);
                    break;
                case 0x45:
                    return std::shared_ptr<ClientboundSetBorderWarningDelayPacket>(new ClientboundSetBorderWarningDelayPacket);
                    break;
                case 0x46:
                    return std::shared_ptr<ClientboundSetBorderWarningDistancePacket>(new ClientboundSetBorderWarningDistancePacket);
                    break;
                case 0x47:
                    return std::shared_ptr<ClientboundSetCameraPacket>(new ClientboundSetCameraPacket);
                    break;
                case 0x48:
                    return std::shared_ptr<ClientboundSetCarriedItemPacket>(new ClientboundSetCarriedItemPacket);
                    break;
                case 0x49:
                    return std::shared_ptr<ClientboundSetChunkCacheCenterPacket>(new ClientboundSetChunkCacheCenterPacket);
                    break;
                case 0x4A:
                    return std::shared_ptr<ClientboundSetChunkCacheRadiusPacket>(new ClientboundSetChunkCacheRadiusPacket);
                    break;
                case 0x4B:
                    return std::shared_ptr<ClientboundSetDefaultSpawnPositionPacket>(new ClientboundSetDefaultSpawnPositionPacket);
                    break;
                case 0x4C:
                    return std::shared_ptr<ClientboundSetDisplayObjectivePacket>(new ClientboundSetDisplayObjectivePacket);
                    break;
                case 0x4D:
                    return std::shared_ptr<ClientboundSetEntityDataPacket>(new ClientboundSetEntityDataPacket);
                    break;
                case 0x4E:
                    return std::shared_ptr<ClientboundSetEntityLinkPacket>(new ClientboundSetEntityLinkPacket);
                    break;
                case 0x4F:
                    return std::shared_ptr<ClientboundSetEntityMotionPacket>(new ClientboundSetEntityMotionPacket);
                    break;
                case 0x50:
                    return std::shared_ptr<ClientboundSetEquipmentPacket>(new ClientboundSetEquipmentPacket);
                    break;
                case 0x51:
                    return std::shared_ptr<ClientboundSetExperiencePacket>(new ClientboundSetExperiencePacket);
                    break;
                case 0x52:
                    return std::shared_ptr<ClientboundSetHealthPacket>(new ClientboundSetHealthPacket);
                    break;
                case 0x53:
                    return std::shared_ptr<ClientboundSetObjectivePacket>(new ClientboundSetObjectivePacket);
                    break;
                case 0x54:
                    return std::shared_ptr<ClientboundSetPassengersPacket>(new ClientboundSetPassengersPacket);
                    break;
                case 0x55:
                    return std::shared_ptr<ClientboundSetPlayerTeamPacket>(new ClientboundSetPlayerTeamPacket);
                    break;
                case 0x56:
                    return std::shared_ptr<ClientboundSetScorePacket>(new ClientboundSetScorePacket);
                    break;
                case 0x57:
                    return std::shared_ptr<ClientboundSetSubtitleTextPacket>(new ClientboundSetSubtitleTextPacket);
                    break;
                case 0x58:
                    return std::shared_ptr<ClientboundSetTimePacket>(new ClientboundSetTimePacket);
                    break;
                case 0x59:
                    return std::shared_ptr<ClientboundSetTitleTextPacket>(new ClientboundSetTitleTextPacket);
                    break;
                case 0x5A:
                    return std::shared_ptr<ClientboundSetTitlesAnimationPacket>(new ClientboundSetTitlesAnimationPacket);
                    break;
                case 0x5B:
                    return std::shared_ptr<ClientboundSoundEntityPacket>(new ClientboundSoundEntityPacket);
                    break;
                case 0x5C:
                    return std::shared_ptr<ClientboundSoundPacket>(new ClientboundSoundPacket);
                    break;
                case 0x5D:
                    return std::shared_ptr<ClientboundStopSoundPacket>(new ClientboundStopSoundPacket);
                    break;
                case 0x5E:
                    return std::shared_ptr<ClientboundTabListPacket>(new ClientboundTabListPacket);
                    break;
                case 0x5F:
                    return std::shared_ptr<ClientboundTagQueryPacket>(new ClientboundTagQueryPacket);
                    break;
                case 0x60:
                    return std::shared_ptr<ClientboundTakeItemEntityPacket>(new ClientboundTakeItemEntityPacket);
                    break;
                case 0x61:
                    return std::shared_ptr<ClientboundTeleportEntityPacket>(new ClientboundTeleportEntityPacket);
                    break;
                case 0x62:
                    return std::shared_ptr<ClientboundUpdateAdvancementsPacket>(new ClientboundUpdateAdvancementsPacket);
                    break;
                case 0x63:
                    return std::shared_ptr<ClientboundUpdateAttributesPacket>(new ClientboundUpdateAttributesPacket);
                    break;
                case 0x64:
                    return std::shared_ptr<ClientboundUpdateMobEffectPacket>(new ClientboundUpdateMobEffectPacket);
                    break;
                case 0x65:
                    return std::shared_ptr<ClientboundUpdateRecipesPacket>(new ClientboundUpdateRecipesPacket);
                    break;
                case 0x66:
                    return std::shared_ptr<ClientboundUpdateTagsPacket>(new ClientboundUpdateTagsPacket);
                    break;
#else
                #error "Protocol version not implemented"
#endif
                default:
                    return nullptr;
                    break;
                }
            default:
                return nullptr;
                break;
            }
        }

        static std::shared_ptr<Message> CreateMessageServerbound(const int id, const ConnectionState state)
        {
            switch (state)
            {
            case ConnectionState::None:
                switch (id)
                {
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Handshake:
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<ServerboundClientIntentionPacket>(new ServerboundClientIntentionPacket);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Status:
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<ServerboundStatusRequestPacket>(new ServerboundStatusRequestPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundPingRequestPacket>(new ServerboundPingRequestPacket);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Login:
                switch (id)
                {
                case 0x00:
                    return std::shared_ptr<ServerboundHelloPacket>(new ServerboundHelloPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundKeyPacket>(new ServerboundKeyPacket);
                    break;
                default:
                    return nullptr;
                    break;
                }
                break;
            case ConnectionState::Play:
                switch (id)
                {
#if PROTOCOL_VERSION == 340 // 1.12.2
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundContainerAckPacket>(new ServerboundContainerAckPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundEnchantItemPacket>(new ServerboundEnchantItemPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundMovePlayerPacket>(new ServerboundMovePlayerPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundRecipeBookUpdatePacket>(new ServerboundRecipeBookUpdatePacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundBlockEntityTagQuery>(new ServerboundBlockEntityTagQuery);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundContainerAckPacket>(new ServerboundContainerAckPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundEnchantItemPacket>(new ServerboundEnchantItemPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundEditBookPacket>(new ServerboundEditBookPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundEntityTagQuery>(new ServerboundEntityTagQuery);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundMovePlayerPacket>(new ServerboundMovePlayerPacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundPickItemPacket>(new ServerboundPickItemPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundRecipeBookUpdatePacket>(new ServerboundRecipeBookUpdatePacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundRenameItemPacket>(new ServerboundRenameItemPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundSelectTradePacket>(new ServerboundSelectTradePacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundSetBeaconPacket>(new ServerboundSetBeaconPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ServerboundSetCommandBlockPacket>(new ServerboundSetCommandBlockPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ServerboundSetCommandMinecartPacket>(new ServerboundSetCommandMinecartPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ServerboundSetStructureBlockPacket>(new ServerboundSetStructureBlockPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundBlockEntityTagQuery>(new ServerboundBlockEntityTagQuery);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChangeDifficultyPacket>(new ServerboundChangeDifficultyPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundContainerAckPacket>(new ServerboundContainerAckPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerButtonClickPacket>(new ServerboundContainerButtonClickPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundEditBookPacket>(new ServerboundEditBookPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundEntityTagQuery>(new ServerboundEntityTagQuery);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundLockDifficultyPacket>(new ServerboundLockDifficultyPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundMovePlayerPacket>(new ServerboundMovePlayerPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundPickItemPacket>(new ServerboundPickItemPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundRecipeBookUpdatePacket>(new ServerboundRecipeBookUpdatePacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundRenameItemPacket>(new ServerboundRenameItemPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ServerboundSelectTradePacket>(new ServerboundSelectTradePacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ServerboundSetBeaconPacket>(new ServerboundSetBeaconPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ServerboundSetCommandBlockPacket>(new ServerboundSetCommandBlockPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ServerboundSetCommandMinecartPacket>(new ServerboundSetCommandMinecartPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ServerboundSetJigsawBlockPacket>(new ServerboundSetJigsawBlockPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ServerboundSetStructureBlockPacket>(new ServerboundSetStructureBlockPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundBlockEntityTagQuery>(new ServerboundBlockEntityTagQuery);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChangeDifficultyPacket>(new ServerboundChangeDifficultyPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundContainerAckPacket>(new ServerboundContainerAckPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerButtonClickPacket>(new ServerboundContainerButtonClickPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundEditBookPacket>(new ServerboundEditBookPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundEntityTagQuery>(new ServerboundEntityTagQuery);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundLockDifficultyPacket>(new ServerboundLockDifficultyPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundMovePlayerPacket>(new ServerboundMovePlayerPacket);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundPickItemPacket>(new ServerboundPickItemPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundRecipeBookUpdatePacket>(new ServerboundRecipeBookUpdatePacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundRenameItemPacket>(new ServerboundRenameItemPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ServerboundSelectTradePacket>(new ServerboundSelectTradePacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ServerboundSetBeaconPacket>(new ServerboundSetBeaconPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ServerboundSetCommandBlockPacket>(new ServerboundSetCommandBlockPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ServerboundSetCommandMinecartPacket>(new ServerboundSetCommandMinecartPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ServerboundSetJigsawBlockPacket>(new ServerboundSetJigsawBlockPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ServerboundSetStructureBlockPacket>(new ServerboundSetStructureBlockPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 // 1.16.0 or 1.16.1
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundBlockEntityTagQuery>(new ServerboundBlockEntityTagQuery);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChangeDifficultyPacket>(new ServerboundChangeDifficultyPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundContainerAckPacket>(new ServerboundContainerAckPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerButtonClickPacket>(new ServerboundContainerButtonClickPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundEditBookPacket>(new ServerboundEditBookPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundEntityTagQuery>(new ServerboundEntityTagQuery);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundJigsawGeneratePacket>(new ServerboundJigsawGeneratePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundLockDifficultyPacket>(new ServerboundLockDifficultyPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundMovePlayerPacket>(new ServerboundMovePlayerPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundPickItemPacket>(new ServerboundPickItemPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundRecipeBookUpdatePacket>(new ServerboundRecipeBookUpdatePacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundRenameItemPacket>(new ServerboundRenameItemPacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ServerboundSelectTradePacket>(new ServerboundSelectTradePacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ServerboundSetBeaconPacket>(new ServerboundSetBeaconPacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ServerboundSetCommandBlockPacket>(new ServerboundSetCommandBlockPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ServerboundSetCommandMinecartPacket>(new ServerboundSetCommandMinecartPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ServerboundSetJigsawBlockPacket>(new ServerboundSetJigsawBlockPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ServerboundSetStructureBlockPacket>(new ServerboundSetStructureBlockPacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundBlockEntityTagQuery>(new ServerboundBlockEntityTagQuery);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChangeDifficultyPacket>(new ServerboundChangeDifficultyPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundContainerAckPacket>(new ServerboundContainerAckPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerButtonClickPacket>(new ServerboundContainerButtonClickPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundEditBookPacket>(new ServerboundEditBookPacket);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundEntityTagQuery>(new ServerboundEntityTagQuery);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundJigsawGeneratePacket>(new ServerboundJigsawGeneratePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundLockDifficultyPacket>(new ServerboundLockDifficultyPacket);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundMovePlayerPacket>(new ServerboundMovePlayerPacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundPickItemPacket>(new ServerboundPickItemPacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundRecipeBookChangeSettingsPacket>(new ServerboundRecipeBookChangeSettingsPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundRecipeBookSeenRecipePacket>(new ServerboundRecipeBookSeenRecipePacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundRenameItemPacket>(new ServerboundRenameItemPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ServerboundSelectTradePacket>(new ServerboundSelectTradePacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ServerboundSetBeaconPacket>(new ServerboundSetBeaconPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ServerboundSetCommandBlockPacket>(new ServerboundSetCommandBlockPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ServerboundSetCommandMinecartPacket>(new ServerboundSetCommandMinecartPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ServerboundSetJigsawBlockPacket>(new ServerboundSetJigsawBlockPacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ServerboundSetStructureBlockPacket>(new ServerboundSetStructureBlockPacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
                case 0x00:
                    return std::shared_ptr<ServerboundAcceptTeleportationPacket>(new ServerboundAcceptTeleportationPacket);
                    break;
                case 0x01:
                    return std::shared_ptr<ServerboundBlockEntityTagQuery>(new ServerboundBlockEntityTagQuery);
                    break;
                case 0x02:
                    return std::shared_ptr<ServerboundChangeDifficultyPacket>(new ServerboundChangeDifficultyPacket);
                    break;
                case 0x03:
                    return std::shared_ptr<ServerboundChatPacket>(new ServerboundChatPacket);
                    break;
                case 0x04:
                    return std::shared_ptr<ServerboundClientCommandPacket>(new ServerboundClientCommandPacket);
                    break;
                case 0x05:
                    return std::shared_ptr<ServerboundClientInformationPacket>(new ServerboundClientInformationPacket);
                    break;
                case 0x06:
                    return std::shared_ptr<ServerboundCommandSuggestionPacket>(new ServerboundCommandSuggestionPacket);
                    break;
                case 0x07:
                    return std::shared_ptr<ServerboundContainerButtonClickPacket>(new ServerboundContainerButtonClickPacket);
                    break;
                case 0x08:
                    return std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);
                    break;
                case 0x09:
                    return std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
                    break;
                case 0x0A:
                    return std::shared_ptr<ServerboundCustomPayloadPacket>(new ServerboundCustomPayloadPacket);
                    break;
                case 0x0B:
                    return std::shared_ptr<ServerboundEditBookPacket>(new ServerboundEditBookPacket);
                    break;
                case 0x0C:
                    return std::shared_ptr<ServerboundEntityTagQuery>(new ServerboundEntityTagQuery);
                    break;
                case 0x0D:
                    return std::shared_ptr<ServerboundInteractPacket>(new ServerboundInteractPacket);
                    break;
                case 0x0E:
                    return std::shared_ptr<ServerboundJigsawGeneratePacket>(new ServerboundJigsawGeneratePacket);
                    break;
                case 0x0F:
                    return std::shared_ptr<ServerboundKeepAlivePacket>(new ServerboundKeepAlivePacket);
                    break;
                case 0x10:
                    return std::shared_ptr<ServerboundLockDifficultyPacket>(new ServerboundLockDifficultyPacket);
                    break;
                case 0x11:
                    return std::shared_ptr<ServerboundMovePlayerPacketPos>(new ServerboundMovePlayerPacketPos);
                    break;
                case 0x12:
                    return std::shared_ptr<ServerboundMovePlayerPacketPosRot>(new ServerboundMovePlayerPacketPosRot);
                    break;
                case 0x13:
                    return std::shared_ptr<ServerboundMovePlayerPacketRot>(new ServerboundMovePlayerPacketRot);
                    break;
                case 0x14:
                    return std::shared_ptr<ServerboundMovePlayerPacketStatusOnly>(new ServerboundMovePlayerPacketStatusOnly);
                    break;
                case 0x15:
                    return std::shared_ptr<ServerboundMoveVehiclePacket>(new ServerboundMoveVehiclePacket);
                    break;
                case 0x16:
                    return std::shared_ptr<ServerboundPaddleBoatPacket>(new ServerboundPaddleBoatPacket);
                    break;
                case 0x17:
                    return std::shared_ptr<ServerboundPickItemPacket>(new ServerboundPickItemPacket);
                    break;
                case 0x18:
                    return std::shared_ptr<ServerboundPlaceRecipePacket>(new ServerboundPlaceRecipePacket);
                    break;
                case 0x19:
                    return std::shared_ptr<ServerboundPlayerAbilitiesPacket>(new ServerboundPlayerAbilitiesPacket);
                    break;
                case 0x1A:
                    return std::shared_ptr<ServerboundPlayerActionPacket>(new ServerboundPlayerActionPacket);
                    break;
                case 0x1B:
                    return std::shared_ptr<ServerboundPlayerCommandPacket>(new ServerboundPlayerCommandPacket);
                    break;
                case 0x1C:
                    return std::shared_ptr<ServerboundPlayerInputPacket>(new ServerboundPlayerInputPacket);
                    break;
                case 0x1D:
                    return std::shared_ptr<ServerboundPongPacket>(new ServerboundPongPacket);
                    break;
                case 0x1E:
                    return std::shared_ptr<ServerboundRecipeBookChangeSettingsPacket>(new ServerboundRecipeBookChangeSettingsPacket);
                    break;
                case 0x1F:
                    return std::shared_ptr<ServerboundRecipeBookSeenRecipePacket>(new ServerboundRecipeBookSeenRecipePacket);
                    break;
                case 0x20:
                    return std::shared_ptr<ServerboundRenameItemPacket>(new ServerboundRenameItemPacket);
                    break;
                case 0x21:
                    return std::shared_ptr<ServerboundResourcePackPacket>(new ServerboundResourcePackPacket);
                    break;
                case 0x22:
                    return std::shared_ptr<ServerboundSeenAdvancementsPacket>(new ServerboundSeenAdvancementsPacket);
                    break;
                case 0x23:
                    return std::shared_ptr<ServerboundSelectTradePacket>(new ServerboundSelectTradePacket);
                    break;
                case 0x24:
                    return std::shared_ptr<ServerboundSetBeaconPacket>(new ServerboundSetBeaconPacket);
                    break;
                case 0x25:
                    return std::shared_ptr<ServerboundSetCarriedItemPacket>(new ServerboundSetCarriedItemPacket);
                    break;
                case 0x26:
                    return std::shared_ptr<ServerboundSetCommandBlockPacket>(new ServerboundSetCommandBlockPacket);
                    break;
                case 0x27:
                    return std::shared_ptr<ServerboundSetCommandMinecartPacket>(new ServerboundSetCommandMinecartPacket);
                    break;
                case 0x28:
                    return std::shared_ptr<ServerboundSetCreativeModeSlotPacket>(new ServerboundSetCreativeModeSlotPacket);
                    break;
                case 0x29:
                    return std::shared_ptr<ServerboundSetJigsawBlockPacket>(new ServerboundSetJigsawBlockPacket);
                    break;
                case 0x2A:
                    return std::shared_ptr<ServerboundSetStructureBlockPacket>(new ServerboundSetStructureBlockPacket);
                    break;
                case 0x2B:
                    return std::shared_ptr<ServerboundSignUpdatePacket>(new ServerboundSignUpdatePacket);
                    break;
                case 0x2C:
                    return std::shared_ptr<ServerboundSwingPacket>(new ServerboundSwingPacket);
                    break;
                case 0x2D:
                    return std::shared_ptr<ServerboundTeleportToEntityPacket>(new ServerboundTeleportToEntityPacket);
                    break;
                case 0x2E:
                    return std::shared_ptr<ServerboundUseItemOnPacket>(new ServerboundUseItemOnPacket);
                    break;
                case 0x2F:
                    return std::shared_ptr<ServerboundUseItemPacket>(new ServerboundUseItemPacket);
                    break;
#else
#error "Protocol version not implemented"
#endif
                default:
                    return nullptr;
                    break;
                }
            default:
                return nullptr;
                break;
            }
        }
    };
} //ProtocolCraft
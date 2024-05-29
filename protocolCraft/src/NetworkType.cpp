#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/PrivateTemplates.hpp"

#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/AdvancementDisplay.hpp"
#include "protocolCraft/Types/AdvancementProgress.hpp"
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Types/BlockEntityInfo.hpp"
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#include "protocolCraft/Types/BlockEntityTag.hpp"
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/ChunkBiomeData.hpp"
#include "protocolCraft/Types/ChunkPos.hpp"
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Types/ClientboundLevelChunkPacketData.hpp"
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Types/ClientboundLightUpdatePacketData.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ClientInformation.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/CommonPlayerSpawnInfo.hpp"
#endif
#include "protocolCraft/Types/CriterionProgress.hpp"
#include "protocolCraft/Types/EntityModifierData.hpp"
#include "protocolCraft/Types/EntityProperty.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GlobalPos.hpp"
#endif
#include "protocolCraft/Types/Identifier.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/KnownPack.hpp"
#endif
#include "protocolCraft/Types/MapDecoration.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/PackedRegistryEntry.hpp"
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Types/PlayerUpdate.hpp"
#endif
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#include "protocolCraft/Types/Record.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/SaltSignature.hpp"
#endif

// Chat
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Types/Chat/ChatMessageContent.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Chat/ChatSender.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"
#include "protocolCraft/Types/Chat/FilterMask.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/NumberFormat.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/PlayerChatMessage.hpp"
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/SignedMessageBody.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"
#endif

// GameProfile
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

// Items
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Item/ItemCost.hpp"
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#include "protocolCraft/Types/Item/MerchantOffer.hpp"
#endif
#include "protocolCraft/Types/Item/Slot.hpp"

// Recipes
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#endif
#include "protocolCraft/Types/Recipes/RecipeBookSettings.hpp"

// Sound
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

// Vibrations
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Vibrations/BlockPositionSource.hpp"
#include "protocolCraft/Types/Vibrations/EntityPositionSource.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"
#endif

namespace ProtocolCraft
{
    // All NetworkType auto serializable methods can be defined here
    DEFINE_NETWORK_TYPE(Advancement);
    DEFINE_SERIALIZED_NETWORK_TYPE(AdvancementDisplay);
    DEFINE_NETWORK_TYPE(AdvancementProgress);
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    DEFINE_NETWORK_TYPE(BlockEntityInfo);
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(BlockEntityTag);
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    DEFINE_NETWORK_TYPE(ChunkBiomeData);
    DEFINE_SERIALIZED_NETWORK_TYPE(ChunkPos);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    DEFINE_NETWORK_TYPE(ClientboundLevelChunkPacketData);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    DEFINE_NETWORK_TYPE(ClientboundLightUpdatePacketData);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_NETWORK_TYPE(ClientInformation);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    DEFINE_NETWORK_TYPE(CommonPlayerSpawnInfo);
#endif
    DEFINE_NETWORK_TYPE(CriterionProgress);
    DEFINE_NETWORK_TYPE(EntityModifierData);
    DEFINE_NETWORK_TYPE(EntityProperty);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(GlobalPos);
#endif
    DEFINE_SERIALIZED_NETWORK_TYPE(Identifier);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_NETWORK_TYPE(KnownPack);
#endif
    DEFINE_NETWORK_TYPE(MapDecoration);
    DEFINE_SERIALIZED_NETWORK_TYPE(NetworkPosition);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_NETWORK_TYPE(PackedRegistryEntry);
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_NETWORK_TYPE(PlayerUpdate);
#endif
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
    DEFINE_NETWORK_TYPE(Record);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(SaltSignature);
#endif

    // Chat
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_NETWORK_TYPE(ChatMessageContent);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(ChatSender);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_NETWORK_TYPE(ChatTypeBoundNetwork);
    DEFINE_SERIALIZED_NETWORK_TYPE(FilterMask);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    DEFINE_NETWORK_TYPE(LastSeenMessagesEntry);
#else
    DEFINE_SERIALIZED_NETWORK_TYPE(LastSeenMessagesEntry);
#endif
    DEFINE_NETWORK_TYPE(LastSeenMessagesUpdate);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    DEFINE_SERIALIZED_NETWORK_TYPE(NumberFormat);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_NETWORK_TYPE(PlayerChatMessage);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    DEFINE_NETWORK_TYPE(RemoteChatSessionData);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
    DEFINE_NETWORK_TYPE(SignedMessageBody);
    DEFINE_NETWORK_TYPE(SignedMessageHeader);
#endif

    // GameProfile
    DEFINE_NETWORK_TYPE(GameProfileProperty);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(GameProfile);
    DEFINE_NETWORK_TYPE(ProfilePublicKey);
#endif

    // Items
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_NETWORK_TYPE(ItemCost);
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    DEFINE_NETWORK_TYPE(MerchantOffer);
#endif
    DEFINE_JSON_NAMES(Slot);

    // Recipes
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(Ingredient);
#endif
    DEFINE_NETWORK_TYPE(RecipeBookSettings);

    // Sound
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    DEFINE_NETWORK_TYPE(SoundEvent);
#endif

    // Vibrations
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_NETWORK_TYPE(BlockPositionSource);
    DEFINE_NETWORK_TYPE(EntityPositionSource);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_JSON_NAMES(VibrationPath);
#endif

}

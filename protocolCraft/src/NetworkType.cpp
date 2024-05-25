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
}

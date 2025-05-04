#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include <map>
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateTagsPacket : public BasePacket<ClientboundUpdateTagsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Tags";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(BlockTags, std::vector<BlockEntityTag>);
        SERIALIZED_FIELD(ItemTags, std::vector<BlockEntityTag>);
        SERIALIZED_FIELD(FluidTags, std::vector<BlockEntityTag>);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(EntityTags, std::vector<BlockEntityTag>);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SERIALIZED_FIELD(Tags, std::map<Identifier, std::vector<BlockEntityTag>>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

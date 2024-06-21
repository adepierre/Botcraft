#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include <map>
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateTagsPacket : public BaseMessage<ClientboundUpdateTagsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Tags";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (std::vector<BlockEntityTag>, std::vector<BlockEntityTag>, std::vector<BlockEntityTag>),
            (BlockTags,                   ItemTags,                    FluidTags)
        );
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (std::vector<BlockEntityTag>, std::vector<BlockEntityTag>, std::vector<BlockEntityTag>, std::vector<BlockEntityTag>),
            (BlockTags,                   ItemTags,                    FluidTags,                   EntityTags)
        );
#else
        DECLARE_FIELDS(
            (std::map<Identifier, std::vector<BlockEntityTag>>),
            (Tags)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(BlockTags);
        GETTER_SETTER(ItemTags);
        GETTER_SETTER(FluidTags);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(EntityTags);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        GETTER_SETTER(Tags);
#endif
    };
} //ProtocolCraft
#endif

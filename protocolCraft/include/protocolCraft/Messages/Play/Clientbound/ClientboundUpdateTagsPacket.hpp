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
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x68;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x6B;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x6A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x6E;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x70;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x74;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x78;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Tags";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS_TYPES(std::vector<BlockEntityTag>, std::vector<BlockEntityTag>, std::vector<BlockEntityTag>);
        DECLARE_FIELDS_NAMES(BlockTags,                   ItemTags,                    FluidTags);
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS_TYPES(std::vector<BlockEntityTag>, std::vector<BlockEntityTag>, std::vector<BlockEntityTag>, std::vector<BlockEntityTag>);
        DECLARE_FIELDS_NAMES(BlockTags,                   ItemTags,                    FluidTags,                   EntityTags);
#else
        DECLARE_FIELDS_TYPES(std::map<Identifier, std::vector<BlockEntityTag>>);
        DECLARE_FIELDS_NAMES(Tags);
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

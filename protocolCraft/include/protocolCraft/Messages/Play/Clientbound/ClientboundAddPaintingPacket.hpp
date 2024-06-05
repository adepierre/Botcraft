#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPaintingPacket : public BaseMessage<ClientboundAddPaintingPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x03;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Add Painting";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS_TYPES(VarInt, UUID, std::string, NetworkPosition, char);
        DECLARE_FIELDS_NAMES(Id_,    Uuid, Title,       Pos,             Direction);
#else
        DECLARE_FIELDS_TYPES(VarInt, UUID, VarInt, NetworkPosition, char);
        DECLARE_FIELDS_NAMES(Id_,    Uuid, Motive, Pos,             Direction);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Uuid);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        GETTER_SETTER(Title);
#else
        GETTER_SETTER(Motive);
#endif
        GETTER_SETTER(Pos);
        GETTER_SETTER(Direction);
    };
} //ProtocolCraft
#endif

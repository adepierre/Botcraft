#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPaintingPacket : public BaseMessage<ClientboundAddPaintingPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Painting";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (VarInt, UUID, std::string, NetworkPosition, char),
            (Id_,    Uuid, Title,       Pos,             Direction)
        );
#else
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, NetworkPosition, char),
            (Id_,    Uuid, Motive, Pos,             Direction)
        );
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

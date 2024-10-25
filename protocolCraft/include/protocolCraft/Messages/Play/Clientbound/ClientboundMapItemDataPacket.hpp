#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/MapDecoration.hpp"

namespace ProtocolCraft
{
    class ClientboundMapItemDataPacket : public BaseMessage<ClientboundMapItemDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Map Item Data";

        DEFINE_CONDITION(HasWidth, GetWidth() > 0);
        SERIALIZED_FIELD(MapId, VarInt);
        SERIALIZED_FIELD(Scale, char);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(TrackingPosition, bool);
        SERIALIZED_FIELD(Decorations, std::vector<MapDecoration>);
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(TrackingPosition, bool);
        SERIALIZED_FIELD(Locked, bool);
        SERIALIZED_FIELD(Decorations, std::vector<MapDecoration>);
#else
        SERIALIZED_FIELD(Locked, bool);
        SERIALIZED_FIELD(Decorations, std::optional<std::vector<MapDecoration>>);
#endif
        SERIALIZED_FIELD(Width, unsigned char);
        SERIALIZED_FIELD(Height, Internal::Conditioned<unsigned char, &THIS::HasWidth>);
        SERIALIZED_FIELD(StartX, Internal::Conditioned<unsigned char, &THIS::HasWidth>);
        SERIALIZED_FIELD(StartZ, Internal::Conditioned<unsigned char, &THIS::HasWidth>);
        SERIALIZED_FIELD(MapColors, Internal::Conditioned<std::vector<unsigned char>, &THIS::HasWidth>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

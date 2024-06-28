#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/MapDecoration.hpp"

namespace ProtocolCraft
{
    class ClientboundMapItemDataPacket : public BaseMessage<ClientboundMapItemDataPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Map Item Data";

        DECLARE_CONDITION(HasWidth, GetWidth() > 0);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (VarInt, char,  bool,             std::vector<MapDecoration>, unsigned char, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<std::vector<unsigned char>, &THIS::HasWidth>),
            (MapId,  Scale, TrackingPosition, Decorations,                Width,         Height,                                                StartX,                                                StartZ,                                                MapColors)
        );
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (VarInt, char,  bool,             bool,   std::vector<MapDecoration>, unsigned char, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<std::vector<unsigned char>, &THIS::HasWidth>),
            (MapId,  Scale, TrackingPosition, Locked, Decorations,                Width,         Height,                                                StartX,                                                StartZ,                                                MapColors)
        );
#else
        DECLARE_FIELDS(
            (VarInt, char,  bool,   std::optional<std::vector<MapDecoration>>, unsigned char, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<unsigned char, &THIS::HasWidth>, Internal::Conditioned<std::vector<unsigned char>, &THIS::HasWidth>),
            (MapId,  Scale, Locked, Decorations,                               Width,         Height,                                                StartX,                                                StartZ,                                                MapColors)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(MapId);
        GETTER_SETTER(Scale);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(TrackingPosition);
#endif
        GETTER_SETTER(Decorations);
        GETTER_SETTER(Width);
        GETTER_SETTER(Height);
        GETTER_SETTER(StartX);
        GETTER_SETTER(StartZ);
        GETTER_SETTER(MapColors);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        GETTER_SETTER(Locked);
#endif
    };
} //ProtocolCraft

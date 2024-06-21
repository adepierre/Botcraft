#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSetJigsawBlockPacket : public BaseMessage<ServerboundSetJigsawBlockPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Jigsaw Block";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (NetworkPosition, Identifier,     Identifier, std::string),
            (Pos,             AttachmentType, TargetPool, FinalState)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (NetworkPosition, Identifier, Identifier, Identifier, std::string, std::string),
            (Pos,             Name_,      Target,     Pool,       FinaleState, Joint)
        );
#else
        DECLARE_FIELDS(
            (NetworkPosition, Identifier, Identifier, Identifier, std::string, std::string, VarInt,            VarInt),
            (Pos,             Name_,      Target,     Pool,       FinaleState, Joint,       SelectionPriority, PlacementPriority)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        GETTER_SETTER(AttachmentType);
        GETTER_SETTER(TargetPool);
        GETTER_SETTER(FinalState);
#endif
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        GETTER_SETTER(Name_);
        GETTER_SETTER(Target);
        GETTER_SETTER(Pool);
        GETTER_SETTER(Joint);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(SelectionPriority);
        GETTER_SETTER(PlacementPriority);
#endif
    };
} //ProtocolCraft
#endif

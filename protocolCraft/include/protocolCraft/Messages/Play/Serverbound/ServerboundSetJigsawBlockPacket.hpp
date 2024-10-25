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

        SERIALIZED_FIELD(Pos, NetworkPosition);
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(AttachmentType, Identifier);
        SERIALIZED_FIELD(TargetPool, Identifier);
        SERIALIZED_FIELD(FinalState, std::string);
#endif
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        SERIALIZED_FIELD(Name_, Identifier);
        SERIALIZED_FIELD(Target, Identifier);
        SERIALIZED_FIELD(Pool, Identifier);
        SERIALIZED_FIELD(FinaleState, std::string);
        SERIALIZED_FIELD(Joint, std::string);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SERIALIZED_FIELD(SelectionPriority, VarInt);
        SERIALIZED_FIELD(PlacementPriority, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

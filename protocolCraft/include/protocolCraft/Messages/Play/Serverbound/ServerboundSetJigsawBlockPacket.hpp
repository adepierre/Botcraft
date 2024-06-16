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
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x33;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Jigsaw Block";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS_TYPES(NetworkPosition, Identifier,     Identifier, std::string);
        DECLARE_FIELDS_NAMES(Pos,             AttachmentType, TargetPool, FinalState);
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS_TYPES(NetworkPosition, Identifier, Identifier, Identifier, std::string, std::string);
        DECLARE_FIELDS_NAMES(Pos,             Name_,      Target,     Pool,       FinaleState, Joint);
#else
        DECLARE_FIELDS_TYPES(NetworkPosition, Identifier, Identifier, Identifier, std::string, std::string, VarInt,            VarInt);
        DECLARE_FIELDS_NAMES(Pos,             Name_,      Target,     Pool,       FinaleState, Joint,       SelectionPriority, PlacementPriority);
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

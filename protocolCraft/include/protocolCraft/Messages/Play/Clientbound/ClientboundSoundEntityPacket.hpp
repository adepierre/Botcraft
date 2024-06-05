#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSoundEntityPacket : public BaseMessage<ClientboundSoundEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x67;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Sound Entity";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS_TYPES(VarInt, VarInt, VarInt, float,  float);
        DECLARE_FIELDS_NAMES(Sound,  Source, Id_,    Volume, Pitch);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(VarInt, VarInt, VarInt, float,  float, long long int);
        DECLARE_FIELDS_NAMES(Sound,  Source, Id_,    Volume, Pitch, Seed);
#else
        DECLARE_FIELDS_TYPES(Holder<SoundEvent>, VarInt, VarInt, float,  float, long long int);
        DECLARE_FIELDS_NAMES(Sound,              Source, Id_,    Volume, Pitch, Seed);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Sound);
        GETTER_SETTER(Source);
        GETTER_SETTER(Id_);
        GETTER_SETTER(Volume);
        GETTER_SETTER(Pitch);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Seed);
#endif
    };
} //ProtocolCraft
#endif

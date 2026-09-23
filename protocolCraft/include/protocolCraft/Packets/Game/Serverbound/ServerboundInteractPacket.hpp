#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
#include "protocolCraft/Types/LpVec3.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundInteractPacket : public BasePacket<ServerboundInteractPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Interact";

#if PROTOCOL_VERSION < 775 /* < 26.1 */
        DEFINE_CONDITION(Action2, GetAction() == 2);
        DEFINE_CONDITION(Action0_2, GetAction() == 0 || GetAction() == 2);
#endif

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(LocationX, Internal::Conditioned<float, &THIS::Action2>);
        SERIALIZED_FIELD(LocationY, Internal::Conditioned<float, &THIS::Action2>);
        SERIALIZED_FIELD(LocationZ, Internal::Conditioned<float, &THIS::Action2>);
#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
        SERIALIZED_FIELD(Hand, Internal::Conditioned<VarInt, &THIS::Action0_2>);
#endif
#else
        SERIALIZED_FIELD(Hand, VarInt);
        SERIALIZED_FIELD(Location, LpVec3);
#endif
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        SERIALIZED_FIELD(UsingSecondaryAction, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

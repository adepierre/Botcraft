#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundInteractPacket : public BasePacket<ServerboundInteractPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Interact";

        DEFINE_CONDITION(Action2, GetAction() == 2);
        DEFINE_CONDITION(Action0_2, GetAction() == 0 || GetAction() == 2);

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(LocationX, Internal::Conditioned<float, &THIS::Action2>);
        SERIALIZED_FIELD(LocationY, Internal::Conditioned<float, &THIS::Action2>);
        SERIALIZED_FIELD(LocationZ, Internal::Conditioned<float, &THIS::Action2>);
        SERIALIZED_FIELD(Hand, Internal::Conditioned<VarInt, &THIS::Action0_2>);
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        SERIALIZED_FIELD(UsingSecondaryAction, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

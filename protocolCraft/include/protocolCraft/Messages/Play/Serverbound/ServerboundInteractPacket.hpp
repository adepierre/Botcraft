#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundInteractPacket : public BaseMessage<ServerboundInteractPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Interact";

        DECLARE_CONDITION(Action2, GetAction() == 2);
        DECLARE_CONDITION(Action0_2, GetAction() == 0 || GetAction() == 2);

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (VarInt,   VarInt, Internal::Conditioned<float, &THIS::Action2>, Internal::Conditioned<float, &THIS::Action2>, Internal::Conditioned<float, &THIS::Action2>, Internal::Conditioned<VarInt, &THIS::Action0_2>),
            (EntityId, Action, LocationX,                                    LocationY,                                    LocationZ,                                    Hand)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   VarInt, Internal::Conditioned<float, &THIS::Action2>, Internal::Conditioned<float, &THIS::Action2>, Internal::Conditioned<float, &THIS::Action2>, Internal::Conditioned<VarInt, &THIS::Action0_2>, bool),
            (EntityId, Action, LocationX,                                    LocationY,                                    LocationZ,                                    Hand,                                            UsingSecondaryAction)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(Action);
        GETTER_SETTER(LocationX);
        GETTER_SETTER(LocationY);
        GETTER_SETTER(LocationZ);
        GETTER_SETTER(Hand);
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        GETTER_SETTER(UsingSecondaryAction);
#endif
    };
} //ProtocolCraft

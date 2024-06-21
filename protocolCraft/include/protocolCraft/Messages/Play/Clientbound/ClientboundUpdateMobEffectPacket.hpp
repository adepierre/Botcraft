#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/NBT/NBT.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateMobEffectPacket : public BaseMessage<ClientboundUpdateMobEffectPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Mob Effect";

#if PROTOCOL_VERSION < 758 /* < 1.18.2 */
        DECLARE_FIELDS(
            (VarInt,   char,     char,            VarInt,              char),
            (EntityId, EffectId, EffectAmplifier, EffectDurationTicks, Flags)
        );
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt,   VarInt,   char,            VarInt,              char),
            (EntityId, EffectId, EffectAmplifier, EffectDurationTicks, Flags)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (VarInt,   VarInt,   char,            VarInt,              char,  std::optional<NBT::UnnamedValue>),
            (EntityId, EffectId, EffectAmplifier, EffectDurationTicks, Flags, FactorData)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   VarInt,   VarInt,          VarInt,              char),
            (EntityId, EffectId, EffectAmplifier, EffectDurationTicks, Flags)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(EffectId);
        GETTER_SETTER(EffectAmplifier);
        GETTER_SETTER(EffectDurationTicks);
        GETTER_SETTER(Flags);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(FactorData);
#endif
    };
} //ProtocolCraft

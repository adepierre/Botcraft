#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/NBT/NBT.hpp"

#include <optional>
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateMobEffectPacket : public BaseMessage<ClientboundUpdateMobEffectPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Mob Effect";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 758 /* < 1.18.2 */
        SERIALIZED_FIELD(EffectId, char);
#else
        SERIALIZED_FIELD(EffectId, VarInt);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(EffectAmplifier, char);
#else
        SERIALIZED_FIELD(EffectAmplifier, VarInt);
#endif
        SERIALIZED_FIELD(EffectDurationTicks, VarInt);
        SERIALIZED_FIELD(Flags, char);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(FactorData, std::optional<NBT::UnnamedValue>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

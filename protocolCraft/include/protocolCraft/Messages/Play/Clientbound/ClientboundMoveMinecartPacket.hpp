#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/MinecartBehaviorMinecartStep.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveMinecartPacket : public BaseMessage<ClientboundMoveMinecartPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Move Minecart";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(LerpSteps, std::vector<MinecartBehaviorMinecartStep>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

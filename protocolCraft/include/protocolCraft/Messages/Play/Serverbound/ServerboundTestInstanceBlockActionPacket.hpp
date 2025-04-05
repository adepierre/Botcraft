#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/TestInstanceBlockEntityData.hpp"

namespace ProtocolCraft
{
    class ServerboundTestInstanceBlockActionPacket : public BaseMessage<ServerboundTestInstanceBlockActionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Test Instance Block Action";

        SERIALIZED_FIELD(BlockPos, NetworkPosition);
        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(Data, TestInstanceBlockEntityData);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

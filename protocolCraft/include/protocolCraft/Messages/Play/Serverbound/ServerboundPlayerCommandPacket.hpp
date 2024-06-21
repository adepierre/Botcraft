#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerCommandPacket : public BaseMessage<ServerboundPlayerCommandPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Command";

        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt),
            (Id_,    Action, Data)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Action);
        GETTER_SETTER(Data);
    };
} //ProtocolCraft

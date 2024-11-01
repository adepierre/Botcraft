#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSelectBundleItemPacket : public BaseMessage<ServerboundSelectBundleItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Select Bundle Item";

        SERIALIZED_FIELD(SlotId, VarInt);
        SERIALIZED_FIELD(SelectedItemIndex, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

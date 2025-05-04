#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundSelectBundleItemPacket : public BasePacket<ServerboundSelectBundleItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Select Bundle Item";

        SERIALIZED_FIELD(SlotId, VarInt);
        SERIALIZED_FIELD(SelectedItemIndex, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

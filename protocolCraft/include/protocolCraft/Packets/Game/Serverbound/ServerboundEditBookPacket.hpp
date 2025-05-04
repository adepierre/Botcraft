#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#if PROTOCOL_VERSION > 755 /* > 1.17 */
#include <vector>
#include <string>
#endif

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundEditBookPacket : public BasePacket<ServerboundEditBookPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Edit Book";

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        SERIALIZED_FIELD(Book, ProtocolCraft::Slot);
        SERIALIZED_FIELD(Signing, bool);
#endif
#if PROTOCOL_VERSION > 393 /* > 1.13 */
        SERIALIZED_FIELD(Slot, VarInt);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        SERIALIZED_FIELD(Pages, std::vector<std::string>);
        SERIALIZED_FIELD(Title, std::optional<std::string>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

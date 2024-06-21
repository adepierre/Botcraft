#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#if PROTOCOL_VERSION > 755 /* > 1.17 */
#include <vector>
#include <string>
#endif

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundEditBookPacket : public BaseMessage<ServerboundEditBookPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Edit Book";

#if PROTOCOL_VERSION < 401 /* < 1.13.1 */
        DECLARE_FIELDS(
            (Slot, bool),
            (Book, Signing)
        );
#elif PROTOCOL_VERSION < 756 /* < 1.17.1 */
        DECLARE_FIELDS(
            (Slot, bool,    VarInt),
            (Book, Signing, Slot)
        );
#else
        DECLARE_FIELDS(
            (VarInt, std::vector<std::string>, std::optional<std::string>),
            (Slot,   Pages,                    Title)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        GETTER_SETTER(Book);
        GETTER_SETTER(Signing);
#endif
#if PROTOCOL_VERSION > 393 /* > 1.13 */
        GETTER_SETTER(Slot);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        GETTER_SETTER(Pages);
        GETTER_SETTER(Title);
#endif
    };
} //ProtocolCraft
#endif

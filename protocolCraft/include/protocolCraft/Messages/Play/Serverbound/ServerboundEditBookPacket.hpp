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
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0c;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x14;
#else
#error "Protocol version not implemented"
#endif

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

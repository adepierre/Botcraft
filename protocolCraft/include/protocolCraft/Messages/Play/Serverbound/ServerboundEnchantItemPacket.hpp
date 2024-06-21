#if PROTOCOL_VERSION < 476 /* < 1.14 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundEnchantItemPacket : public BaseMessage<ServerboundEnchantItemPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Enchant item";

        DECLARE_FIELDS(
            (char, char),
            (ContainerId, Enchantment)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Enchantment);
    };
} //ProtocolCraft
#endif

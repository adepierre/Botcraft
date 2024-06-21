#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/NBT/NBT.hpp"
#else
#include "protocolCraft/Types/PackedRegistryEntry.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>
#endif


namespace ProtocolCraft
{
    class ClientboundRegistryDataPacket : public BaseMessage<ClientboundRegistryDataPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Registry Data";

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (NBT::UnnamedValue),
            (RegistryHolder)
        );
#else
        DECLARE_FIELDS(
            (Identifier, std::vector<PackedRegistryEntry>),
            (Registry,   Entries)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(RegistryHolder);
#else
        GETTER_SETTER(Registry);
        GETTER_SETTER(Entries);
#endif
    };
} //ProtocolCraft
#endif

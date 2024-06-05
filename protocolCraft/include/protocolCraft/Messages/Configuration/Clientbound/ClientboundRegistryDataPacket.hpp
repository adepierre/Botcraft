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
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Registry Data";

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(NBT::UnnamedValue);
        DECLARE_FIELDS_NAMES(RegistryHolder);
#else
        DECLARE_FIELDS_TYPES(Identifier, std::vector<PackedRegistryEntry>);
        DECLARE_FIELDS_NAMES(Registry,   Entries);
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

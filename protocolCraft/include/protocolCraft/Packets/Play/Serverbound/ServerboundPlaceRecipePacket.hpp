#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundPlaceRecipePacket : public BasePacket<ServerboundPlaceRecipePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Place Recipe";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif
#if PROTOCOL_VERSION < 393 /* < 1.13 */ || PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(Recipe, VarInt);
#else
        SERIALIZED_FIELD(Recipe, Identifier);
#endif
        SERIALIZED_FIELD(UseMaxItems, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

#if PROTOCOL_VERSION > 316 /* > 1.11.2 */ && PROTOCOL_VERSION < 338 /* < 1.12.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/Recipes/RecipePlacementItemMove.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipePlacementPacket : public BasePacket<ServerboundRecipePlacementPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Placement";

        SERIALIZED_FIELD(ContainerId, unsigned char);
        SERIALIZED_FIELD(Uid, short);
        SERIALIZED_FIELD(MoveItemsFromGrid, Internal::Vector<RecipePlacementItemMove, short>);
        SERIALIZED_FIELD(MoveItemsToGrid, Internal::Vector<RecipePlacementItemMove, short>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

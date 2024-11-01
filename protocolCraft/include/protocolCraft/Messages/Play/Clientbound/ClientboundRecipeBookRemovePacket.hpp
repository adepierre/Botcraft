#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundRecipeBookRemovePacket : public BaseMessage<ClientboundRecipeBookRemovePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Remove";

        SERIALIZED_FIELD(Recipes, std::vector<VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

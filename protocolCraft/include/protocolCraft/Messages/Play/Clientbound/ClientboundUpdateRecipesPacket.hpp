#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/Recipe.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateRecipesPacket : public BaseMessage<ClientboundUpdateRecipesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Recipes";

        SERIALIZED_FIELD(Recipes, std::vector<Recipe>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

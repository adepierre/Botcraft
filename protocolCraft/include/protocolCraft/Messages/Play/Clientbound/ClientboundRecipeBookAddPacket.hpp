#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/RecipeBookAddEntry.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundRecipeBookAddPacket : public BaseMessage<ClientboundRecipeBookAddPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Add";

        SERIALIZED_FIELD(Entries, std::vector<RecipeBookAddEntry>);
        SERIALIZED_FIELD(Replace, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

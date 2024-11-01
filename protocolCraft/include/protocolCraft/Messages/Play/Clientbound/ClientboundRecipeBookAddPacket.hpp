#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/RecipeDisplayEntry.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundRecipeBookAddPacket : public BaseMessage<ClientboundRecipeBookAddPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Add";

        // The char is the flags (should be an extra subtype with RecipeDisplayEntry and char, but easier with just a pair)
        // TODO: do a proper subtype if one day ClientboundRecipeBookAddPacket::Entry has extra fields
        SERIALIZED_FIELD(Entries, std::vector<std::pair<RecipeDisplayEntry, char>>);
        SERIALIZED_FIELD(Replace, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/RecipeBookSettings.hpp"

namespace ProtocolCraft
{
    class ClientboundRecipeBookSettingsPacket : public BaseMessage<ClientboundRecipeBookSettingsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Settings";

        SERIALIZED_FIELD(BookSettings, RecipeBookSettings);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

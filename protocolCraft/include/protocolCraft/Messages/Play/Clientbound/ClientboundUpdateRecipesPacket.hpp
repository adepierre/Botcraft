#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Types/Recipes/Recipe.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Recipes/SelectableRecipeSingleInputEntry.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateRecipesPacket : public BaseMessage<ClientboundUpdateRecipesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Recipes";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Recipes, std::vector<Recipe>);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(ItemSets, std::map<Identifier, std::vector<VarInt>>);
        SERIALIZED_FIELD(StoneCutterRecipes, std::vector<SelectableRecipeSingleInputEntry>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

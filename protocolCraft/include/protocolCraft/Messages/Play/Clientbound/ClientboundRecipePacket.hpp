#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/RecipeBookSettings.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    enum class RecipeState
    {
        Init = 0,
        Add = 1,
        Remove = 2
    };

    class ClientboundRecipePacket : public BaseMessage<ClientboundRecipePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe";

        DEFINE_CONDITION(IsInit, GetState() == RecipeState::Init);

        SERIALIZED_FIELD(State, Internal::DiffType<RecipeState, VarInt>);
        SERIALIZED_FIELD(BookSettings, RecipeBookSettings);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(Recipes, std::vector<VarInt>);
        SERIALIZED_FIELD(ToHighlight, Internal::Conditioned<std::vector<VarInt>, &THIS::IsInit>);
#else
        SERIALIZED_FIELD(Recipes, std::vector<Identifier>);
        SERIALIZED_FIELD(ToHighlight, Internal::Conditioned<std::vector<Identifier>, &THIS::IsInit>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

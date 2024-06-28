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

        DECLARE_CONDITION(IsInit, GetState() == RecipeState::Init);

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (Internal::DiffType<RecipeState, VarInt>, RecipeBookSettings, std::vector<VarInt>, Internal::Conditioned<std::vector<VarInt>, &THIS::IsInit>),
            (State,                                   BookSettings,       Recipes,             ToHighlight)
        );
#else
        DECLARE_FIELDS(
            (Internal::DiffType<RecipeState, VarInt>, RecipeBookSettings, std::vector<Identifier>, Internal::Conditioned<std::vector<Identifier>, &THIS::IsInit>),
            (State,                                   BookSettings,       Recipes,                 ToHighlight)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(State);
        GETTER_SETTER(BookSettings);
        GETTER_SETTER(Recipes);
        GETTER_SETTER(ToHighlight);
    };
} //ProtocolCraft

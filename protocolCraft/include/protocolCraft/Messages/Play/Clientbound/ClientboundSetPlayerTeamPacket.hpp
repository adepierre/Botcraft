#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 374 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetPlayerTeamPacket : public BaseMessage<ClientboundSetPlayerTeamPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Player Team";

        DECLARE_CONDITION(Method02, GetMethod() == 0 || GetMethod() == 2);
        DECLARE_CONDITION(Method034, GetMethod() == 0 || GetMethod() == 3 || GetMethod() == 4);

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::string, char,   Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<char, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<char, &THIS::Method02>, Internal::Conditioned<std::vector<std::string>, &THIS::Method034>),
            (Name_,       Method, DisplayName,                                         PlayerPrefix,                                        PlayerSuffix,                                        Options,                                      NametagVisibility,                                   CollisionRule,                                       Color,                                        Players)
        );
#else
        DECLARE_FIELDS(
            (std::string, char,   Internal::Conditioned<Chat, &THIS::Method02>, Internal::Conditioned<char, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<VarInt, &THIS::Method02>, Internal::Conditioned<Chat, &THIS::Method02>, Internal::Conditioned<Chat, &THIS::Method02>, Internal::Conditioned<std::vector<std::string>, &THIS::Method034>),
            (Name_,       Method, DisplayName,                                  Options,                                      NametagVisibility,                                   CollisionRule,                                       Color,                                          PlayerPrefix,                                 PlayerSuffix,                                 Players)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Name_);
        GETTER_SETTER(Method);
        GETTER_SETTER(DisplayName);
        GETTER_SETTER(PlayerPrefix);
        GETTER_SETTER(PlayerSuffix);
        GETTER_SETTER(Options);
        GETTER_SETTER(NametagVisibility);
        GETTER_SETTER(CollisionRule);
        GETTER_SETTER(Color);
        GETTER_SETTER(Players);
    };
} //ProtocolCraft

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

        DEFINE_CONDITION(Method02, GetMethod() == 0 || GetMethod() == 2);
        DEFINE_CONDITION(Method034, GetMethod() == 0 || GetMethod() == 3 || GetMethod() == 4);

        SERIALIZED_FIELD(Name_, std::string);
        SERIALIZED_FIELD(Method, char);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(DisplayName, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(PlayerPrefix, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(PlayerSuffix, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(Options, Internal::Conditioned<char, &THIS::Method02>);
        SERIALIZED_FIELD(NametagVisibility, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(CollisionRule, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(Color, Internal::Conditioned<char, &THIS::Method02>);
#else
        SERIALIZED_FIELD(DisplayName, Internal::Conditioned<Chat, &THIS::Method02>);
        SERIALIZED_FIELD(Options, Internal::Conditioned<char, &THIS::Method02>);
        SERIALIZED_FIELD(NametagVisibility, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(CollisionRule, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(Color, Internal::Conditioned<VarInt, &THIS::Method02>);
        SERIALIZED_FIELD(PlayerPrefix, Internal::Conditioned<Chat, &THIS::Method02>);
        SERIALIZED_FIELD(PlayerSuffix, Internal::Conditioned<Chat, &THIS::Method02>);
#endif
        SERIALIZED_FIELD(Players, Internal::Conditioned<std::vector<std::string>, &THIS::Method034>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

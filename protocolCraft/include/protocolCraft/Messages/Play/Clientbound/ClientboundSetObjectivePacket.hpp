#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 389 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/NumberFormat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetObjectivePacket : public BaseMessage<ClientboundSetObjectivePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Objective";

        DECLARE_CONDITION(Method02, GetMethod() == 0 || GetMethod() == 2);

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::string,   char,   Internal::Conditioned<std::string, &THIS::Method02>, Internal::Conditioned<std::string, &THIS::Method02>),
            (ObjectiveName, Method, DisplayName,                                         RenderType)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (std::string,   char,   Internal::Conditioned<Chat, &THIS::Method02>, Internal::Conditioned<VarInt, &THIS::Method02>),
            (ObjectiveName, Method, DisplayName,                                  RenderType)
        );
#else
        DECLARE_FIELDS(
            (std::string,   char,   Internal::Conditioned<Chat, &THIS::Method02>, Internal::Conditioned<VarInt, &THIS::Method02>, Internal::Conditioned<NumberFormat, &THIS::Method02>),
            (ObjectiveName, Method, DisplayName,                                  RenderType,                                     NumberFormat)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ObjectiveName);
        GETTER_SETTER(Method);
        GETTER_SETTER(DisplayName);
        GETTER_SETTER(RenderType);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(NumberFormat);
#endif
    };
} //ProtocolCraft

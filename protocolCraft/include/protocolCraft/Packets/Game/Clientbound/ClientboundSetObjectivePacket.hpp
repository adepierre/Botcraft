#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 389 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/NumberFormat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetObjectivePacket : public BasePacket<ClientboundSetObjectivePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Objective";

        DEFINE_CONDITION(Method02, GetMethod() == 0 || GetMethod() == 2);

        SERIALIZED_FIELD(ObjectiveName, std::string);
        SERIALIZED_FIELD(Method, char);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(DisplayName, Internal::Conditioned<std::string, &THIS::Method02>);
        SERIALIZED_FIELD(RenderType, Internal::Conditioned<std::string, &THIS::Method02>);
#else
        SERIALIZED_FIELD(DisplayName, Internal::Conditioned<Chat, &THIS::Method02>);
        SERIALIZED_FIELD(RenderType, Internal::Conditioned<VarInt, &THIS::Method02>);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SERIALIZED_FIELD(NumberFormat, Internal::Conditioned<ProtocolCraft::NumberFormat, &THIS::Method02>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

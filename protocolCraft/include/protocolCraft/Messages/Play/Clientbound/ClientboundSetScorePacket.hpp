#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    enum class SetScoreMethod
    {
        Change = 0,
        Remove = 1
    };
#endif

    class ClientboundSetScorePacket : public BaseMessage<ClientboundSetScorePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Score";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_CONDITION(NotRemove, GetMethod() != SetScoreMethod::Remove)
        DECLARE_FIELDS(
            (std::string, Internal::DiffType<SetScoreMethod, char>, std::string,   Internal::Conditioned<VarInt, &ClientboundSetScorePacket::NotRemove>),
            (Owner,       Method,                                   ObjectiveName, Score)
        );
#else
        DECLARE_FIELDS(
            (std::string, std::string,   VarInt, std::optional<Chat>, std::optional<NumberFormat>),
            (Owner,       ObjectiveName, Score,  Display,             NumberFormat)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Owner);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        GETTER_SETTER(Method);
#endif
        GETTER_SETTER(ObjectiveName);
        GETTER_SETTER(Score);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(Display);
        GETTER_SETTER(NumberFormat);
#endif
    };
} //ProtocolCraft

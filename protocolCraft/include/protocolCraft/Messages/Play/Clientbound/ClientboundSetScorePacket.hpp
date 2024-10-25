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
        DEFINE_CONDITION(NotRemove, GetMethod() != SetScoreMethod::Remove);
        SERIALIZED_FIELD(Owner, std::string);
        SERIALIZED_FIELD(Method, Internal::DiffType<SetScoreMethod, char>);
        SERIALIZED_FIELD(ObjectiveName, std::string);
        SERIALIZED_FIELD(Score, Internal::Conditioned<VarInt, &THIS::NotRemove>);
#else
        SERIALIZED_FIELD(Owner, std::string);
        SERIALIZED_FIELD(ObjectiveName, std::string);
        SERIALIZED_FIELD(Score, VarInt);
        SERIALIZED_FIELD(Display, std::optional<Chat>);
        SERIALIZED_FIELD(NumberFormat, std::optional<ProtocolCraft::NumberFormat>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    enum class SetTitlesType
    {
        Title = 0,
        Subtitle,
#if PROTOCOL_VERSION > 210 /* > 1.10.2 */
        ActionBar,
#endif
        Times,
        Clear,
        Reset
    };

    class ClientboundSetTitlesPacket : public BasePacket<ClientboundSetTitlesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Titles";

#if PROTOCOL_VERSION > 210 /* > 1.10.2 */
        DEFINE_CONDITION(HasText, GetType() == SetTitlesType::Title || GetType() == SetTitlesType::Subtitle || GetType() == SetTitlesType::ActionBar);
#else
        DEFINE_CONDITION(HasText, GetType() == SetTitlesType::Title || GetType() == SetTitlesType::Subtitle);
#endif
        DEFINE_CONDITION(HasTimes, GetType() == SetTitlesType::Times);

        SERIALIZED_FIELD(Type, Internal::DiffType<SetTitlesType, VarInt>);
        SERIALIZED_FIELD(Text, Internal::Conditioned<Chat, &THIS::HasText>);
        SERIALIZED_FIELD(FadeInTime, Internal::Conditioned<int, &THIS::HasTimes>);
        SERIALIZED_FIELD(StayTime, Internal::Conditioned<int, &THIS::HasTimes>);
        SERIALIZED_FIELD(FadeOutTime, Internal::Conditioned<int, &THIS::HasTimes>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

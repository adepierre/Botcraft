#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    enum class SetTitlesType
    {
        Title = 0,
        Subtitle = 1,
        ActionBar = 2,
        Times = 3,
        Clear = 4,
        Reset = 5
    };

    class ClientboundSetTitlesPacket : public BaseMessage<ClientboundSetTitlesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Titles";

        DECLARE_CONDITION(HasText, GetType() == SetTitlesType::Title || GetType() == SetTitlesType::Subtitle || GetType() == SetTitlesType::ActionBar);
        DECLARE_CONDITION(HasTimes, GetType() == SetTitlesType::Times);

        DECLARE_FIELDS(
            (Internal::DiffType<SetTitlesType, VarInt>, Internal::Conditioned<Chat, &THIS::HasText>, Internal::Conditioned<int, &THIS::HasTimes>, Internal::Conditioned<int, &THIS::HasTimes>, Internal::Conditioned<int, &THIS::HasTimes>),
            (Type,                                      Text,                                        FadeInTime,                                  StayTime,                                    FadeOutTime)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Type);
        GETTER_SETTER(Text);
        GETTER_SETTER(FadeInTime);
        GETTER_SETTER(StayTime);
        GETTER_SETTER(FadeOutTime);
    };
} //ProtocolCraft
#endif

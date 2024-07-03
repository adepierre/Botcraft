#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStopSoundPacket : public BaseMessage<ClientboundStopSoundPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Stop Sound";

        DECLARE_CONDITION(Flags1, GetFlags() & 0x01);
        DECLARE_CONDITION(Flags2, GetFlags() & 0x02);

        DECLARE_FIELDS(
            (char,  Internal::Conditioned<VarInt, &THIS::Flags1>, Internal::Conditioned<Identifier, &THIS::Flags2>),
            (Flags, Source,                                       Name_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Flags);
        GETTER       (Source);
        GETTER       (Name_);
    public:
        auto& SetSource(const std::optional<int>& Source)
        {
            SetFlags(Source.has_value() ? (GetFlags() | 0x01) : (GetFlags() & ~0x01));
            std::get<static_cast<size_t>(FieldsEnum::Source)>(fields) = Source;
            return *this;
        }

        auto& SetName_(const std::optional<Identifier>& Name_)
        {
            SetFlags(Name_.has_value() ? (GetFlags() | 0x02) : (GetFlags() & ~0x02));
            std::get<static_cast<size_t>(FieldsEnum::Name_)>(fields) = Name_;
            return *this;
        }
    };
} //ProtocolCraft
#endif

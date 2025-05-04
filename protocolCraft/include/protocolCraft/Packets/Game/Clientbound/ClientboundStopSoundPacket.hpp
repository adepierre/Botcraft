#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStopSoundPacket : public BasePacket<ClientboundStopSoundPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Stop Sound";

        DEFINE_CONDITION(Flags1, GetFlags() & 0x01);
        DEFINE_CONDITION(Flags2, GetFlags() & 0x02);

        SERIALIZED_FIELD(Flags, char);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Source, Internal::Conditioned<VarInt, &THIS::Flags1>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Name_, Internal::Conditioned<Identifier, &THIS::Flags2>);

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(Source);
        GETTER(Name_);

    public:
        auto& SetSource(const std::optional<int>& Source_)
        {
            SetFlags(Source.has_value() ? (GetFlags() | 0x01) : (GetFlags() & ~0x01));
            Source = Source_;
            return *this;
        }

        auto& SetName_(const std::optional<Identifier>& Name__)
        {
            SetFlags(Name_.has_value() ? (GetFlags() | 0x02) : (GetFlags() & ~0x02));
            Name_ = Name__;
            return *this;
        }
    };
} //ProtocolCraft
#endif

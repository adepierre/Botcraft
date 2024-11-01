#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketRot : public BaseMessage<ServerboundMovePlayerPacketRot>
    {
    public:
        static constexpr std::string_view packet_name = "Move Player Rot";

        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(OnGround, bool);
#else
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Flags, std::bitset<2>);

    public:
        bool GetOnGround() const { return Flags[0]; }
        bool GetHorizontalCollision() const { return Flags[1]; }
        THIS& SetOnGround(const bool b) { Flags.set(0, b); return *this; }
        THIS& SetHorizontalCollision(const bool b) { Flags.set(1, b); return *this; }
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

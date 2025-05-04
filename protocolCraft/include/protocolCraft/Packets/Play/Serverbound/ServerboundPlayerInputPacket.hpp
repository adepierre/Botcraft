#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerInputPacket : public BasePacket<ServerboundPlayerInputPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Input";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Xxa, float);
        SERIALIZED_FIELD(Zza, float);
        SERIALIZED_FIELD(Flags, unsigned char);
#else
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Flags, std::bitset<7>);

    public:
        bool GetForward()  const { return Flags[0]; }
        bool GetBackward() const { return Flags[1]; }
        bool GetLeft()     const { return Flags[2]; }
        bool GetRight()    const { return Flags[3]; }
        bool GetJump()     const { return Flags[4]; }
        bool GetShift()    const { return Flags[5]; }
        bool GetSprint()   const { return Flags[6]; }
        THIS& SetForward (const bool b) { Flags.set(0, b); return *this; }
        THIS& SetBackward(const bool b) { Flags.set(1, b); return *this; }
        THIS& SetLeft    (const bool b) { Flags.set(2, b); return *this; }
        THIS& SetRight   (const bool b) { Flags.set(3, b); return *this; }
        THIS& SetJump    (const bool b) { Flags.set(4, b); return *this; }
        THIS& SetShift   (const bool b) { Flags.set(5, b); return *this; }
        THIS& SetSprint  (const bool b) { Flags.set(6, b); return *this; }
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

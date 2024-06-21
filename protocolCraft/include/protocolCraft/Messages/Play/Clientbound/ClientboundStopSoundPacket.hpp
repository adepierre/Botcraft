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

        DECLARE_FIELDS(
            (std::optional<VarInt>, std::optional<Identifier>),
            (Source,                Name_)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(Source);
        GETTER_SETTER(Name_);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const char flags = ReadData<char>(iter, length);
            SetSource(flags & 0x01 ? ReadData<VarInt>(iter, length) : std::optional<int>());
            SetName_(flags & 0x02 ? ReadData<Identifier>(iter, length) : std::optional<Identifier>());
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(static_cast<char>((static_cast<int>(GetName_().has_value()) << 1) | static_cast<int>(GetSource().has_value())), container);
            if (GetSource().has_value())
            {
                WriteData<VarInt>(GetSource().value(), container);
            }
            if (GetName_().has_value())
            {
                WriteData<Identifier>(GetName_().value(), container);
            }
        }
    };
} //ProtocolCraft
#endif

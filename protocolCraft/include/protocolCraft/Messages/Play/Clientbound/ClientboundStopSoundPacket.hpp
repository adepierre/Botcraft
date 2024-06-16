#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStopSoundPacket : public BaseMessage<ClientboundStopSoundPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x68;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x6A;
#else
#error "Protocol version not implemented"
#endif

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

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetSimulationDistancePacket : public BaseMessage<ClientboundSetSimulationDistancePacket>
    {
    public:
#if   PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x62;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Simulation Distance";

        DECLARE_FIELDS_TYPES(VarInt);
        DECLARE_FIELDS_NAMES(SimulationDistance);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SimulationDistance);
    };
} //ProtocolCraft
#endif

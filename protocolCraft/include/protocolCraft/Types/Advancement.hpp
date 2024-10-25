#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/AdvancementDisplay.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class Advancement : public NetworkType
    {
        SERIALIZED_FIELD(ParentId, std::optional<Identifier>);
        SERIALIZED_FIELD(DisplayData, std::optional<AdvancementDisplay>);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(Criteria, std::vector<Identifier>);
#endif
        SERIALIZED_FIELD(Requirements, std::vector<std::vector<std::string>>);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        SERIALIZED_FIELD(SendsTelemetryEvent, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}

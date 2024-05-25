#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/AdvancementDisplay.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class Advancement : public NetworkType
    {
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS_TYPES(std::optional<Identifier>, std::optional<AdvancementDisplay>, std::vector<Identifier>, std::vector<std::vector<std::string>>);
        DECLARE_FIELDS_NAMES(ParentId,                  DisplayData,                       Criteria,                Requirements);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS_TYPES(std::optional<Identifier>, std::optional<AdvancementDisplay>, std::vector<Identifier>, std::vector<std::vector<std::string>>, bool);
        DECLARE_FIELDS_NAMES(ParentId,                  DisplayData,                       Criteria,                Requirements,                          SendsTelementryEvent);
#else
        DECLARE_FIELDS_TYPES(std::optional<Identifier>, std::optional<AdvancementDisplay>, std::vector<std::vector<std::string>>, bool);
        DECLARE_FIELDS_NAMES(ParentId,                  DisplayData,                       Requirements,                          SendsTelemetryEvent);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ParentId);
        GETTER_SETTER(DisplayData);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(Criteria);
#endif
        GETTER_SETTER(Requirements);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        GETTER_SETTER(SendsTelemetryEvent);
#endif
    };
}

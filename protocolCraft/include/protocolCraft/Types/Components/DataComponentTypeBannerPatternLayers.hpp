#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/BannerPatternLayer.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBannerPatternLayers : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(std::vector<BannerPatternLayer>);
            DECLARE_FIELDS_NAMES(Layers);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Layers);
        };
    }
}
#endif

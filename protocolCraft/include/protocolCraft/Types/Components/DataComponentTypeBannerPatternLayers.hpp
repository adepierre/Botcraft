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
            SERIALIZED_FIELD(Layers, std::vector<BannerPatternLayer>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

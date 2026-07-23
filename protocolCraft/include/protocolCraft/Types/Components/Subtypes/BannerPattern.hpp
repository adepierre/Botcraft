#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class BannerPattern : public NetworkType
        {
            SERIALIZED_FIELD(AssetId, Identifier);
            SERIALIZED_FIELD(TranslationKey, std::string);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class AssetInfo : public NetworkType
        {
            SERIALIZED_FIELD(Suffix, std::string);

            DECLARE_READ_WRITE_SERIALIZE;
        };

        class MaterialAssetGroup : public NetworkType
        {
            SERIALIZED_FIELD(Base, AssetInfo);
            SERIALIZED_FIELD(Overrides, std::map<Identifier, AssetInfo>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

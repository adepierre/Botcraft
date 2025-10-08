#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>
#include <string>

namespace ProtocolCraft
{
    namespace Components
    {
        class PlayerSkinPatch : public NetworkType
        {
            SERIALIZED_FIELD(Body, std::optional<Identifier>);
            SERIALIZED_FIELD(Cape, std::optional<Identifier>);
            SERIALIZED_FIELD(Elytra, std::optional<Identifier>);
            SERIALIZED_FIELD(Model, std::optional<bool>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

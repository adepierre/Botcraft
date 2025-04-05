#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Components/Subtypes/TrimMaterial.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeProvidesTrimMaterial : public DataComponentType
        {
            SERIALIZED_FIELD(Material, Either<Holder<ProtocolCraft::Components::TrimMaterial>, Identifier>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

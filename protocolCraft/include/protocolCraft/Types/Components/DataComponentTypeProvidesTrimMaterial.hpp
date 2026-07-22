#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/TrimMaterial.hpp"
#include "protocolCraft/Types/Holder.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeProvidesTrimMaterial : public DataComponentType
        {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            SERIALIZED_FIELD(Material, Either<Holder<ProtocolCraft::Components::TrimMaterial>, Identifier>);
#else
            SERIALIZED_FIELD(Material, Holder<ProtocolCraft::Components::TrimMaterial>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

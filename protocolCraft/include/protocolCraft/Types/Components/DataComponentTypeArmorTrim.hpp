#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Components/Subtypes/TrimMaterial.hpp"
#include "protocolCraft/Types/Components/Subtypes/TrimPattern.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeArmorTrim : public DataComponentType
        {
            SERIALIZED_FIELD(Material, Holder<TrimMaterial>);
            SERIALIZED_FIELD(Pattern, Holder<TrimPattern>);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            SERIALIZED_FIELD(ShowInTooltip, bool);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeWeapon : public DataComponentType
        {
            SERIALIZED_FIELD(ItemDamagePerAttack, VarInt);
            SERIALIZED_FIELD(DisableBlockingForSeconds, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

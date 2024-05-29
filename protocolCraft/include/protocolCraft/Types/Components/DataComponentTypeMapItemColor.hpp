#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMapItemColor : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(int);
            DECLARE_FIELDS_NAMES(Rgb);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Rgb);
        };
    }
}
#endif

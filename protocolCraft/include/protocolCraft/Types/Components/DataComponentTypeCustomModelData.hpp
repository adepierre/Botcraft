#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeCustomModelData : public DataComponentType
        {
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
            SERIALIZED_FIELD(Value, VarInt);
#else
            SERIALIZED_FIELD(Floats, std::vector<float>);
            SERIALIZED_FIELD(Flags, std::vector<bool>);
            SERIALIZED_FIELD(Strings, std::vector<std::string>);
            SERIALIZED_FIELD(Colors, std::vector<int>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

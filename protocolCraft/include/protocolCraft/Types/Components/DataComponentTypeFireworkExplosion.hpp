#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFireworkExplosion : public DataComponentType
        {
            SERIALIZED_FIELD(Shape, int);
            SERIALIZED_FIELD(Colors, std::vector<int>);
            SERIALIZED_FIELD(FadeColors, std::vector<int>);
            SERIALIZED_FIELD(HasTrail, bool);
            SERIALIZED_FIELD(HasTwinkle, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFireworkExplosion : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(int,   std::vector<int>, std::vector<int>, bool,     bool);
            DECLARE_FIELDS_NAMES(Shape, Colors,           FadeColors,       HasTrail, HasTwinkle);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Shape);
            GETTER_SETTER(Colors);
            GETTER_SETTER(FadeColors);
            GETTER_SETTER(HasTrail);
            GETTER_SETTER(HasTwinkle);
        };
    }
}
#endif

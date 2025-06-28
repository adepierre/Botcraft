#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ItemAttributeModifiersDisplayData : public NetworkType
        {
        public:
            virtual ~ItemAttributeModifiersDisplayData() {}
        };
    }
}
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ValueMatcher : public NetworkType
        {
        public:
            virtual ~ValueMatcher()
            {

            }

        };
    }
}
#endif

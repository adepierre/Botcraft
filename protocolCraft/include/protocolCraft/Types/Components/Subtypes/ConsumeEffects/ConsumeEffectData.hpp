#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ConsumeEffectData : public NetworkType
        {
        public:
            virtual ~ConsumeEffectData() {};
        };
    }
}
#endif

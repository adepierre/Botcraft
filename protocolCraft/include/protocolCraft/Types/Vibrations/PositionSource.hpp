#pragma once

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class PositionSource : public NetworkType
    {
    public:
        virtual ~PositionSource() override
        {

        }
        
        static std::shared_ptr<PositionSource> CreatePositionSource(const Identifier& position_source_type);
    };
}
#endif

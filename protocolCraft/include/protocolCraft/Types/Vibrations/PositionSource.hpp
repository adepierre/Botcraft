#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    enum class PositionSourceType
    {
        None = -1,
        Block = 0,
        Entity = 1,
    };
#endif

    class PositionSource : public NetworkType
    {
    public:
        virtual ~PositionSource() override {}

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        static std::shared_ptr<PositionSource> CreatePositionSource(const PositionSourceType position_source_type);
#else
        static std::shared_ptr<PositionSource> CreatePositionSource(const Identifier& position_source_type);
#endif
    };
}
#endif

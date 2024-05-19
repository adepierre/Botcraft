#if PROTOCOL_VERSION > 754 /* > 1.16.5 */

#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#include "protocolCraft/Types/Vibrations/BlockPositionSource.hpp"
#include "protocolCraft/Types/Vibrations/EntityPositionSource.hpp"

#include <stdexcept>

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    std::shared_ptr<PositionSource> PositionSource::CreatePositionSource(const PositionSourceType position_source_type)
    {
        switch (position_source_type)
        {
            case PositionSourceType::Block:
                return std::make_shared<BlockPositionSource>();
            case PositionSourceType::Entity:
                return std::make_shared<EntityPositionSource>();
            default:
                throw std::runtime_error("Unable to create position source with type: " + std::to_string(static_cast<int>(position_source_type)));
        }
    }
#else
    std::shared_ptr<PositionSource> PositionSource::CreatePositionSource(const Identifier& position_source_type)
    {
        if (position_source_type.GetName() == "block")
        {
            return std::make_shared<BlockPositionSource>();
        }
        else if (position_source_type.GetName() == "entity")
        {
            return std::make_shared<EntityPositionSource>();
        }
        else
        {
            throw std::runtime_error("Unable to create position source with type: " + position_source_type.GetFull());
        }
    }
#endif
}
#endif

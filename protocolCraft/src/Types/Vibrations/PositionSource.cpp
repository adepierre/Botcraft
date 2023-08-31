#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */

#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#include "protocolCraft/Types/Vibrations/BlockPositionSource.hpp"
#include "protocolCraft/Types/Vibrations/EntityPositionSource.hpp"

#include <stdexcept>

namespace ProtocolCraft
{
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
}
#endif

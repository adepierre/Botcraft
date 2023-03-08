#if PROTOCOL_VERSION > 754

#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#include "protocolCraft/Types/Vibrations/BlockPositionSource.hpp"
#include "protocolCraft/Types/Vibrations/EntityPositionSource.hpp"

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
            throw std::runtime_error("Unknown type of PositionSource: " + position_source_type.GetName());
        }
    }
}
#endif

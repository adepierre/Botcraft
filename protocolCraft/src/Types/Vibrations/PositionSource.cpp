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
            return std::shared_ptr<BlockPositionSource>(new BlockPositionSource);
        }
        else if (position_source_type.GetName() == "entity")
        {
            return std::shared_ptr<EntityPositionSource>(new EntityPositionSource);
        }
        else
        {
            throw(std::runtime_error("Unknown type of PositionSource: " + position_source_type.GetName()));
        }
    }
}
#endif

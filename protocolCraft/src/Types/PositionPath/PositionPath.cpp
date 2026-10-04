#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/PositionPath/PositionPath.hpp"

#include "protocolCraft/Types/PositionPath/PositionPathLinear.hpp"
#include "protocolCraft/Types/PositionPath/PositionPathStepped.hpp"

#include <stdexcept>

namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(PositionPathLinear);
    DEFINE_NETWORK_TYPE(PositionPathStepped);

    std::shared_ptr<PositionPathData> PositionPath::CreatePositionPathData(const PositionPathDataType type)
    {
        switch (type)
        {
        case PositionPathDataType::Linear:
            return std::make_shared<PositionPathLinear>();
        case PositionPathDataType::Stepped:
            return std::make_shared<PositionPathStepped>();
        default: // Should not happen
            throw std::runtime_error("Unable to create PositionPathData with id: " + std::to_string(static_cast<int>(type)) + ".");
            return nullptr;
        }
    }

    DEFINE_NETWORK_TYPE(PositionPath);
}
#endif

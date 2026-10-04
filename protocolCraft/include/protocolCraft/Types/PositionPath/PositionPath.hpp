#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"


namespace ProtocolCraft
{
    enum class PositionPathDataType
    {
        None = -1,
        Linear,
        Stepped,
        NUM_POSITIONPATH_TYPES
    };

    class PositionPathData;

    class PositionPath : public NetworkType
    {
    private:
        static std::shared_ptr<PositionPathData> CreatePositionPathData(const PositionPathDataType type);

        SERIALIZED_DYNAMIC_FIELD(PositionPath, Type, Data, PositionPathData, PositionPath::CreatePositionPathData, Internal::DiffType<PositionPathDataType, VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"

namespace ProtocolCraft
{
    class VibrationPath : public NetworkType
    {
        SERIALIZED_FIELD(Origin, NetworkPosition);
        SERIALIZED_DYNAMIC_FIELD(VibrationPath, DestinationType, Destination, PositionSource, PositionSource::CreatePositionSource, Identifier);
        SERIALIZED_FIELD(ArrivalInTicks, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif

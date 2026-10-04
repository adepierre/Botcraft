#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"
#else
#include "protocolCraft/Utilities/DynamicType.hpp"
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#endif

namespace ProtocolCraft
{
    class VibrationParticleOption : public ParticleOption
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(VibrationPath, ProtocolCraft::VibrationPath);
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SERIALIZED_DYNAMIC_FIELD(VibrationParticleOption, DestinationType, Destination, PositionSource, PositionSource::CreatePositionSource, Identifier);
        SERIALIZED_FIELD(ArrivalInTicks, VarInt);
#else
        SERIALIZED_DYNAMIC_FIELD(VibrationParticleOption, DestinationType, Destination, PositionSource, PositionSource::CreatePositionSource, Internal::DiffType<PositionSourceType, VarInt>);
        SERIALIZED_FIELD(ArrivalInTicks, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

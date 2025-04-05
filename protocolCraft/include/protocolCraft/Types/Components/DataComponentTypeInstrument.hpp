#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "protocolCraft/Types/Either.hpp"
#endif
#include "protocolCraft/Types/Components/Subtypes/Instrument.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeInstrument : public DataComponentType
        {
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            SERIALIZED_FIELD(Instrument, Holder<ProtocolCraft::Components::Instrument>);
#else
            SERIALIZED_FIELD(Instrument, Either<Holder<ProtocolCraft::Components::Instrument>, Identifier>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

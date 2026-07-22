#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */ && PROTOCOL_VERSION < 775 /* < 26.1 */
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
#elif PROTOCOL_VERSION < 775 /* < 26.1 */
            SERIALIZED_FIELD(Instrument, Either<Holder<ProtocolCraft::Components::Instrument>, Identifier>);
#else
            SERIALIZED_FIELD(Instrument, Holder<ProtocolCraft::Components::Instrument>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

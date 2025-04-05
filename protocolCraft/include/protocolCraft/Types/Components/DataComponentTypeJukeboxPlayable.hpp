#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Components/Subtypes/JukeboxSong.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeJukeboxPlayable : public DataComponentType
        {
            SERIALIZED_FIELD(Song, Either<Holder<JukeboxSong>, Identifier>);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            SERIALIZED_FIELD(ShowInTooltip, bool);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

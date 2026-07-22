#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/JukeboxSong.hpp"
#include "protocolCraft/Types/Holder.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeJukeboxPlayable : public DataComponentType
        {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
            SERIALIZED_FIELD(Song, Either<Holder<JukeboxSong>, Identifier>);
#else
            SERIALIZED_FIELD(Song, Holder<JukeboxSong>);
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            SERIALIZED_FIELD(ShowInTooltip, bool);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

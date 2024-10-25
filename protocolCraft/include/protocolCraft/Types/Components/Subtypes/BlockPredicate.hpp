#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/HolderSet.hpp"
#include "protocolCraft/Types/Components/Subtypes/StatePropertiesPredicate.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class BlockPredicate : public NetworkType
        {
            SERIALIZED_FIELD(Blocks, std::optional<HolderSet>);
            SERIALIZED_FIELD(Properties, std::optional<StatePropertiesPredicate>);
            SERIALIZED_FIELD(Nbt, std::optional<NBT::UnnamedValue>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

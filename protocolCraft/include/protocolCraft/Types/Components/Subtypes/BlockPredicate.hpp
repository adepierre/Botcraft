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
            DECLARE_FIELDS(
                (std::optional<HolderSet>, std::optional<StatePropertiesPredicate>, std::optional<NBT::UnnamedValue>),
                (Blocks,                   Properties,                              Nbt)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Blocks);
            GETTER_SETTER(Properties);
            GETTER_SETTER(Nbt);
        };
    }
}
#endif

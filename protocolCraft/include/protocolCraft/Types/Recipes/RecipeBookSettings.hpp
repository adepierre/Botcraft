#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class RecipeBookSettings : public NetworkType
    {
        SERIALIZED_FIELD(IsGuiOpen, bool);
        SERIALIZED_FIELD(IsFilteringCraftable, bool);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        SERIALIZED_FIELD(IsFurnaceGuiOpen, bool);
        SERIALIZED_FIELD(IsFurnaceFilteringOpen, bool);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        SERIALIZED_FIELD(IsBlastingFurnaceGuiOpen, bool);
        SERIALIZED_FIELD(IsBlastingFurnaceFilteringCraftable, bool);
        SERIALIZED_FIELD(IsSmokerGuiOpen, bool);
        SERIALIZED_FIELD(IsSmokerFilteringCraftable, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}

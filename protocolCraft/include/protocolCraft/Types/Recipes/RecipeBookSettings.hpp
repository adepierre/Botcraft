#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class RecipeBookSettings : public NetworkType
    {
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (bool,      bool),
            (IsGuiOpen, IsFilteringCraftable)
        );
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS(
            (bool,      bool,                 bool,             bool),
            (IsGuiOpen, IsFilteringCraftable, IsFurnaceGuiOpen, IsFurnaceFilteringOpen)
        );
#else
        DECLARE_FIELDS(
            (bool,      bool,                 bool,             bool,                   bool,                     bool,                                bool,            bool),
            (IsGuiOpen, IsFilteringCraftable, IsFurnaceGuiOpen, IsFurnaceFilteringOpen, IsBlastingFurnaceGuiOpen, IsBlastingFurnaceFilteringCraftable, IsSmokerGuiOpen, IsSmokerFilteringCraftable)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(IsGuiOpen);
        GETTER_SETTER(IsFilteringCraftable);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        GETTER_SETTER(IsFurnaceGuiOpen);
        GETTER_SETTER(IsFurnaceFilteringOpen);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        GETTER_SETTER(IsBlastingFurnaceGuiOpen);
        GETTER_SETTER(IsBlastingFurnaceFilteringCraftable);
        GETTER_SETTER(IsSmokerGuiOpen);
        GETTER_SETTER(IsSmokerFilteringCraftable);
#endif
    };
}

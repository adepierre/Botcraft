#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Item/Slot.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"

#include <optional>

namespace ProtocolCraft
{
    class HashedSlotActualItem : public NetworkType
    {
        SERIALIZED_FIELD(ItemId, VarInt);
        SERIALIZED_FIELD(ItemCount, VarInt);
        SERIALIZED_FIELD(Components, Components::HashedDataComponentPatch);

        DECLARE_READ_WRITE_SERIALIZE;
    };

    class HashedSlot : public NetworkType
    {
    public:
        HashedSlot() = default;
        // Useful conversion from regular slot
        HashedSlot(const Slot& slot)
        {
            if (slot.IsEmptySlot())
            {
                ActualItem = std::nullopt;
            }
            else
            {
                ActualItem = HashedSlotActualItem()
                    .SetItemId(slot.GetItemId())
                    .SetItemCount(slot.GetItemCount())
                    .SetComponents(slot.GetComponents());
            }
        }

        SERIALIZED_FIELD(ActualItem, std::optional<HashedSlotActualItem>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif

#pragma once

#include <map>
#include "protocolCraft/Types/Slot.hpp"

namespace Botcraft
{
    class Window
    {
    public:
        static const short PLAYER_INVENTORY_INDEX;

        static const short INVENTORY_CRAFTING_OUTPUT_INDEX;
        static const short INVENTORY_CRAFTING_INPUT_START;
        static const short INVENTORY_ARMOR_START;
        static const short INVENTORY_STORAGE_START;
        static const short INVENTORY_HOTBAR_START;
        static const short INVENTORY_OFFHAND_INDEX;

        static const ProtocolCraft::Slot EMPTY_SLOT;

        Window(const int type_ = -1);

        const ProtocolCraft::Slot& GetSlot(const short index) const;
        const std::map<short, ProtocolCraft::Slot>& GetSlots() const;
        void SetSlot(const short index, const ProtocolCraft::Slot& slot);
        const int GetNextTransactionId() const;
        void SetNextTransactionId(const int n);

    private:
        std::map<short, ProtocolCraft::Slot> slots;
        // Types are detailed in registries, see https://wiki.vg/Inventory
        int type;
        // TODO, need mutex to make this thread-safe?
        int next_transaction_id;
    };
} // Botcraft
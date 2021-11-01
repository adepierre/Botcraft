#pragma once

#include <map>
#include "protocolCraft/Types/Slot.hpp"
#include "botcraft/Game/Enums.hpp"

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

        Window(const InventoryType type_ = InventoryType::Default);

        const ProtocolCraft::Slot& GetSlot(const short index) const;
        const std::map<short, ProtocolCraft::Slot>& GetSlots() const;
        const InventoryType GetType() const;
        void SetSlot(const short index, const ProtocolCraft::Slot& slot);
#if PROTOCOL_VERSION < 755
        const int GetNextTransactionId() const;
        void SetNextTransactionId(const int n);
#else
        const int GetStateId() const;
        void SetStateId(const int state_id_);
#endif
        const short GetFirstPlayerInventorySlot() const;

    private:
        std::map<short, ProtocolCraft::Slot> slots;
        InventoryType type;

#if PROTOCOL_VERSION < 755
        // TODO, need mutex to make this thread-safe?
        int next_transaction_id;
#elif PROTOCOL_VERSION > 755
        int state_id;
#endif
    };
} // Botcraft
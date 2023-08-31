#pragma once

#include <map>
#include "protocolCraft/Types/Slot.hpp"
#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
    class Window
    {
    public:
        static constexpr short PLAYER_INVENTORY_INDEX = 0;

        static constexpr short INVENTORY_CRAFTING_OUTPUT_INDEX = 0;
        static constexpr short INVENTORY_CRAFTING_INPUT_START = 1;
        static constexpr short INVENTORY_ARMOR_START = 5;
        static constexpr short INVENTORY_HEAD_ARMOR = INVENTORY_ARMOR_START + 0;
        static constexpr short INVENTORY_CHEST_ARMOR = INVENTORY_ARMOR_START + 1;
        static constexpr short INVENTORY_LEGS_ARMOR = INVENTORY_ARMOR_START + 2;
        static constexpr short INVENTORY_FEET_ARMOR = INVENTORY_ARMOR_START + 3;
        static constexpr short INVENTORY_STORAGE_START = 9;
        static constexpr short INVENTORY_HOTBAR_START = 36;
        static constexpr short INVENTORY_OFFHAND_INDEX = 45;

        static const ProtocolCraft::Slot EMPTY_SLOT;

        Window(const InventoryType type_ = InventoryType::Default);

        const ProtocolCraft::Slot& GetSlot(const short index) const;
        const std::map<short, ProtocolCraft::Slot>& GetSlots() const;
        const InventoryType GetType() const;
        void SetSlot(const short index, const ProtocolCraft::Slot& slot);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        const int GetNextTransactionId() const;
        void SetNextTransactionId(const int n);
#elif PROTOCOL_VERSION > 755 /* > 1.17 */
        const int GetStateId() const;
        void SetStateId(const int state_id_);
#endif
        const short GetFirstPlayerInventorySlot() const;

    private:
        std::map<short, ProtocolCraft::Slot> slots;
        InventoryType type;

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        // TODO, need mutex to make this thread-safe?
        int next_transaction_id;
#elif PROTOCOL_VERSION > 755 /* > 1.17 */
        int state_id;
#endif
    };
} // Botcraft

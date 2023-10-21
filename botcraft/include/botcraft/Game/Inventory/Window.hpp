#pragma once

#include <map>
#include <shared_mutex>

#include "protocolCraft/Types/Slot.hpp"

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Utilities/ScopeLockedWrapper.hpp"

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

        Window(const InventoryType type_ = InventoryType::Default);

        ProtocolCraft::Slot GetSlot(const short index) const;
        std::map<short, ProtocolCraft::Slot> GetSlots() const;
        /// @brief Get a read-only locked version of all the slots
        /// @return Basically an object you can use as a std::map<short, ProtocolCraft::Slot>*.
        /// **ALL UPDATE OF THIS INVENTORY WILL BE BLOCKED WHILE THIS OBJECT IS ALIVE**, make sure it goes out of scope
        /// as soon as you don't need it. You can use GetSlots instead to get a copy without blocking future updates
        Utilities::ScopeLockedWrapper<const std::map<short, ProtocolCraft::Slot>, std::shared_mutex, std::shared_lock> GetLockedSlots() const;
        InventoryType GetType() const;
        void SetSlot(const short index, const ProtocolCraft::Slot& slot);
        void SetContent(const std::vector<ProtocolCraft::Slot>& slots_);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        /// @brief Return a unique transaction id and increment it for next time
        /// @return The transaction id to use for next transaction
        int GetNextTransactionId();
#elif PROTOCOL_VERSION > 755 /* > 1.17 */
        int GetStateId() const;
        void SetStateId(const int state_id_);
#endif
        short GetFirstPlayerInventorySlot() const;

    private:
        mutable std::shared_mutex window_mutex;

        std::map<short, ProtocolCraft::Slot> slots;
        const InventoryType type;

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        // TODO, need mutex to make this thread-safe?
        int next_transaction_id;
#elif PROTOCOL_VERSION > 755 /* > 1.17 */
        int state_id;
#endif
    };
} // Botcraft

#pragma once

#include <functional>
#include <map>
#include <optional>
#include <shared_mutex>

#include "protocolCraft/Types/Item/Slot.hpp"

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

        void Init();

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
        /// @brief First slot with index >= first_index and for which predicate is true, thread-safe
        /// @param predicate Predictate to match, must not call back into this window to prevent double locking
        /// @param first_index Initial index to start the search
        /// @return First matching slot index, std::nullopt if none
        std::optional<short> FindSlotMatching(const std::function<bool(const short, const ProtocolCraft::Slot&)>& predicate, const short first_index = 0) const;
        /// @brief Total count of item_id in slots >= first_index
        /// @return Number of item in matching slots
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        int CountItem(const std::pair<int, unsigned char>& item_id, const short first_index = 0) const;
#else
        int CountItem(const int item_id, const short first_index = 0) const;
#endif

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

#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    Window::Window(const InventoryType type_) : type(type_)
    {
        std::scoped_lock<std::shared_mutex> lock(window_mutex);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        next_transaction_id = 1;
#elif PROTOCOL_VERSION > 755 /* > 1.17 */
        state_id = 1;
#endif
    }

    Slot Window::GetSlot(const short index) const
    {
        std::shared_lock<std::shared_mutex> lock(window_mutex);
        if (slots.find(index) == slots.end())
        {
            return Slot();
        }
        
        return slots.at(index);
    }

    std::map<short, Slot> Window::GetSlots() const
    {
        std::shared_lock<std::shared_mutex> lock(window_mutex);
        return slots;
    }

    Utilities::ScopeLockedWrapper<const std::map<short, ProtocolCraft::Slot>, std::shared_mutex, std::shared_lock> Window::GetLockedSlots() const
    {
        return Utilities::ScopeLockedWrapper<const std::map<short, ProtocolCraft::Slot>, std::shared_mutex, std::shared_lock>(slots, window_mutex);
    }

    InventoryType Window::GetType() const
    {
        std::shared_lock<std::shared_mutex> lock(window_mutex);
        return type;
    }

    void Window::SetSlot(const short index, const ProtocolCraft::Slot& slot)
    {
        std::scoped_lock<std::shared_mutex> lock(window_mutex);
        slots[index] = slot;
    }

    void Window::SetContent(const std::vector<ProtocolCraft::Slot>& slots_)
    {
        std::scoped_lock<std::shared_mutex> lock(window_mutex);
        for (size_t i = 0; i < slots_.size(); ++i)
        {
            slots[i] = slots_[i];
        }
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    int Window::GetNextTransactionId()
    {
        std::scoped_lock<std::shared_mutex> lock(window_mutex);
        return next_transaction_id++;
    }
#elif PROTOCOL_VERSION > 755 /* > 1.17 */
    int Window::GetStateId() const
    {
        std::shared_lock<std::shared_mutex> lock(window_mutex);
        return state_id;
    }

    void Window::SetStateId(const int state_id_)
    {
        std::scoped_lock<std::shared_mutex> lock(window_mutex);
        state_id = state_id_;
    }
#endif

    short Window::GetFirstPlayerInventorySlot() const
    {
        switch (type)
        {
        case InventoryType::Beacon:
        case InventoryType::Lectern:
            return 1;
        case InventoryType::Enchantment:
        case InventoryType::StoneCutter:
            return 2;
        case InventoryType::Furnace:
        case InventoryType::Smoker:
        case InventoryType::BlastFurnace:
        case InventoryType::Merchant:
        case InventoryType::Anvil:
        case InventoryType::CartographyTable:
        case InventoryType::Grindstone:
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        case InventoryType::Smithing:
#endif
            return 3;
        case InventoryType::Loom:
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        case InventoryType::Smithing:
#endif
            return 4;
        case InventoryType::Hopper:
        case InventoryType::BrewingStand:
            return 5;
        case InventoryType::Default:
        case InventoryType::PlayerInventory:
        case InventoryType::Generic3x3:
            return 9;
        case InventoryType::Crafting:
            return 10;
        case InventoryType::ShulkerBox:
            return 27;
        case InventoryType::Generic9x1:
        case InventoryType::Generic9x2:
        case InventoryType::Generic9x3:
        case InventoryType::Generic9x5:
        case InventoryType::Generic9x4:
        case InventoryType::Generic9x6:
            return (static_cast<short>(type) + 1) * 9;
        default:
            LOG_WARNING("First slot asked for unknown InventoryType " << static_cast<int>(type));
            return 9;
        }
    }

} //Botcraft

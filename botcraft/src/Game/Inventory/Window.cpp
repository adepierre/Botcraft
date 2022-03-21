#include "botcraft/Game/Inventory/Window.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    const short Window::PLAYER_INVENTORY_INDEX = 0;

    const short Window::INVENTORY_CRAFTING_OUTPUT_INDEX = 0;
    const short Window::INVENTORY_CRAFTING_INPUT_START = 1;
    const short Window::INVENTORY_ARMOR_START = 5;
    const short Window::INVENTORY_STORAGE_START = 9;
    const short Window::INVENTORY_HOTBAR_START = 36;
    const short Window::INVENTORY_OFFHAND_INDEX = 45;

    const Slot Window::EMPTY_SLOT = Slot();

    Window::Window(const InventoryType type_)
    {
#if PROTOCOL_VERSION < 755
        next_transaction_id = 1;
#elif PROTOCOL_VERSION > 755
        state_id = 1;
#endif
        type = type_;
    }

    const Slot& Window::GetSlot(const short index) const
    {
        if (slots.find(index) == slots.end())
        {
            return EMPTY_SLOT;
        }
        
        return slots.at(index);
    }

    const std::map<short, Slot>& Window::GetSlots() const
    {
        return slots;
    }

    const InventoryType Window::GetType() const
    {
        return type;
    }

    void Window::SetSlot(const short index, const ProtocolCraft::Slot& slot)
    {
        slots[index] = slot;
    }

#if PROTOCOL_VERSION < 755
    const int Window::GetNextTransactionId() const
    {
        return next_transaction_id;
    }

    void Window::SetNextTransactionId(const int n)
    {
        next_transaction_id = n;
    }
#elif PROTOCOL_VERSION > 755
    const int Window::GetStateId() const
    {
        return state_id;
    }

    void Window::SetStateId(const int state_id_)
    {
        state_id = state_id_;
    }
#endif

    const short Window::GetFirstPlayerInventorySlot() const
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
        case InventoryType::Smithing:
            return 3;
        case InventoryType::Loom:
            return 4;
        case InventoryType::Hopper:
        case InventoryType::BrewingStand:
            return 5;
        case InventoryType::Default:
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
        }
    }

} //Botcraft
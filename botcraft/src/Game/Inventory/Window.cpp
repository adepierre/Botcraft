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

    Window::Window(const int type_)
    {
        next_transaction_id = 1;
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

    void Window::SetSlot(const short index, const ProtocolCraft::Slot& slot)
    {
        slots[index] = slot;
    }

    const int Window::GetNextTransactionId() const
    {
        return next_transaction_id;
    }

    void Window::SetNextTransactionId(const int n)
    {
        next_transaction_id = n;
    }


} //Botcraft
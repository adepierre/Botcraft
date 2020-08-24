#include "botcraft/Game/Inventory/Inventory.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    const short Inventory::PLAYER_INVENTORY_INDEX = 0;
    const short Inventory::HOTBAR_START_INDEX = 36;

    Inventory::Inventory()
    {

    }

    const Slot Inventory::GetSlot(const short index) const
    {
        auto it = slots.find(index);
        if (it == slots.end())
        {
            return Slot();
        }
        
        return it->second;
    }

    const std::map<short, Slot>& Inventory::GetSlots() const
    {
        return slots;
    }

    std::map<short, Slot>& Inventory::GetSlots()
    {
        return slots;
    }
} //Botcraft
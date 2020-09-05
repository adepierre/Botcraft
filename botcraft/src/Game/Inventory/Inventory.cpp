#include "botcraft/Game/Inventory/Inventory.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    const short Inventory::PLAYER_INVENTORY_INDEX = 0;

    const short Inventory::INVENTORY_CRAFTING_OUTPUT_INDEX = 0;
    const short Inventory::INVENTORY_CRAFTING_INPUT_START = 1;
    const short Inventory::INVENTORY_ARMOR_START = 5;
    const short Inventory::INVENTORY_STORAGE_START = 9;
    const short Inventory::INVENTORY_HOTBAR_START = 36;
    const short Inventory::INVENTORY_OFFHAND_INDEX = 45;

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
#pragma once

#include <map>
#include "botcraft/Game/Inventory/Slot.hpp"

namespace Botcraft
{
    class Inventory
    {
    public:
        static const short PLAYER_INVENTORY_INDEX;
        static const short HOTBAR_START_INDEX;

        Inventory();

        const Slot GetSlot(const short index) const;
        const std::map<short, Slot>& GetSlots() const;
        std::map<short, Slot>& GetSlots();

    private:
        std::map<short, Slot> slots;
    };
} // Botcraft
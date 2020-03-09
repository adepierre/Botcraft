#pragma once

#include <map>
#include "protocolCraft/Types/Slot.hpp"

namespace Botcraft
{
    class Inventory
    {
    public:
        static const short PLAYER_INVENTORY_INDEX;
        static const short HOTBAR_START_INDEX;

        Inventory();

        const ProtocolCraft::Slot GetSlot(const short index) const;
        const std::map<short, ProtocolCraft::Slot>& GetSlots() const;
        std::map<short, ProtocolCraft::Slot>& GetSlots();

    private:
        std::map<short, ProtocolCraft::Slot> slots;
    };
} // Botcraft
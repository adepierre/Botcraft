#pragma once

#include <map>
#include "protocolCraft/Types/Slot.hpp"

namespace Botcraft
{
    class Inventory
    {
    public:
        static const short PLAYER_INVENTORY_INDEX;

        static const short INVENTORY_CRAFTING_OUTPUT_INDEX;
        static const short INVENTORY_CRAFTING_INPUT_START;
        static const short INVENTORY_ARMOR_START;
        static const short INVENTORY_STORAGE_START;
        static const short INVENTORY_HOTBAR_START;
        static const short INVENTORY_OFFHAND_INDEX;

        Inventory();

        const ProtocolCraft::Slot GetSlot(const short index) const;
        const std::map<short, ProtocolCraft::Slot>& GetSlots() const;
        std::map<short, ProtocolCraft::Slot>& GetSlots();

    private:
        std::map<short, ProtocolCraft::Slot> slots;
    };
} // Botcraft
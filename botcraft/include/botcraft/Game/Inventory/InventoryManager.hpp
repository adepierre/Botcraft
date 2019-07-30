#pragma once

#include <memory>
#include <map>
#include "botcraft/Game/Inventory/Slot.hpp"

namespace Botcraft
{
    class Inventory;

    class InventoryManager
    {
    public:
        InventoryManager();

        void SetSlot(const short window_id, const short index, const Slot& slot);
        std::shared_ptr<Inventory> GetInventory(const short window_id);
        std::shared_ptr<Inventory> GetPlayerInventory();
        const std::shared_ptr<Inventory> GetInventory(const short window_id) const;
        const std::shared_ptr<Inventory> GetPlayerInventory() const;

        void EraseInventory(const short window_id);
        void AddInventory(const short window_id);

        const Slot GetHotbarSelected() const;
        void SetHotbarSelected(const short index);

        const Slot& GetCursor() const;
        void SetCursor(const Slot &c);

    private:
        std::map<short, std::shared_ptr<Inventory> > inventories;
        short index_hotbar_selected;
        Slot cursor;
    };
} // Botcraft
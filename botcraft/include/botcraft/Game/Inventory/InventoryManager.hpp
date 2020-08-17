#pragma once

#include <memory>
#include <map>
#include <mutex>
#include "protocolCraft/Types/Slot.hpp"
#include "protocolCraft/Handler.hpp"

namespace Botcraft
{
    class Inventory;

    class InventoryManager : public ProtocolCraft::Handler
    {
    public:
        InventoryManager();

        std::mutex& GetMutex();

        void SetSlot(const short window_id, const short index, const ProtocolCraft::Slot& slot);
        std::shared_ptr<Inventory> GetInventory(const short window_id);
        std::shared_ptr<Inventory> GetPlayerInventory();
        const std::shared_ptr<Inventory> GetInventory(const short window_id) const;
        const std::shared_ptr<Inventory> GetPlayerInventory() const;

        void EraseInventory(const short window_id);
        void AddInventory(const short window_id);

        const ProtocolCraft::Slot GetHotbarSelected() const;
        void SetHotbarSelected(const short index);

        const ProtocolCraft::Slot& GetCursor() const;
        void SetCursor(const ProtocolCraft::Slot &c);
    private:

        virtual void Handle(ProtocolCraft::Message& msg) override;
        virtual void Handle(ProtocolCraft::SetSlot& msg) override;
        virtual void Handle(ProtocolCraft::WindowItems& msg) override;
        virtual void Handle(ProtocolCraft::OpenWindow& msg) override;
        virtual void Handle(ProtocolCraft::HeldItemChangeClientbound& msg) override;

    private:
        std::mutex inventory_manager_mutex;
        std::map<short, std::shared_ptr<Inventory> > inventories;
        short index_hotbar_selected;
        ProtocolCraft::Slot cursor;
    };
} // Botcraft
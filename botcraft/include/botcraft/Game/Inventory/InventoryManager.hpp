#pragma once

#include <memory>
#include <map>
#include <mutex>
#include "protocolCraft/Types/Slot.hpp"
#include "protocolCraft/Handler.hpp"

namespace Botcraft
{
    class Window;

    class InventoryManager : public ProtocolCraft::Handler
    {
    public:
        InventoryManager();

        std::mutex& GetMutex();

        const std::shared_ptr<Window> GetWindow(const short window_id) const;
        const std::shared_ptr<Window> GetPlayerInventory() const;
        std::shared_ptr<Window> GetWindow(const short window_id);
        std::shared_ptr<Window> GetPlayerInventory();
        const short GetIndexHotbarSelected() const;
        const ProtocolCraft::Slot& GetHotbarSelected() const;
        const ProtocolCraft::Slot& GetCursor() const;
        void AddPendingTransaction(const std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> transaction);

    private:
        void SetHotbarSelected(const short index);
        void SetCursor(const ProtocolCraft::Slot& c);

        void EraseInventory(const short window_id);
        void AddInventory(const short window_id);
        void SetSlot(const short window_id, const short index, const ProtocolCraft::Slot& slot);

    private:

        virtual void Handle(ProtocolCraft::Message& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundContainerSetSlotPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundContainerSetContentPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundOpenScreenPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetCarriedItemPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundContainerAckPacket& msg) override;

    private:
        std::mutex inventory_manager_mutex;
        std::map<short, std::shared_ptr<Window> > inventories;
        short index_hotbar_selected;
        ProtocolCraft::Slot cursor;

        // Vector storing all the transactions that have neither been accepted
        // nor refused by the server yet
        std::vector<ProtocolCraft::ServerboundContainerClickPacket> pending_transactions;
    };
} // Botcraft
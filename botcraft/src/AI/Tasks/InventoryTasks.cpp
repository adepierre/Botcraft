#include <iostream>

#include "botcraft/AI/Tasks/InventoryTasks.hpp"
#include "botcraft/AI/Blackboard.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    namespace AI
    {
        /// <summary>
        /// Utility function to swap two slots in a given container
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <param name="container_id">Container ID</param>
        /// <param name="first_slot">First slot index</param>
        /// <param name="second_slot">Second slot index</param>
        /// <returns>Success if the two slots have been correctly swapped, Failure otherwise</returns>
        Status SwapItemsInContainer(BehaviourClient& client, const short container_id, const short first_slot, const short second_slot)
        {
            std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
            std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);

            if (!container)
            {
                return Status::Failure;
            }

            Slot copied_slot;
            std::shared_ptr<ServerboundContainerClickPacket> click_window_msg;
            int transaction_id;

            // Left click on the first slot, transferring the slot
            // to the cursor
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                copied_slot = container->GetSlots().at(first_slot);
            }

            click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(first_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
            click_window_msg->SetItemStack(copied_slot);
#else
            click_window_msg->SetCarriedItem(copied_slot);
#endif

            transaction_id = client.SendInventoryTransaction(click_window_msg);

            // Wait for the click confirmation (versions < 1.17)
#if PROTOCOL_VERSION < 755
            auto start = std::chrono::system_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
                {
                    std::cerr << "Something went wrong trying to select first slot during swap inventory (Timeout)." << std::endl;
                    return Status::Failure;
                }
                TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
                if (transaction_state == TransactionState::Accepted)
                {
                    break;
                }
                // The transaction has been refused by the server, don't bother with other clicks
                else if (transaction_state == TransactionState::Refused)
                {
                    return Status::Failure;
                }

                client.Yield();
            }
#endif



            // left click on the second slot, transferring the cursor to the slot
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                copied_slot = container->GetSlots().at(second_slot);
            }
            click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(second_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
            click_window_msg->SetItemStack(copied_slot);
#else
            click_window_msg->SetCarriedItem(copied_slot);
#endif

            transaction_id = client.SendInventoryTransaction(click_window_msg);

            // Wait for confirmation in version < 1.17
#if PROTOCOL_VERSION < 755
            start = std::chrono::system_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
                {
                    std::cerr << "Something went wrong trying to select second slot during swap inventory (Timeout)." << std::endl;
                    return Status::Failure;
                }

                TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
                if (transaction_state == TransactionState::Accepted)
                {
                    break;
                }
                // The transaction has been refused by the server, don't bother with other clicks
                else if (transaction_state == TransactionState::Refused)
                {
                    return Status::Failure;
                }

                client.Yield();
            }
#endif
            // Left click once again on the first slot, transferring the cursor to the slot
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                copied_slot = container->GetSlots().at(first_slot);
            }
            click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(first_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
            click_window_msg->SetItemStack(copied_slot);
#else
            click_window_msg->SetCarriedItem(copied_slot);
#endif

            transaction_id = client.SendInventoryTransaction(click_window_msg);

            // Wait for confirmation in version < 1.17
#if PROTOCOL_VERSION < 755
            start = std::chrono::system_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
                {
                    std::cerr << "Something went wrong trying to select third slot during swap inventory (Timeout)." << std::endl;
                    return Status::Failure;
                }

                TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
                if (transaction_state == TransactionState::Accepted)
                {
                    break;
                }
                // The transaction has been refused by the server, don't bother with other clicks
                else if (transaction_state == TransactionState::Refused)
                {
                    return Status::Failure;
                }

                client.Yield();
            }
#endif
            // If we're here, everything succeeded
            return Status::Success;
        }


        Status SetItemInHand(BehaviourClient& client, const std::string& item_name, const Hand hand)
        {
            return Status();
        }

        Status SetItemInHandBlackboard(BehaviourClient& client)
        {
            const std::vector<std::string> variable_names = {
                "SetItemInHand.item_name", "SetItemInHand.hand" };

            Blackboard& blackboard = client.GetBlackboard();

            // Mandatory
            const std::string& item_name = blackboard.Get<std::string>(variable_names[0]);
            const Hand hand = blackboard.Get<Hand>(variable_names[1], Hand::Right);

            return SetItemInHand(client, item_name, hand);
        }

}
}
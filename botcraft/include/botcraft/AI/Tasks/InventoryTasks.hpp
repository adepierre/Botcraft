#pragma once

#include "botcraft/AI/Status.hpp"
#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Game/Inventory/Item.hpp"

namespace Botcraft
{
    class BehaviourClient;

    /// @brief Perform a click action on a container
    /// @param client The client performing the action
    /// @param container_id Container id
    /// @param slot_id Clicked slot id
    /// @param click_type Type of click (same as in ServerboundContainerClickPacket)
    /// @param button_num Button clicked (same as in ServerboundContainerClickPacket)
    /// @return Success if the slots is clicked (for versions < 1.17 and the server confirms it), Failure otherwise
    Status ClickSlotInContainer(BehaviourClient& client, const short container_id, const short slot_id, const int click_type, const char button_num);

    /// @brief Same thing as ClickSlotInContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the slots is clicked (for versions < 1.17 and the server confirms it), Failure otherwise
    Status ClickSlotInContainerBlackboard(BehaviourClient& client);


    /// @brief Swap two slots in a given container
    /// @param client The client performing the action
    /// @param container_id Container ID
    /// @param first_slot First slot index
    /// @param second_slot Second slot index
    /// @return Success if the two slots have been correctly swapped, Failure otherwise
    Status SwapItemsInContainer(BehaviourClient& client, const short container_id, const short first_slot, const short second_slot);

    /// @brief Same thing as SwapItemsInContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the two slots have been correctly swapped, Failure otherwise
    Status SwapItemsInContainerBlackboard(BehaviourClient& client);


    /// @brief Drop item out of inventory
    /// @param client The client performing the action
    /// @param container_id Container ID
    /// @param slot_id Slot ID
    /// @param num_to_keep Number of items to keep in the input slot
    /// @return Success if items were correctly dropped, Failure otherwise
    Status DropItemsFromContainer(BehaviourClient& client, const short container_id, const short slot_id, const short num_to_keep = 0);

    /// @brief Same thing as DropItemsFromContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if items were correctly dropped, Failure otherwise
    Status DropItemsFromContainerBlackboard(BehaviourClient& client);


    /// @brief Take one item from source_slot, and put it on destination_slot
    /// @param client The client performing the action
    /// @param container_id Container ID
    /// @param source_slot Slot from which the item is taken
    /// @param destination_slot Slot receiving the item
    /// @return Success if the item is correctly set, Failure otherwise
    Status PutOneItemInContainerSlot(BehaviourClient& client, const short container_id, const short source_slot, const short destination_slot);

    /// @brief Same thing as PutOneItemInContainerSlot, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the item is correctly set, Failure otherwise
    Status PutOneItemInContainerSlotBlackboard(BehaviourClient& client);


    /// @brief Try to set a given item in the given hand
    /// @param client The client performing the action
    /// @param item_id Item id to place in hand
    /// @param hand Left or right hand
    /// @return Success if the item is now in hand, Failure otherwise
    Status SetItemIdInHand(BehaviourClient& client, const ItemId item_id, const Hand hand = Hand::Right);

    /// @brief Same thing as SetItemIdInHand, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the item is now in hand, Failure otherwise
    Status SetItemIdInHandBlackboard(BehaviourClient& client);

    /// @brief Try to set a given item in the given hand
    /// @param client The client performing the action
    /// @param item_name Item name to place in hand
    /// @param hand Left or right hand
    /// @return Success if the item is now in hand, Failure otherwise
    Status SetItemInHand(BehaviourClient& client, const std::string& item_name, const Hand hand = Hand::Right);

    /// @brief Same thing as SetItemInHand, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the item is now in hand, Failure otherwise
    Status SetItemInHandBlackboard(BehaviourClient& client);


    /// @brief Try to place the item at given pos. If too far, will try
    /// to pathfind toward the position first.
    /// @param client The client performing the action
    /// @param item_name The item to place
    /// @param pos The location where we want to place the block
    /// @param face The face on which the block is placed. If not specified the optimal placing face will be automatically detected using the position of the block relative to the player eyes
    /// @param wait_confirmation If true, waits for the server to send the new block in pos
    /// @param allow_midair_placing If false, task will fail if the neighbour block matching face is air
    /// @param allow_pathfinding If true, the bot will try to pathfind toward the block if it's too far. If false the task will return Failure instead in this case.
    /// @return Success if placement attempt was made (and confirmed by the server if wait_confirmation is true), Failure otherwise
    Status PlaceBlock(BehaviourClient& client, const std::string& item_name, const Position& pos, std::optional<PlayerDiggingFace> face = std::nullopt, const bool wait_confirmation = false, const bool allow_midair_placing = false, const bool allow_pathfinding = true);

    /// @brief Same thing as PlaceBlock, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if placement attempt was made (and confirmed by the server if wait_confirmation is true), Failure otherwise
    Status PlaceBlockBlackboard(BehaviourClient& client);


    /// @brief Search for food item in the inventory and eat it
    /// @param client The client performing the action
    /// @param food_name The item to eat
    /// @param wait_confirmation If true, waits for the eaten stack to be reduced by 1 before returning Success
    /// @return Success if the item was eaten (and confirmed if wait_confirmation is true), Failure otherwise
    Status Eat(BehaviourClient& client, const std::string& food_name, const bool wait_confirmation = true);

    /// @brief Same thing as Eat, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the item was eaten (and confirmed if wait_confirmation is true), Failure otherwise
    Status EatBlackboard(BehaviourClient& client);


    /// @brief Open a container at a given position
    /// @param client The client performing the action
    /// @param pos The position of the container
    /// @return Success if the container is opened, Failure otherwise
    Status OpenContainer(BehaviourClient& client, const Position& pos);

    /// @brief Same thing as OpenContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the container is opened, Failure otherwise
    Status OpenContainerBlackboard(BehaviourClient& client);


    /// @brief Close an opened container
    /// @param client The client performing the action
    /// @param container_id The id of the container to close, if -1, will close the first one found
    /// @return Always return Success
    Status CloseContainer(BehaviourClient& client, const short container_id = -1);

    /// @brief Same thing as CloseContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status CloseContainerBlackboard(BehaviourClient& client);


    /// @brief Log all the inventory content at given log level
    /// @param client The client performing the action
    /// @param level Desired log level
    /// @return Always return Success
    Status LogInventoryContent(BehaviourClient& client, const LogLevel level = LogLevel::Info);

    /// @brief Same thing as LogInventoryContent, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status LogInventoryContentBlackboard(BehaviourClient& client);


#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
    /// @brief Buy or sell an item, assuming a trading window is currently opened.
    /// @param client The client performing the action
    /// @param item_id Id of the item to buy/sell
    /// @param buy If true, the item is bought, otherwise is sold
    /// @param trade_id If > -1, specify which trade we want to use in the list
    /// (useful when the villager sells multiple variants of the same item like
    /// enchanted books or bows)
    /// @return Success if the exchange went sucessfully, Failure otherwise
    Status Trade(BehaviourClient& client, const int item_id, const bool buy, const int trade_id = -1);

    /// @brief Same thing as Trade, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the exchange went sucessfully, Failure otherwise
    Status TradeBlackboard(BehaviourClient& client);


    /// @brief Buy or sell an item, assuming a trading window is currently opened.
    /// @param client The client performing the action
    /// @param item_name Item to buy/sell
    /// @param buy If true, the item is bought, otherwise is sold
    /// @param trade_id If > -1, specify which trade we want to use in the list
    /// (useful when the villager sells multiple variants of the same item like
    /// enchanted books or bows)
    /// @return Success if the exchange went sucessfully, Failure otherwise
    Status TradeName(BehaviourClient& client, const std::string& item_name, const bool buy, const int trade_id = -1);

    /// @brief Same thing as TradeName, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the exchange went sucessfully, Failure otherwise
    Status TradeNameBlackboard(BehaviourClient& client);
#endif


    /// @brief Put item in a crafting container and click on the output, storing it in the inventory.
    /// @param client The client performing the action
    /// @param inputs Input items IDs in a 3x3 grid, inputs[0][1] refers to first line, second column
    /// @param allow_inventory_craft If true, the client will use the inventory small 2x2 grid to craft if possible
    /// @return Success if item is crafted, Failure otherwise
    Status Craft(BehaviourClient& client, const std::array<std::array<ItemId, 3>, 3>& inputs, const bool allow_inventory_craft = true);


    /// @brief Same thing as Craft, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if item is crafted, Failure otherwise
    Status CraftBlackboard(BehaviourClient& client);


    /// @brief Put item in a crafting container and click on the output, storing it in the inventory.
    /// @param client The client performing the action
    /// @param inputs Input items names in a 3x3 grid, inputs[0][1] refers to first line, second column
    /// @param allow_inventory_craft If true, the client will use the inventory small 2x2 grid to craft if possible
    /// @return Success if item is crafted, Failure otherwise
    Status CraftNamed(BehaviourClient& client, const std::array<std::array<std::string, 3>, 3>& inputs, const bool allow_inventory_craft = true);

    /// @brief Same thing as CraftNamed, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if item is crafted, Failure otherwise
    Status CraftNamedBlackboard(BehaviourClient& client);


    /// @brief Check if item_id is present in inventory
    /// @param client The client performing the action
    /// @param item_id Item id
    /// @param quantity Min quantity to have
    /// @return Success if inventory quantity is >= quantity else Failure
    Status HasItemIdInInventory(BehaviourClient& client, const ItemId item_id, const int quantity = 1);

    /// @brief Same thing as HasItemIdInInventory, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if inventory quantity is >= quantity else Failure
    Status HasItemIdInInventoryBlackboard(BehaviourClient& client);

    /// @brief Check if item_name is present in inventory
    /// @param client The client performing the action
    /// @param item_name Item name
    /// @param quantity Min quantity to have
    /// @return Success if inventory quantity is >= quantity else Failure
    Status HasItemInInventory(BehaviourClient& client, const std::string& item_name, const int quantity = 1);

    /// @brief Same thing as HasItemInInventory, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if inventory quantity is >= quantity else Failure
    Status HasItemInInventoryBlackboard(BehaviourClient& client);


    /// @brief Clean the inventory stacking same items together
    /// @param client The client performing the action
    /// @return Success if no operation failed, Failure otherwise
    Status SortInventory(BehaviourClient& client);
}

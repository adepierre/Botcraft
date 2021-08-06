#pragma once

#include "botcraft/Game/BaseClient.hpp"
#include "botcraft/Game/Vector3.hpp"

#include "botcraft/AI/Blackboard.hpp"
#include "botcraft/AI/PathfindingTask.hpp"

namespace Botcraft
{
    enum class DiggingState
    {
        Waiting,
        Digging,
        Stop
    };

    class InterfaceClient : public BaseClient
    {
    public:
        InterfaceClient(const bool use_renderer_, const bool afk_only_ = false);
        ~InterfaceClient();

        const DiggingState GetDiggingState() const;
        // Try to dig the currently pointed block
        void DigPointedBlock();
        const bool DigAt(const Botcraft::Position& location, const PlayerDiggingFace face);
        void StopDigging();

        // Place a given block at a given location
        // item: name of the item to place, fails if not present in the inventory
        // location: position of the placed block
        // placed_face: face on wich placing the block
        // wait_confirmation: if true, wait for the world to update at this location
        const bool PlaceBlock(const std::string& item, const Position& location, const PlayerDiggingFace placed_face, const bool wait_confirmation);
        
        // Interact (right click) with the block at the given location
        // location: position of the block, the player must be < 5 blocks away
        // placed_face: face on wich the player wants to click
        // animation: whether or not to send the animation to the server (vanilla client does)
        const bool InteractWithBlock(const Position& location, const PlayerDiggingFace interact_face, const bool animation = false);

        // Set an item in the given hand, returns true if successfully done, false otherwise
        // item_name: name of the item to find in the inventory
        // hand: in which hand should the item be placed
        const bool SetItemInHand(const std::string& item_name, const Hand hand);

    protected:
        // Example of overriding the processing of an incoming packet
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket&msg) override;

#if PROTOCOL_VERSION > 493
        virtual void Handle(ProtocolCraft::ClientboundBlockBreakAckPacket &msg) override;
#endif


    protected:
        // Swap two slots in a given container
        const bool SwapItemsInContainer(const short container_id, const short first_slot, const short second_slot);

        // Search for specified food item in the inventory and
        // eat it if found.
        // food_name: name of the item to eat, not checked to be actual food
        // wait_confirmation: if true, waits for the eaten stack to be reduced by 1
        const bool Eat(const std::string& food_name, const bool wait_confirmation = false);

        // Open container at a given position
        // pos: position of the chest/barrel/shulker thing
        const bool OpenContainer(const Position& pos);

        // Close an opened container
        const bool CloseContainer(const short container_id);

        // Add some speed on Y
        void Jump();
    
    protected:
        DiggingState digging_state;

        AI::Blackboard blackboard;
        AI::PathfindingTask pathfinding_task;

        // We want the tasks to access the managers
        friend AI::PathfindingTask;
    };
}

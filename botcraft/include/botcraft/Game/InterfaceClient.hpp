#pragma once

#include "botcraft/Game/BaseClient.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    // This looks like a state machine A LOT
    // could be a good idea to refactor this
    // before it's too big
    enum class PathFindingState
    {
        Waiting,
        Searching,
        Moving,
        Stop
    };

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

        // Send a message in the chat
        void Say(const std::string &msg);

        // Ask to respawn when dead (use it if auto_respawn is false)
        void Respawn();

        const bool GetShouldBeClosed() const;

        const DiggingState GetDiggingState() const;
        // Try to dig the currently pointed block
        void Dig();
        void StopDigging();

        void SetAutoRespawn(const bool b);

        // Go to a position
        // goal is the target position of the feets of the player
        // in_range: if true, the pathfinding is considered successful if
        // the final position is less than 4 blocks from the target
        // speed is on block/s on the (X, Z) plane
        // Returns true of the position was reached, false otherwise
        const bool GoTo(const Position &goal, const bool in_range, const float speed = 4.317f);
        void StopPathFinding();

        // Place a given block at a given location
        // item: name of the item to place, fails if not present in the inventory
        // location: position of the placed block, the player must be < 5 blocks away
        // placed_face: face on wich placing the block
        const bool PlaceBlock(const std::string& item, const Position& location, const PlayerDiggingFace placed_face);
        
        // Interact (right click) with the block at the given location
        // location: position of the block, the player must be < 5 blocks away
        // placed_face: face on wich the player wants to click
        // animation: whether or not to send the animation to the server (vanilla client does)
        const bool InteractBlock(const Position& location, const PlayerDiggingFace interact_face, const bool animation = false);

    protected:
        // Example of overriding the processing of an incoming packet
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket&msg) override;

#if PROTOCOL_VERSION > 493
        virtual void Handle(ProtocolCraft::ClientboundBlockBreakAckPacket &msg) override;
#endif


    protected:
        // Find a path between two positions
        const std::vector<Position> FindPath(const Position &start, const Position &end);

        // Set an item in the given hand, returns true if successfully done, false otherwise
        // item_name: name of the item to find in the inventory
        // hand: in which hand should the item be placed
        const bool SetItemInHand(const std::string& item_name, const Hand hand);

        // Search for specified food item in the inventory and
        // eat it if found.
        // food_name: name of the item to eat, not checked to be actual food
        // wait_confirmation: if true, waits for the eaten stack to be reduced by 1
        const bool Eat(const std::string& food_name, const bool wait_confirmation = false);

        // Add some speed on Y
        void Jump();
    
    private:
        PathFindingState pathfinding_state;

        DiggingState digging_state;
    };
}

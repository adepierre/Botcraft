#pragma once

#include "botcraft/Game/BaseClient.hpp"

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
        // speed is the time in seconds to move one block on the (X, Z) plane
        // Returns true of the position was reached, false otherwise
        const bool GoTo(const Position &goal, const float speed = 1.0f);
        void StopPathFinding();

        // Place a given block at a given location
        // item: name of the item to place, fails if not present in the inventory
        // location: position of the placed block, the player must be < 5 blocks away
        // placed_face: face on wich placing the block
        const bool PlaceBlock(const std::string& item, const Position& location, const PlayerDiggingFace placed_face);

    protected:
        // Example of overriding the processing of an incoming packet
        virtual void Handle(ProtocolCraft::UpdateHealth &msg) override;

#if PROTOCOL_VERSION > 493
        virtual void Handle(ProtocolCraft::AcknowledgePlayerDigging &msg) override;
#endif


    private:
        // Find a path between two positions
        const std::vector<Position> FindPath(const Position &start, const Position &end);
    
    private:
        PathFindingState pathfinding_state;

        DiggingState digging_state;
    };
}

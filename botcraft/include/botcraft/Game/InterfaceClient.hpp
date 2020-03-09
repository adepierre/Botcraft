#pragma once

#include "botcraft/Game/BaseClient.hpp"

namespace Botcraft
{
    enum class PathFindingState;

    enum class DiggingState
    {
        Waiting,
        Digging,
        Stop
    };

    class InterfaceClient : public BaseClient
    {
    public:
        InterfaceClient(const std::vector<int> &printed_packets_ = std::vector<int>(0));
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

    protected:
        // Example of overriding the processing of an incoming packet
        virtual void Handle(ProtocolCraft::UpdateHealth &msg) override;

#if PROTOCOL_VERSION > 493
        virtual void Handle(ProtocolCraft::AcknowledgePlayerDigging &msg) override;
#endif


    private:
        // Find a path between two positions
        // /!\ target pos must be in a loaded chunk
        const std::vector<Position> FindPath(const Position &start, const Position &end);
    
    private:
        PathFindingState pathfinding_state;

        DiggingState digging_state;
    };
}

#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    /// @brief Interact with a given entity. If too far, will try to pathfind to it.
    /// @param client The client performing the action
    /// @param entity_id The ID of the entity we want to interact with
    /// @param hand The hand we want to use
    /// @param swing If true, a swing packet will be sent too
    /// @return Success if the entity is right clicked (does not mean the server accepted it though). Failure otherwise.
    Status InteractEntity(BehaviourClient& client, const double entity_id, const Hand hand = Hand::Main, const bool swing = false);

    /// @brief Same thing as InteractEntity, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the entity is right clicked (does not mean the server accepted it though). Failure otherwise.
    Status InteractEntityBlackboard(BehaviourClient& client);
}

#pragma once

#include <string>

#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/AI/Status.hpp"

/// @brief Hit all nearby monster, respecting the invulnerability cooldown of 0.5s
/// @param c The client performing the action
/// @return Always return Success
Botcraft::Status HitCloseHostiles(Botcraft::BehaviourClient& c);

/// @brief Remove entries in Entities.LastTimeHit if last seen > 10s
/// @param c The client performing the action
/// @return Always return Success
Botcraft::Status CleanLastTimeHit(Botcraft::BehaviourClient& c);

#pragma once

#include <memory>

#include <botcraft/Game/ManagersClient.hpp>
#include <botcraft/Game/Vector3.hpp>

std::unique_ptr<Botcraft::ManagersClient> SetupTestBot(const Botcraft::Vector3<double>& offset = { 0,0,0 });

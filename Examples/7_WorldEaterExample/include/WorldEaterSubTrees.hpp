#pragma once

#include <botcraft/AI/Tasks/AllTasks.hpp>
#include <botcraft/AI/SimpleBehaviourClient.hpp>

std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> FullTree();

std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> IsDeadTree();
std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> InitTree();
std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> BaseCampResupplyTree();
std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> MainTree();
std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> ActionLoopTree();
std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> CompletionTree();


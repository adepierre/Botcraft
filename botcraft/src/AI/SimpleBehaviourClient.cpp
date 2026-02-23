#include "botcraft/AI/SimpleBehaviourClient.hpp"

namespace Botcraft
{
    SimpleBehaviourClient::SimpleBehaviourClient(const bool use_renderer_, std::optional<std::pair<int, int>> resolution) :
	    TemplatedBehaviourClient<SimpleBehaviourClient>(use_renderer_, resolution)
    {

    }

    SimpleBehaviourClient::~SimpleBehaviourClient()
    {

    }
} // namespace Botcraft

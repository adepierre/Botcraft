#pragma once

#include <chrono>
#include <functional>

namespace Botcraft
{
    class BehaviourClient;
}

namespace Botcraft::Utilities
{
    void SleepUntil(const std::chrono::steady_clock::time_point& end);

    template <class _Rep, class _Period>
    void SleepFor(const std::chrono::duration<_Rep, _Period>& time)
    {
        SleepUntil(std::chrono::steady_clock::now() + time);
    }

    bool WaitForCondition(const std::function<bool()>& condition, const long long int timeout_ms = 0, const long long int check_interval_ms = 10);

    bool YieldForCondition(const std::function<bool()>& condition, BehaviourClient& client, const long long int timeout_ms = 0);
}

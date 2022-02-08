#pragma once

#include <chrono>

namespace Botcraft
{
    void SleepUntil(const std::chrono::steady_clock::time_point& end);

    template <class _Rep, class _Period>
    void SleepFor(const std::chrono::duration<_Rep, _Period>& time)
    {
        SleepUntil(std::chrono::steady_clock::now() + time);
    }
}

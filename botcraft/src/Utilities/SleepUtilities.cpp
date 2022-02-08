#include "botcraft/Utilities/SleepUtilities.hpp"

#include <thread>

#ifdef _WIN32 && BETTER_SLEEP
#include <Windows.h>
#include <timeapi.h>
#endif

namespace Botcraft
{
    void SleepUntil(const std::chrono::steady_clock::time_point& end)
    {
#if _WIN32 && BETTER_SLEEP
        timeBeginPeriod(1);
#endif

        std::this_thread::sleep_until(end);

#if _WIN32 && BETTER_SLEEP
        timeEndPeriod(1);
#endif
    }
}

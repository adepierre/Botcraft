#include "botcraft/Utilities/SleepUtilities.hpp"

#include <thread>
#include <stdexcept>

#if _WIN32 && BETTER_SLEEP
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

    bool WaitForCondition(const std::function<bool()>& condition, const long long int timeout_ms)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while (timeout_ms == 0 || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < timeout_ms)
        {
            if (condition())
            {
                return true;
            }
            SleepFor(std::chrono::milliseconds(10));
        }
        return false;
    }
}

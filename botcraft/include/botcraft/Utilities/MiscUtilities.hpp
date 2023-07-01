#pragma once

#include <functional>

namespace Botcraft::Utilities
{
    /// @brief A class to execute a callback when destroyed
    class OnEndScope
    {
    public:
        OnEndScope(const std::function<void()>& f) : callback(f) {}
        ~OnEndScope() { callback(); }

        // No copy
        OnEndScope(const OnEndScope& other) = delete;
        OnEndScope(OnEndScope&& other) = delete;
        OnEndScope& operator=(const OnEndScope& other) = delete;

    private:
        std::function<void()> callback;
    };
}

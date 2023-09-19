#pragma once

#include <mutex>

namespace Botcraft::Utilities
{
    /// @brief Mutex protected reference, will be locked until destroyed
    /// @tparam T Class to store
    /// @tparam Mutex Mutex type to use
    /// @tparam Lock Lock type to use
    template<
        class T,
        class Mutex = std::mutex,
        template<class...> class Lock = std::scoped_lock
    >
    class ScopeLockedWrapper
    {
    public:
        ScopeLockedWrapper(T& val, Mutex& mutex) : v(val), lock(mutex) { }

        T* operator->() const { return &v; }
        T& operator*() const { return v; }
    private:
        T& v;
        Lock<Mutex> lock;
    };
}

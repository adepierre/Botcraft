#pragma once

#include <map>
#include <any>
#include <string>

namespace Botcraft
{
    /// @brief Wrapper around a reference that will run a callback on destruct
    /// @tparam T Type of the reference
    template<typename T>
    class OnDestructRef
    {
    public:
        OnDestructRef(T& r, const std::function<void()>& on_destruct_callback_) : _ref(r), on_destruct_callback(on_destruct_callback_) {}
        ~OnDestructRef()
        {
            if (on_destruct_callback)
            {
                on_destruct_callback();
            }
        }

        /// @brief Reference getter. Only works on lvalue to prevent calling it on a temporary object (which would run
        /// the callback immediately instead of when going out of scope.
        /// @return The wrapped reference
        T& ref() const& { return _ref; }
        T& ref() const&& = delete;

    private:
        T& _ref;
        std::function<void()> on_destruct_callback;
    };

    class BlackboardObserver
    {
    public:
        virtual void OnReset() const = 0;
        virtual void OnValueChanged(const std::string& key, const std::any& value) const = 0;
        virtual void OnValueRemoved(const std::string& key) const = 0;
    };

    /// @brief A map wrapper to store arbitrary data
    class Blackboard
    {
    public:
        Blackboard() {}
        ~Blackboard() {}

        /// @brief Get the map value at key, casting it to T.
        /// The map has to contains key and it has to be a T.
        /// @tparam T Any type, must match the type stored at key
        /// @param key key to retrieve the value from
        /// @return The stored value
        template<class T>
        const T& Get(const std::string& key)
        {
            return std::any_cast<T&>(blackboard[key]);
        }
        
        /// @brief Get the map value at key, casting it to T.
        /// If the key is not present in the map, add
        /// it with default_value, and returns it.
        /// @tparam T Any type, must match the type stored at key
        /// @param key key to retrieve the value from
        /// @param default_value The default value to return if key is not found
        /// @return The stored value
        template<class T>
        const T& Get(const std::string& key, const T& default_value)
        {
            auto it = blackboard.find(key);
            if (it == blackboard.end())
            {
                it = blackboard.insert(std::pair<std::string, std::any>(key, default_value)).first;
                NotifyKeyChanged(key, it->second);
            }
            return std::any_cast<T&>(it->second);
        }

        /// @brief Get a ref to the map value at key, casting it to T&.
        /// If the key is not present in the map, add it with default_value, and returns it.
        /// Usage example:
        /// ```cpp
        /// {
        ///     OnDestructRef<int> raw_ref = blackboard.GetRef<int>("key", 0);
        ///     int& my_ref = raw_ref.ref;
        ///     my_ref = 8;
        /// } // End of scope, raw_ref is destroyed and blackboard is notified value has potentially changed
        /// ```
        /// @tparam T Any type, must match the type stored at key
        /// @param key key to retrieve the value from
        /// @param default_value The default value to return if key is not found
        /// @return The stored value
        template<class T>
        OnDestructRef<T> GetRef(const std::string& key, const T& default_value)
        {
            auto it = blackboard.find(key);
            if (it == blackboard.end())
            {
                it = blackboard.insert(std::pair<std::string, std::any>(key, default_value)).first;
            }
            return OnDestructRef(std::any_cast<T&>(it->second), [this, key]() { NotifyKeyChanged(key, blackboard.at(key)); });
        }

        /// @brief Set map entry at key to value
        /// @tparam T Any type, be careful to be explicit with strings because "foo" is not a std::string but a C-style char*
        /// @param key key to store the value at
        /// @param value value to store at key
        template<class T>
        void Set(const std::string& key, const T& value)
        {
            blackboard[key] = value;
            NotifyKeyChanged(key, blackboard[key]);
        }

        /// @brief Copy a blackboard value
        /// @param src Source key, must exist in the blackboard
        /// @param dst Destination key
        void Copy(const std::string& src, const std::string& dst)
        {
            const std::any& source = blackboard.at(src);
            blackboard[dst] = source;
            NotifyKeyChanged(dst, source);
        }

        /// @brief Remove a map entry if present
        /// @param key key we want to remove
        void Erase(const std::string& key)
        {
            blackboard.erase(key);
            NotifyKeyRemoved(key);
        }
        
        /// @brief Clear all the entries in the blackboard
        void Clear()
        {
            blackboard.clear();
            NotifyCleared();
        }

        void Subscribe(BlackboardObserver* observer)
        {
            observers.push_back(observer);
        }

        void Unsubscribe(BlackboardObserver* observer)
        {
            for (auto it = observers.begin(); it != observers.end(); )
            {
                if (*it == observer)
                {
                    it = observers.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

    private:
        void NotifyCleared() const
        {
            for (auto o : observers)
            {
                if (o != nullptr)
                {
                    o->OnReset();
                }
            }
        }

        void NotifyKeyRemoved(const std::string& key) const
        {
            for (auto o : observers)
            {
                if (o != nullptr)
                {
                    o->OnValueRemoved(key);
                }
            }
        }

        void NotifyKeyChanged(const std::string& key, const std::any& value) const
        {
            for (auto o : observers)
            {
                if (o != nullptr)
                {
                    o->OnValueChanged(key, value);
                }
            }
        }

    private:
        std::map<std::string, std::any> blackboard;
        std::vector<BlackboardObserver*> observers;
    };
} // namespace Botcraft

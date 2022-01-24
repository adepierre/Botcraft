#pragma once

#include <map>
#include <any>
#include <string>

namespace Botcraft
{    
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
            }
            return std::any_cast<T&>(it->second);
        }

        /// @brief Get a ref to the map value at key, casting it to T&.
        /// If the key is not present in the map, add
        /// it with default_value, and returns it.
        /// @tparam T Any type, must match the type stored at key
        /// @param key key to retrieve the value from
        /// @param default_value The default value to return if key is not found
        /// @return The stored value
        template<class T>
        T& GetRef(const std::string& key, const T& default_value)
        {
            auto it = blackboard.find(key);
            if (it == blackboard.end())
            {
                it = blackboard.insert(std::pair<std::string, std::any>(key, default_value)).first;
            }
            return std::any_cast<T&>(it->second);
        }

        /// @brief Set map entry at key to value
        /// @tparam T Any type, be careful to be explicit with strings because "foo" is not a std::string
        /// @param key key to store the value at
        /// @param value value to store at key
        template<class T>
        void Set(const std::string& key, const T& value)
        {
            blackboard[key] = value;
        }

        /// @brief Remove a map entry if present
        /// @param key key we want to remove
        void Erase(const std::string& key)
        {
            blackboard.erase(key);
        }
        
        /// @brief Clear all the entries in the blackboard
        void Clear()
        {
            blackboard.clear();
        }

    private:
        std::map<std::string, std::any> blackboard;
    };
} // namespace Botcraft

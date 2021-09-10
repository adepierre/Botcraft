#pragma once

#include <map>
#include <any>
#include <string>

namespace Botcraft
{
    namespace AI
    {
        /// <summary>
        /// A map wrapper to store arbitrary data
        /// </summary>
        class Blackboard
        {
        public:
            Blackboard() {}
            ~Blackboard() {}

            /// <summary>
            /// Get the map value at key, casting it to T.
            /// The map has to contains key and it has to be a T.
            /// </summary>
            /// <typeparam name="T"></typeparam>
            /// <param name="key">key to retrieve the value from</param>
            /// <returns>The stored value</returns>
            template<class T>
            const T& Get(const std::string& key)
            {
                return std::any_cast<T&>(blackboard[key]);
            }

            /// <summary>
            /// Get the map value at key, casting it to T.
            /// If the key is not present in the map, add
            /// it with default_value, and returns it.
            /// </summary>
            /// <typeparam name="T"></typeparam>
            /// <param name="key">key to retrieve the value from</param>
            /// <param name="default_value">The default value to return if key is not found</param>
            /// <returns>The stored value</returns>
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

            /// <summary>
            /// Set map entry at key to value
            /// </summary>
            /// <typeparam name="T"></typeparam>
            /// <param name="key">Key</param>
            /// <param name="value">Value</param>
            template<class T>
            void Set(const std::string& key, const T& value)
            {
                blackboard[key] = value;
            }

            /// <summary>
            /// Remove a map entry if present
            /// </summary>
            /// <param name="key">Key</param>
            void Erase(const std::string& key)
            {
                blackboard.erase(key);
            }

            /// <summary>
            /// Clear all the entries in the blackboard
            /// </summary>
            void Clear()
            {
                blackboard.clear();
            }

        private:
            std::map<std::string, std::any> blackboard;
        };
    } // namespace AI
} // namespace Botcraft
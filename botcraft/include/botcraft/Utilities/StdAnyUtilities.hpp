#pragma once

#include <any>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <functional>
#include <unordered_map>

namespace Botcraft::Utilities
{
    class AnyParser
    {
    public:
        /// @brief Give a string representation of a std::any value
        /// @param value A std::any object to convert to string
        /// @return If the type of the std::any is in registered_types, the string version of value, type name only otherwise.
        static std::string ToString(const std::any& value);

        /// @brief Default function to convert all unregistered
        /// @param value Value to convert
        /// @return String v
        static std::string DefaultToString(const std::any& value);

        static void RegisterType(const std::type_index& index, const std::function<std::string(const std::any&)>& f);

        template<class T>
        static void RegisterType(const std::function<std::string(const std::any&)>& f)
        {
            RegisterType(std::type_index(typeid(T)), f);
        }

    private:
        /// @brief Maps std::type_index of a std::any to a function to convert it to std::string
        static std::unordered_map<std::type_index, std::function<std::string(const std::any&)>> registered_types;
    };
}

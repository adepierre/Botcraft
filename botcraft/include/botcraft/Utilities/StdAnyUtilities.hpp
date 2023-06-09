#pragma once

#include <any>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <functional>

namespace Botcraft
{
    class AnyParser
    {
    public:
        /// @brief Give a string representation of a std::any value
        /// @param value A std::any object to convert to string
        /// @return If the type of the std::any is in registered_types, the string version of value, type name only otherwise.
        static std::string ToString(const std::any& value);

        template<class T>
        void RegisterType(const std::function<std::string(const std::any&)>& f)
        {
            registered_types[std::type_index(typeid(T))] = f;
        }
    private:
        /// @brief Maps std::type_index of a std::any to a function to convert it to std::string
        static std::unordered_map<std::type_index, std::function<std::string(const std::any&)>> registered_types;
    };

}

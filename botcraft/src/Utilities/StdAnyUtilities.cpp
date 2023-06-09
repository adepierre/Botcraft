#include "botcraft/Utilities/StdAnyUtilities.hpp"

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    template<class T>
    std::function<std::string(const std::any&)> SimpleToString()
    {
        return [](const std::any& f) { return std::to_string(std::any_cast<const T&>(f)); };
    }

    std::unordered_map<std::type_index, std::function<std::string(const std::any&)>> AnyParser::registered_types =
    {
        { std::type_index(typeid(void)),                   [](const std::any&) { return "{}"; } },
        { std::type_index(typeid(bool)),                   [](const std::any& v) { return std::any_cast<bool>(v) ? "true" : "false"; } },
        { std::type_index(typeid(short)),                  SimpleToString<short>() },
        { std::type_index(typeid(unsigned short)),         SimpleToString<unsigned short>() },
        { std::type_index(typeid(int)),                    SimpleToString<int>() },
        { std::type_index(typeid(unsigned int)),           SimpleToString<unsigned int>() },
        { std::type_index(typeid(long long int)),          SimpleToString<long long int>() },
        { std::type_index(typeid(unsigned long long int)), SimpleToString<unsigned long long int>() },
        { std::type_index(typeid(float)),                  SimpleToString<float>() },
        { std::type_index(typeid(double)),                 SimpleToString<double>() },
        { std::type_index(typeid(std::string)),            [](const std::any& v) { return std::any_cast<const std::string&>(v); } },
        { std::type_index(typeid(const char*)),            [](const std::any& v) { return std::any_cast<const char* const&>(v); } },
        { std::type_index(typeid(Position)),               [](const std::any& v) {
            const Position& pos = std::any_cast<const Position&>(v);
            return "[" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "," + std::to_string(pos.z) + "]";
        }},
    };

    std::string AnyParser::ToString(const std::any& value)
    {
        const auto it = registered_types.find(std::type_index(value.type()));
        if (it != registered_types.end())
        {
            return it->second(value);
        }

        // TODO: demangle name if available (?)
        return value.type().name();
    }
}

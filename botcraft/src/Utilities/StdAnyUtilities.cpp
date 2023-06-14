#include "botcraft/Utilities/StdAnyUtilities.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/Enums.hpp"

#include <sstream>
#include <iomanip>

namespace Botcraft
{
    template<class T>
    std::string SimpleToString(const std::any& v)
    {
        return std::to_string(std::any_cast<const T&>(v));
    }

    template<class T>
    std::string SimpleStreamOperatorToString(const std::any& v)
    {
        std::stringstream s;
        s << std::any_cast<const T&>(v);
        return s.str();
    }

    std::string CraftInputs(const std::any& v)
    {
        const std::array<std::array<std::string, 3>, 3>& inputs = std::any_cast<const std::array<std::array<std::string, 3>, 3>&>(v);
        std::stringstream s;
        for (size_t row = 0; row < 3; ++row)
        {
            s << '[';
            for (size_t col = 0; col < 3; ++col)
            {
                if (col > 0)
                {
                    s << " | ";
                }
                s << inputs[row][col];
            }
            s << ']';
            if (row < 2)
            {
                s << '\n';
            }
        }
        return s.str();
    }

    std::unordered_map<std::type_index, std::function<std::string(const std::any&)>> AnyParser::registered_types =
    {
        { std::type_index(typeid(void)),                                      [](const std::any&) { return "{}"; } },
        { std::type_index(typeid(bool)),                                      [](const std::any& v) { return std::any_cast<bool>(v) ? "true" : "false"; } },
        { std::type_index(typeid(char)),                                      [](const std::any& v) { std::stringstream s; const char val = std::any_cast<const char&>(v); s << (val < 0 ? "-0x" : "0x") << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(std::abs(val)); return s.str(); }},
        { std::type_index(typeid(unsigned char)),                             [](const std::any& v) { std::stringstream s; s << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(std::any_cast<const unsigned char&>(v)); return s.str(); }},
        { std::type_index(typeid(short)),                                     SimpleToString<short> },
        { std::type_index(typeid(unsigned short)),                            SimpleToString<unsigned short> },
        { std::type_index(typeid(int)),                                       SimpleToString<int> },
        { std::type_index(typeid(unsigned int)),                              SimpleToString<unsigned int> },
        { std::type_index(typeid(long long int)),                             SimpleToString<long long int> },
        { std::type_index(typeid(unsigned long long int)),                    SimpleToString<unsigned long long int> },
        { std::type_index(typeid(float)),                                     SimpleToString<float> },
        { std::type_index(typeid(double)),                                    SimpleToString<double> },
        { std::type_index(typeid(std::string)),                               [](const std::any& v) { return std::any_cast<const std::string&>(v); } },
        { std::type_index(typeid(const char*)),                               [](const std::any& v) { return std::any_cast<const char* const&>(v); } },
        { std::type_index(typeid(Position)),                                  SimpleStreamOperatorToString<Position> },
        { std::type_index(typeid(Vector3<double>)),                           SimpleStreamOperatorToString<Vector3<double>> },
        { std::type_index(typeid(PlayerDiggingFace)),                         SimpleStreamOperatorToString<PlayerDiggingFace> },
        { std::type_index(typeid(Hand)),                                      SimpleStreamOperatorToString<Hand> },
        { std::type_index(typeid(LogLevel)),                                  SimpleStreamOperatorToString<LogLevel> },
        { std::type_index(typeid(std::array<std::array<std::string, 3>, 3>)), CraftInputs },
    };

    std::string AnyParser::ToString(const std::any& value)
    {
        const auto it = registered_types.find(std::type_index(value.type()));
        if (it != registered_types.end())
        {
            return it->second(value);
        }

        return DefaultToString(value);
    }

    std::string AnyParser::DefaultToString(const std::any& value)
    {
        // TODO: demangle name if available (?)
        return value.type().name();
    }

    void AnyParser::RegisterType(const std::type_index& index, const std::function<std::string(const std::any&)>& f)
    {
        registered_types[index] = f;
    }
}

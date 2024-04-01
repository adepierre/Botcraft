#include <array>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    using namespace Internal;

    namespace Json
    {
        std::string EscapeChars(const std::string& s);
        void SkipSpaces(std::string_view::const_iterator& iter, size_t& length);
        Value NumberFromString(const std::string& s, const bool is_scientific, const bool is_double);
        Value ParseNumber(std::string_view::const_iterator& iter, size_t& length);
        Value ParseString(std::string_view::const_iterator& iter, size_t& length);
        Value ParseObject(std::string_view::const_iterator& iter, size_t& length);
        Value ParseArray(std::string_view::const_iterator& iter, size_t& length);
        Value ParseValue(std::string_view::const_iterator& iter, size_t& length);

        Value::Value(std::nullptr_t)
        {

        }

        Value::Value(std::string_view s) : val(std::string(s))
        {

        }

        Value::Value(const std::string& s) : val(s)
        {

        }

        Value::Value(std::string&& s) : val(std::move(s))
        {

        }

        Value::Value(const char* s) : val(std::string(s))
        {

        }

        Value::Value(const bool b) : val(b)
        {

        }

        Value::Value(const Object& o) : val(o)
        {

        }

        Value::Value(Object&& o) : val(std::move(o))
        {

        }

        Value::Value(const Array& a) : val(a)
        {

        }

        Value::Value(Array&& a) : val(std::move(a))
        {

        }

        Value::Value(const std::initializer_list<Value>& init)
        {
            if (init.size() == 2 && init.begin()->is_string())
            {
                val = Object({ { init.begin()->get<std::string>(), *(init.begin() + 1) } });
                return;
            }

            // If all elements are pairs and first element is a string,
            // this is an object, otherwise it's an array
            for (const auto& j : init)
            {
                if (!j.is_object()
                    || j.size() != 1)
                {
                    val = Array(init);
                    return;
                }
            }

            Object new_val;

            for (const auto& j : init)
            {
                new_val.insert(*j.get_object().begin());
            }

            val = std::move(new_val);
        }

        Value::Value(const NetworkType& o) : val(std::move(o.Serialize().val))
        {

        }

        Object& Value::get_object()
        {
            return get<Object>();
        }

        Array& Value::get_array()
        {
            return get<Array>();
        }

        std::string& Value::get_string()
        {
            return get<std::string>();
        }

        const Object& Value::get_object() const
        {
            return get<Object>();
        }

        const Array& Value::get_array() const
        {
            return get<Array>();
        }

        const std::string& Value::get_string() const
        {
            return get<std::string>();
        }

        bool Value::is_null() const
        {
            return is<std::monostate>();
        }

        bool Value::is_string() const
        {
            return is<std::string>();
        }

        bool Value::is_object() const
        {
            return is<Json::Object>();
        }

        bool Value::is_array() const
        {
            return is<Json::Array>();
        }

        bool Value::is_bool() const
        {
            return is<bool>();
        }

        bool Value::is_integer() const
        {
            return std::holds_alternative<long long int>(val)
                || std::holds_alternative<unsigned long long int>(val);
        }

        bool Value::is_number() const
        {
            return std::holds_alternative<long long int>(val)
                || std::holds_alternative<unsigned long long int>(val)
                || std::holds_alternative<double>(val);
        }

        Value& Value::operator[](const std::string& s)
        {
            if (std::holds_alternative<std::monostate>(val))
            {
                val = Object();
            }

            if (!std::holds_alternative<RecursiveWrapper<Object>>(val))
            {
                throw std::runtime_error("Json::Value is not an object");
            }

            return get<Object>()[s];
        }

        const Value& Value::operator[](const std::string& s) const
        {
            if (!std::holds_alternative<RecursiveWrapper<Object>>(val))
            {
                throw std::runtime_error("Json::Value is not an object");
            }

            return get<Object>().at(s);
        }

        Value& Value::operator[](const size_t i)
        {
            if (!std::holds_alternative<RecursiveWrapper<Array>>(val))
            {
                throw std::runtime_error("Json::Value is not an array");
            }

            return get<Array>()[i];
        }

        const Value& Value::operator[](const size_t i) const
        {
            if (!std::holds_alternative<RecursiveWrapper<Array>>(val))
            {
                throw std::runtime_error("Json::Value is not an array");
            }

            return get<Array>().at(i);
        }

        std::istream& operator>>(std::istream& is, Value& v)
        {
            v = ProtocolCraft::Json::Parse(std::string(
                std::istreambuf_iterator<char>(is),
                std::istreambuf_iterator<char>()
            ));

            return is;
        }
        
        bool Value::contains(const std::string& s) const
        {
            return is_object() && get<Object>().count(s);
        }

        size_t Value::size() const
        {
            if (std::holds_alternative<std::monostate>(val))
            {
                return 0;
            }

            if (std::holds_alternative<RecursiveWrapper<Object>>(val))
            {
                return get<Object>().size();
            }

            if (std::holds_alternative<RecursiveWrapper<Array>>(val))
            {
                return get<Array>().size();
            }

            throw std::runtime_error("Json::Value is neither an array nor an object");
        }

        void Value::push_back(const Value& value)
        {
            if (std::holds_alternative<std::monostate>(val))
            {
                val = Array();
            }

            if (!std::holds_alternative<RecursiveWrapper<Array>>(val))
            {
                throw std::runtime_error("Can't push_back in a non-array Json::Value");
            }

            get<Array>().push_back(value);
        }

        void Value::push_back(Value&& value)
        {
            if (std::holds_alternative<std::monostate>(val))
            {
                val = Array();
            }

            if (!std::holds_alternative<RecursiveWrapper<Array>>(val))
            {
                throw std::runtime_error("Can't push_back in a non-array Json::Value");
            }

            get<Array>().push_back(std::move(value));
        }

        std::string Value::Dump(const int indent, const char indent_char) const
        {
            return Dump(0, indent, indent_char);
        }

        Value Parse(std::string_view::const_iterator iter, size_t length, bool no_except)
        {
            const size_t init_length = length;
            try
            {
                Value out = ParseValue(iter, length);
                if (length > 0)
                {
                    throw std::runtime_error(std::to_string(length) + " unread characters remaining after parsing");
                }
                return out;
            }
            catch (const std::runtime_error& e)
            {
                if (no_except)
                {
                    return Value();
                }
                throw std::runtime_error(e.what() + std::string(" (at pos ") + std::to_string(init_length - length) + ')');
            }
        }

        Value Parse(const std::string& s, bool no_except)
        {
            if (s.empty())
            {
                return Value();
            }

            size_t length = s.size();
            std::string_view sview(s.begin().operator->(), s.end() - s.begin());
            try
            {
                return Parse(sview.begin(), length);
            }
            catch (const std::runtime_error& e)
            {
                if (no_except)
                {
                    return Value();
                }
                throw std::runtime_error(e.what() + std::string(" (at pos ") + std::to_string(s.size() - length) + ')');
            }
        }

        std::string Value::Dump(const size_t depth_level, const int indent, const char indent_char) const
        {
            std::ostringstream oss;

            std::visit([&](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;

                if constexpr (std::is_same_v<T, std::monostate>)
                {
                    oss << "null";
                }
                else if constexpr (std::is_same_v<T, RecursiveWrapper<Object>>)
                {
                    const Object& o = arg.get();
                    if (o.empty())
                    {
                        oss << "{}";
                        return;
                    }

                    const std::string new_line = (indent == -1 ? "" : "\n");
                    const std::string line_indentation = indent > -1 ? std::string(depth_level * indent, indent_char) : "";
                    const std::string value_indentation = indent > -1 ? std::string(indent, indent_char) : "";

                    oss << "{" << new_line;
                    bool first = true;
                    for (const auto& [k, v] : o)
                    {
                        if (!first)
                        {
                            oss << "," << new_line;
                        }
                        else
                        {
                            first = false;
                        }
                        oss << line_indentation << value_indentation << "\"" << k << "\"" << (indent == -1 ? ":" : ": ") << v.Dump(depth_level + 1, indent, indent_char);
                    }
                    oss << new_line << line_indentation << "}";
                }
                else if constexpr (std::is_same_v<T, RecursiveWrapper<Array>>)
                {
                    const Array& a = arg.get();
                    if (a.empty())
                    {
                        oss << "[]";
                        return;
                    }
                    const std::string new_line = (indent == -1 ? "" : "\n");
                    const std::string line_indentation = indent > -1 ? std::string(depth_level * indent, indent_char) : "";
                    const std::string value_indentation = indent > -1 ? std::string(indent, indent_char) : "";

                    oss << '[' << new_line;
                    bool first = true;
                    for (const auto& v : a)
                    {
                        if (!first)
                        {
                            oss << ',' << new_line;
                        }
                        else
                        {
                            first = false;
                        }
                        oss << line_indentation << value_indentation << v.Dump(depth_level + 1, indent, indent_char);
                    }
                    oss << new_line << line_indentation << ']';
                }
                else if constexpr (std::is_same_v<T, std::string>)
                {
                    oss << "\"" << EscapeChars(arg) << "\"";
                }
                else if constexpr (std::is_same_v<T, bool>)
                {
                    oss << (arg ? "true" : "false");
                }
                else if constexpr (std::is_same_v<T, double>)
                {
                    if (arg == std::floor(arg))
                    {
                        oss << std::setprecision(1) << std::fixed << arg;
                    }
                    else
                    {
                        oss << arg;
                    }
                }
                else
                {
                    oss << arg;
                }
            }, val);

            return oss.str();
        }

        std::string EscapeChars(const std::string& s)
        {
            std::ostringstream out;
            auto it = s.begin();
            while (it != s.end())
            {
                switch (*it)
                {
                case '\\':
                case '"':
                    out << '\\' << *it;
                    it += 1;
                    break;
                case '\b':
                    out << '\\' << 'b';
                    it += 1;
                    break;
                case '\f':
                    out << '\\' << 'f';
                    it += 1;
                    break;
                case '\n':
                    out << '\\' << 'n';
                    it += 1;
                    break;
                case '\r':
                    out << '\\' << 'r';
                    it += 1;
                    break;
                case '\t':
                    out << '\\' << 't';
                    it += 1;
                    break;
                default:
                    out << *it;
                    it += 1;
                    break;
                }
            }

            return out.str();
        }

        void SkipSpaces(std::string_view::const_iterator& iter, size_t& length)
        {
            while (length)
            {
                switch (*iter)
                {
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    iter += 1;
                    length -= 1;
                    break;
                default:
                    return;
                    break;
                }
            }
        }

        void ValidateStringNumber(const std::string& s)
        {
            const size_t s_size = s.size();
            // Validate the string format
            for (size_t i = 0; i < s_size; ++i)
            {
                switch (s[i])
                {
                case '0':
                    if ((i == 0 && s_size > 1 && s[1] != '.' && s[1] != 'e' && s[1] != 'E') ||
                        (i == 1 && s_size > 2 && s[0] == '-' && s[2] != '.' && s[2] != 'e' && s[2] != 'E'))
                    {
                        throw std::runtime_error("Unexpected leading 0 when parsing number");
                    }
                    break;
                case '-':
                    if (i == s_size - 1 ||
                        (i != 0 && (s[i - 1] == '.' || s[i - 1] == '+'))
                        )
                    {
                        throw std::runtime_error("Unexpected - character when parsing number");
                    }
                    break;
                case '+':
                    if (i == 0 || i == s_size - 1 || (s[i - 1] != 'e' && s[i - 1] != 'E'))
                    {
                        throw std::runtime_error("Unexpected + character when parsing number");
                    }
                    break;
                case 'e':
                case 'E':
                    if (i == 0 ||
                        i == s_size - 1 ||
                        s[i - 1] == '.' ||
                        s[i - 1] == '+' ||
                        s[i - 1] == '-')
                    {
                        throw std::runtime_error("Unexpected exponent sign found when parsing a number");
                    }
                    break;
                case '.':
                    if (i == 0 ||
                        i == s_size - 1 ||
                        s[i - 1] == 'e' ||
                        s[i - 1] == 'E' ||
                        s[i - 1] == '+' ||
                        s[i - 1] == '-')
                    {
                        throw std::runtime_error("Unexpected . sign found when parsing a number");
                    }
                    break;
                default:
                    break;
                }
            }
        }

        Value NumberFromString(const std::string& s, const bool is_scientific, const bool is_double)
        {
            if (s.empty())
            {
                throw std::runtime_error("Trying to convert empty string to number");
            }

            ValidateStringNumber(s);

            if (is_scientific || is_double)
            {
                return std::stod(s);
            }

            if (s[0] == '-')
            {
                // min long long int (but with > because string comparison)
                if (s.size() >= 20 && s > "-9223372036854775808")
                {
                    return std::stod(s);
                }
                return std::stoll(s);
            }

            // max unsigned long long int
            if (s.size() >= 20 && s > "18446744073709551615")
            {
                return std::stod(s);
            }
            return std::stoull(s);
        }

        Value ParseNumber(std::string_view::const_iterator& iter, size_t& length)
        {
            std::string_view::const_iterator start = iter;

            bool is_scientific = false;
            bool is_double = false;

            while (length)
            {
                switch (*iter)
                {
                case 'e':
                case 'E':
                    if (is_scientific)
                    {
                        throw std::runtime_error("Multiple exponent char encountered while parsing number");
                    }
                    is_scientific = true;
                    iter += 1;
                    length -= 1;
                    break;
                case '.':
                    if (is_double)
                    {
                        throw std::runtime_error("Multiple decimal separator encountered while parsing number");
                    }
                    is_double = true;
                    iter += 1;
                    length -= 1;
                    break;
                case '+':
                case '-':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    iter += 1;
                    length -= 1;
                    break;
                default:
                    return NumberFromString(std::string(start, iter), is_scientific, is_double);
                }
            }

            // This means the whole string was a number and no other character was present to stop the reading
            return NumberFromString(std::string(start, iter), is_scientific, is_double);
        }

        bool IsValidCodepoint(const unsigned long cp)
        {
            // Is in range of valide codepoints and is not a surrogate
            return cp <= 0x0010ffffu && !(cp >= 0xd800u && cp <= 0xdfffu);
        }

        std::string CodepointToUtf8(const std::string& hex_chars)
        {
            const unsigned long codepoint = std::stoul(hex_chars, nullptr, 16);

            if (!IsValidCodepoint(codepoint))
            {
                throw std::runtime_error("Trying to parse an invalid codepoint to UTF8 while reading string");
            }

            if (codepoint < 0x80)
            {
                return std::string()
                    + static_cast<char>(codepoint);
            }
            else if (codepoint < 0x800)
            {
                return std::string()
                    + static_cast<char>((codepoint >> 6) | 0xc0)
                    + static_cast<char>((codepoint & 0x3f) | 0x80);
            }
            else if (codepoint < 0x10000)
            {
                return std::string()
                    + static_cast<char>((codepoint >> 12) | 0xe0)
                    + static_cast<char>(((codepoint >> 6) & 0x3f) | 0x80)
                    + static_cast<char>((codepoint & 0x3f) | 0x80);
            }
            else
            {
                return std::string()
                    + static_cast<char>((codepoint >> 18) | 0xf0)
                    + static_cast<char>(((codepoint >> 12) & 0x3f) | 0x80)
                    + static_cast<char>(((codepoint >> 6) & 0x3f) | 0x80)
                    + static_cast<char>((codepoint & 0x3f) | 0x80);
            }
        }

        Value ParseString(std::string_view::const_iterator& iter, size_t& length)
        {
            if (length < 2)
            {
                throw std::runtime_error("Not enough input when reading string");
            }
            if (*iter != '\"')
            {
                throw std::runtime_error(std::string("Unexpected char found at beginning of string \"") + *iter + "\"");
            }
            iter += 1;
            length -= 1;

            std::ostringstream output;
            while (length)
            {
                switch (*iter)
                {
                case '\b':
                case '\f':
                case '\n':
                case '\r':
                case '\t':
                    throw std::runtime_error("Unexpected unescaped special character encountered when parsing string");
                case '"':
                    iter += 1;
                    length -= 1;
                    return output.str();
                case '\\':
                    if (length == 1)
                    {
                        throw std::runtime_error("Missing data after escape character when parsing string");
                    }
                    else
                    {
                        switch (*(iter + 1))
                        {
                        case '\"':
                            output << *iter << *(iter + 1);
                            iter += 2;
                            length -= 2;
                            break;
                        case '\\':
                            output << '\\';
                            iter += 2;
                            length -= 2;
                            break;
                        case '/':
                            output << '/';
                            iter += 2;
                            length -= 2;
                            break;
                        case 'b':
                            output << '\b';
                            iter += 2;
                            length -= 2;
                            break;
                        case 'f':
                            output << '\f';
                            iter += 2;
                            length -= 2;
                            break;
                        case 'n':
                            output << '\n';
                            iter += 2;
                            length -= 2;
                            break;
                        case 'r':
                            output << '\r';
                            iter += 2;
                            length -= 2;
                            break;
                        case 't':
                            output << '\t';
                            iter += 2;
                            length -= 2;
                            break;
                        case 'u':
                            if (length < 6)
                            {
                                throw std::runtime_error("Missing data after \\u character when parsing string");
                            }
                            output << CodepointToUtf8(std::string(iter + 2, iter + 6));
                            iter += 6;
                            length -= 6;
                            break;
                        default:
                            throw std::runtime_error("Unexpected escape character encountered when parsing string");
                            break;
                        }
                    }
                    break;
                default:
                    if (*iter > -1 && *iter < 32)
                    {
                        // Control characters are invalid
                        throw std::runtime_error("Unexpected control character encountered when parsing string");
                    }
                    output << *iter;
                    iter += 1;
                    length -= 1;
                    break;
                }
            }

            throw std::runtime_error("Not enough input when reading string");
        }

        Value ParseObject(std::string_view::const_iterator& iter, size_t& length)
        {
            if (length < 2)
            {
                throw std::runtime_error("Not enough input when reading Json::Object");
            }
            if (*iter != '{')
            {
                throw std::runtime_error(std::string("Unexpected char found at beginning of Json::Object \"") + *iter + "\"");
            }
            iter += 1;
            length -= 1;

            SkipSpaces(iter, length);

            if (length == 0)
            {
                throw std::runtime_error("Not enough input when reading Json::Object");
            }

            Object output;
            if (*iter == '}')
            {
                iter += 1;
                length -= 1;
                return output;
            }

            while (length)
            {
                SkipSpaces(iter, length);

                const Value key = ParseString(iter, length);

                SkipSpaces(iter, length);

                if (*iter != ':')
                {
                    throw std::runtime_error(std::string("Unexpected char \"") + *iter + "\" when reading Json::Object while expecting :");
                }
                iter += 1;
                length -= 1;

                SkipSpaces(iter, length);

                const Value value = ParseValue(iter, length);
                output[key.get_string()] = value;

                SkipSpaces(iter, length);

                if (*iter == '}')
                {
                    iter += 1;
                    length -= 1;
                    return output;
                }
                else if (*iter != ',')
                {
                    throw std::runtime_error(std::string("Unexpected char \"") + *iter + "\" when reading Json::Object while expecting ,");
                }

                iter += 1;
                length -= 1;
            }

            throw std::runtime_error("Not enough input when reading Json::Object");
        }

        Value ParseArray(std::string_view::const_iterator& iter, size_t& length)
        {
            if (length < 2)
            {
                throw std::runtime_error("Not enough input when reading Json::Array");
            }
            if (*iter != '[')
            {
                throw std::runtime_error(std::string("Unexpected char found at beginning of Json::Array \"") + *iter + "\"");
            }
            iter += 1;
            length -= 1;

            Array output;

            SkipSpaces(iter, length);

            if (length == 0)
            {
                throw std::runtime_error("Not enough input when reading Json::Array");
            }

            if (*iter == ']')
            {
                iter += 1;
                length -= 1;
                return output;
            }

            while (length)
            {
                SkipSpaces(iter, length);

                const Value value = ParseValue(iter, length);
                output.push_back(value);

                SkipSpaces(iter, length);

                if (*iter == ']')
                {
                    iter += 1;
                    length -= 1;
                    return output;
                }
                else if (*iter != ',')
                {
                    throw std::runtime_error(std::string("Unexpected char \"") + *iter + "\" when reading Json::Array while expecting ,");
                }

                iter += 1;
                length -= 1;
            }

            throw std::runtime_error("Not enough input when reading Json::Array");
        }

        Value ParseValue(std::string_view::const_iterator& iter, size_t& length)
        {
            SkipSpaces(iter, length);

            Value output;

            switch (*iter)
            {
            case '{':
                output = ParseObject(iter, length);
                break;
            case '[':
                output = ParseArray(iter, length);
                break;
            case '\"':
                output = ParseString(iter, length);
                break;
            case 'n':
                if (length < 4
                    || *(iter + 1) != 'u'
                    || *(iter + 2) != 'l'
                    || *(iter + 3) != 'l')
                {
                    throw std::runtime_error("Unexpected char \"n\"");
                }
                else
                {
                    iter += 4;
                    length -= 4;
                }
                break;
            case 't':
                if (length < 4
                    || *(iter + 1) != 'r'
                    || *(iter + 2) != 'u'
                    || *(iter + 3) != 'e')
                {
                    throw std::runtime_error("Unexpected char \"t\"");
                }
                else
                {
                    iter += 4;
                    length -= 4;
                    output = true;
                }
                break;
            case 'f':
                if (length < 5
                    || *(iter + 1) != 'a'
                    || *(iter + 2) != 'l'
                    || *(iter + 3) != 's'
                    || *(iter + 4) != 'e')
                {
                    throw std::runtime_error("Unexpected char \"f\"");
                }
                else
                {
                    iter += 5;
                    length -= 5;
                    output = false;
                }
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '-':
                output = ParseNumber(iter, length);
                break;
            default:
                throw std::runtime_error(std::string("Unexpected char \"") + *iter + "\"");
                break;
            }

            SkipSpaces(iter, length);

            return output;
        }
    }
}

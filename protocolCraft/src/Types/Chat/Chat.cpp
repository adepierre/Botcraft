#include "protocolCraft/Types/Chat/Chat.hpp"

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include <cctype>
#include <sstream>
#endif

namespace ProtocolCraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    std::string Chat::ParseChat(const Json::Value& raw_json)
    {
        if (raw_json.is_object())
        {
            std::string output = "";

            if (raw_json.contains("text"))
            {
                // It should always be text but just in case
                if (raw_json["text"].is_string())
                {
                    output += raw_json["text"].get_string();
                }
            }
            // TODO: deal with other translate types for completeness
            else if (raw_json.contains("translate") && raw_json["translate"].is_string() && raw_json["translate"].get_string() == "chat.type.text")
            {
                // It *should* be <%s> %s, so we only need with[1]
                if (raw_json.contains("with") && raw_json["with"].is_array() && raw_json["with"].size() > 1)
                {
                    output += ParseChat(raw_json["with"][1]);
                }
            }
            else
            {
                // TODO: deal with other type of content (NBT, scoreboard, selector, keybind)
            }

            // Add extra
            if (raw_json.contains("extra") && raw_json["extra"].is_array())
            {
                output += ParseChat(raw_json["extra"]);
            }

            return output;
        }

        if (raw_json.is_null())
        {
            return "";
        }

        if (raw_json.is_string())
        {
            return raw_json.get_string();
        }

        if (raw_json.is_bool())
        {
            return raw_json.get<bool>() ? "true" : "false";
        }

        if (raw_json.is_number())
        {
            return std::to_string(raw_json.get_number());
        }

        if (raw_json.is_array())
        {
            std::string output = "";

            for (const auto& s : raw_json.get_array())
            {
                output += ParseChat(s);
            }
            return output;
        }

        return "";
    }
#else
    std::string Chat::ParseChatCompound(const NBT::TagCompound& raw)
    {
        std::string output = "";

        if (raw.contains("text") && raw["text"].is<NBT::TagString>())
        {
            output += raw["text"].get<NBT::TagString>();
        }
        // Weird TagList with mixed types : each element is wrapped in a { "", X } compound
        else if (raw.size() == 1 && raw.contains(""))
        {
            output += ParseChat(raw[""]);
        }
        // Translation key
        else if (raw.contains("translate") && raw["translate"].is<NBT::TagString>())
        {
            const std::vector<std::string> args = raw.contains("with") ? ParseChatParts(raw["with"]) : std::vector<std::string>();
            if (raw.contains("fallback") && raw["fallback"].is<NBT::TagString>())
            {
                // Fill %s etc... arguments
                const std::string& format = raw["fallback"].get<NBT::TagString>();
                std::string formatted;
                size_t next_arg = 0;
                bool malformed = false;
                for (size_t i = 0; i < format.size(); ++i)
                {
                    if (format[i] != '%')
                    {
                        formatted += format[i];
                        continue;
                    }

                    // This is a special %XXX character
                    size_t j = i + 1;
                    if (j < format.size() && std::isdigit(static_cast<unsigned char>(format[j])))
                    {
                        // Positional argument, %n$s
                        size_t n = 0;
                        while (j < format.size() && std::isdigit(static_cast<unsigned char>(format[j])))
                        {
                            n *= 10;
                            n += format[j] - '0';
                            ++j;
                        }
                        if (n == 0 || n > args.size() || j + 1 >= format.size() || format[j] != '$' || format[j + 1] != 's')
                        {
                            // This probably shouldn't happen
                            malformed = true;
                            break;
                        }
                        else
                        {
                            formatted += args[n - 1];
                            i = j + 1;
                        }
                    }
                    // escaped %%
                    else if (j < format.size() && format[j] == '%')
                    {
                        formatted += '%';
                        i = j;
                    }
                    // replace string with arg
                    else if (j < format.size() && format[j] == 's' && next_arg < args.size())
                    {
                        formatted += args[next_arg++];
                        i = j;
                    }
                    else
                    {
                        // This probably shouldn't happen
                        malformed = true;
                        break;
                    }
                }
                output += malformed ? format : formatted;
            }
            else
            {
                // We don't have any translation available, keep the translation key
                output += raw["translate"].get<NBT::TagString>();
                if (!args.empty())
                {
                    output += "[";
                    for (size_t i = 0; i < args.size(); ++i)
                    {
                        output += (i == 0 ? "" : ", ") + args[i];
                    }
                    output += "]";
                }
            }
        }
        else if (raw.contains("keybind") && raw["keybind"].is<NBT::TagString>())
        {
            output += raw["keybind"].get<NBT::TagString>();
        }
        // Should be processed server side I think?
        else if (raw.contains("score") || raw.contains("nbt"))
        {

        }
        else if (raw.contains("selector") && raw["selector"].is<NBT::TagString>())
        {
            output += raw["selector"].get<NBT::TagString>();
        }
        // Icon
        else if (raw.contains("object") || raw.contains("sprite") || raw.contains("player"))
        {
            if (raw.contains("fallback"))
            {
                output += ParseChat(raw["fallback"]);
            }
            else if (raw.contains("player") && raw["player"].is<NBT::TagString>())
            {
                output += "<" + raw["player"].get<NBT::TagString>() + ">";
            }
            else if (raw.contains("player") && raw["player"].contains("name") && raw["player"]["name"].is<NBT::TagString>())
            {
                output += "<" + raw["player"]["name"].get<NBT::TagString>() + ">";
            }
        }

        // Add extra
        if (raw.contains("extra"))
        {
            output += Chat::ParseChat(raw["extra"]);
        }

        return output;
    }

    namespace
    {
        template<typename T>
        void AppendNumbersIfTypeMatch(const NBT::Tag& tag, std::vector<std::string>& parts)
        {
            if (tag.is<T>())
            {
                std::ostringstream output;
                if constexpr (std::is_same_v<T, NBT::TagByte>)
                {
                    output << static_cast<int>(tag.get<T>());
                }
                else
                {
                    output << tag.get<T>();
                }
                parts.push_back(output.str());
            }
            else if (tag.is_list_of<T>())
            {
                for (const T value : tag.as_list_of<T>())
                {
                    std::ostringstream output;
                    if constexpr (std::is_same_v<T, NBT::TagByte>)
                    {
                        output << static_cast<int>(value);
                    }
                    else
                    {
                        output << value;
                    }
                    parts.push_back(output.str());
                }
            }
        }
    }

    std::vector<std::string> Chat::ParseChatParts(const NBT::Tag& tag)
    {
        if (tag.is<NBT::TagString>())
        {
            return { tag.get<NBT::TagString>() };
        }

        if (tag.is<NBT::TagCompound>())
        {
            return { ParseChatCompound(tag.get<NBT::TagCompound>()) };
        }

        if (tag.is_list_of<NBT::TagString>())
        {
            return tag.as_list_of<NBT::TagString>();
        }

        std::vector<std::string> parts;
        if (tag.is_list_of<NBT::TagCompound>())
        {
            for (const auto& c : tag.as_list_of<NBT::TagCompound>())
            {
                parts.push_back(ParseChatCompound(c));
            }
        }
        // Numbers for translation arguments
        else
        {
            AppendNumbersIfTypeMatch<NBT::TagByte>(tag, parts);
            AppendNumbersIfTypeMatch<NBT::TagShort>(tag, parts);
            AppendNumbersIfTypeMatch<NBT::TagInt>(tag, parts);
            AppendNumbersIfTypeMatch<NBT::TagLong>(tag, parts);
            AppendNumbersIfTypeMatch<NBT::TagFloat>(tag, parts);
            AppendNumbersIfTypeMatch<NBT::TagDouble>(tag, parts);
        }

        return parts;
    }

    std::string Chat::ParseChat(const NBT::Tag& tag)
    {
        std::string output = "";
        for (const std::string& part : ParseChatParts(tag))
        {
            output += part;
        }
        return output;
    }
#endif
}

#include <nlohmann/json.hpp>

#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    const std::string Chat::ParseChat(const nlohmann::json& raw_json)
    {
        if (raw_json.is_object())
        {
            std::string output = "";

            if (raw_json.contains("text"))
            {
                // It should always be text but just in case
                if (raw_json["text"].is_string())
                {
                    output += raw_json["text"].get<std::string>();
                }
            }
            // TODO: deal with other translate types for completeness
            else if (raw_json.contains("translate") && raw_json["translate"].is_string() && raw_json["translate"].get<std::string>() == "chat.type.text")
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
            return raw_json.get<std::string>();
        }

        if (raw_json.is_boolean())
        {
            return raw_json.get<bool>() ? "true" : "false";
        }

        if (raw_json.is_number_integer())
        {
            return raw_json.is_number_unsigned() ? std::to_string(raw_json.get<unsigned long long int>()) : std::to_string(raw_json.get<long long int>());
        }

        if (raw_json.is_number_float())
        {
            return std::to_string(raw_json.get<double>());
        }

        if (raw_json.is_array())
        {
            std::string output = "";

            for (const auto& s : raw_json)
            {
                output += ParseChat(s);
            }
            return output;
        }

        return "";
    }
}

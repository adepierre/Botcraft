#include <nlohmann/json.hpp>

#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    const std::string Chat::ParseChat(const std::string &json)
    {
        nlohmann::json v;
        v = nlohmann::json::parse(json);

        if (v.is_object())
        {
            if (v.contains("translate") && v["translate"].is_string())
            {
                std::string output;

                // Only deal with other player commands
                if (v["translate"] == "chat.type.text")
                {
                    if (v.contains("with") && v["with"].is_array())
                    {
                        for (auto& s : v["with"])
                        {
                            if (s.is_object() && s.contains("text") && s.at("text").is_string())
                            {
                                from += s["text"].get<std::string>();
                            }
                            else if (s.is_string())
                            {
                                output += s.get<std::string>();
                            }
                        }
                    }
                }
                return output;
            }
        }

        if (v.is_null())
        {
            return "";
        }

        if (v.is_string())
        {
            return v.get<std::string>();
        }

        if (v.is_array())
        {
            std::string output;

            for (auto& s : v)
            {
                output += ParseChat(s.dump());
            }
            return output;
        }

        return "";
    }

    const nlohmann::json Chat::SerializeImpl() const
    {
        nlohmann::json value;

        value["from"] = from;
        value["text"] = text;

        return value;
    }
}
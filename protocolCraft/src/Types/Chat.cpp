#include <iostream>
#include <nlohmann/json.hpp>

#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    std::string Chat::ParseChat(const std::string& json)
    {
        nlohmann::json v;
        try
        {
            v = nlohmann::json::parse(json);
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "Error parsing chat message: " << e.what() << std::endl;
            return "";
        }

        return ParseChat(v);
    }

    std::string Chat::ParseChat(const nlohmann::json& root)
    {
        std::string output;

        if (root.is_object())
        {
            // if there is a "text" key in current root, this goes first - any "extra" values are nested siblings
            if (root.contains("text"))
            {

            }

            if (root.contains("translate") && root["translate"].is_string())
            {
                // Only deal with other player commands
                if (root["translate"] == "chat.type.text")
                {
                    if (root.contains("with") && root["with"].is_array())
                    {
                        for (auto& s : root["with"])
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
            else if (root.contains("extra") && root["extra"].is_array())
            {
                // extra should be an array of strings, one entry per formating style
                for (auto& arrayEntry : root["extra"])
                {
                  // entry should have text and possibly formating
                    if (arrayEntry["text"].is_string())
                    {
                        output += arrayEntry["text"];
                    }
                    
                    if (arrayEntry.contains("extra"))
                    {
                        output += ParseChat(arrayEntry);
                    }
                }
            }
        }
        
        if (root.is_array())
        {
            for (auto& s : root)
            {
                output += ParseChat(s);
            }
            return output;
        }
        
        return output;
    }

    const nlohmann::json Chat::SerializeImpl() const
    {
        nlohmann::json value;

        value["from"] = from;
        value["text"] = text;

        return value;
    }
}
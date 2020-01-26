#include <picojson/picojson.h>

#include "botcraft/Protocol/Types/Chat.hpp"

namespace Botcraft
{
    const std::string Chat::ParseChat(const std::string &json)
    {
        picojson::value v;
        std::string error = picojson::parse(v, json);

        if (!error.empty())
        {
            std::cerr << "Error parsing chat message: " << error << std::endl;
            return "";
        }

        if (v.is<picojson::object>())
        {
            if (v.contains("translate") && v.get("translate").is<std::string>())
            {
                const std::string translate = v.get("translate").get<std::string>();
                std::string output;

                // Only deal with other player commands
                if (translate == "chat.type.text")
                {
                    if (v.contains("with") && v.get("with").is<picojson::array>())
                    {
                        const picojson::array &with = v.get("with").get<picojson::array>();
                        for (auto it = with.begin(); it != with.end(); ++it)
                        {
                            if (it->is<picojson::object>() && it->contains("text") && it->get("text").is<std::string>())
                            {
                                from += it->get("text").get<std::string>();
                            }
                            else if (it->is<std::string>())
                            {
                                output += it->get<std::string>();
                            }
                        }
                    }
                }
                return output;
            }
        }

        if (v.is<picojson::null>())
        {
            return "";
        }

        if (v.is<std::string>())
        {
            return v.get<std::string>();
        }

        if (v.is<picojson::array>())
        {
            std::string output;
            const picojson::array &a = v.get<picojson::array>();
            for (auto it = a.begin(); it != a.end(); ++it)
            {
                output += ParseChat(it->to_str());
            }
            return output;
        }

        return "";
    }

    const picojson::value Chat::SerializeImpl() const
    {
        picojson::value value(picojson::object_type, false);
        picojson::object &object = value.get<picojson::object>();

        object["from"] = picojson::value(from);
        object["text"] = picojson::value(text);

        return value;
    }
}
#include "botcraft/Game/PlayerInformation.hpp"

namespace Botcraft
{
    PlayerInformation::PlayerInformation()
    {

    }

    const std::string& PlayerInformation::GetUUID() const
    {
        return uuid;
    }

    const std::string& PlayerInformation::GetName() const
    {
        return name;
    }

    const GameMode PlayerInformation::GetGamemode() const
    {
        return gamemode;
    }

    const int PlayerInformation::GetPing() const
    {
        return ping;
    }

    const bool PlayerInformation::GetHasDisplayName() const
    {
        return has_display_name;
    }

    const Chat& PlayerInformation::GetDisplayName() const
    {
        return display_name;
    }

    const std::vector<PlayerProperty>& PlayerInformation::GetProperties() const
    {
        return properties;
    }

    std::vector<PlayerProperty>& PlayerInformation::GetProperties()
    {
        return properties;
    }

    void PlayerInformation::SetUUID(const std::string &s)
    {
        uuid = s;
    }

    void PlayerInformation::SetName(const std::string &s)
    {
        name = s;
    }

    void PlayerInformation::SetGamemode(const GameMode g)
    {
        gamemode = g;
    }

    void PlayerInformation::SetPing(const int i)
    {
        ping = i;
    }

    void PlayerInformation::SetHasDisplayName(const bool b)
    {
        has_display_name = b;
    }

    void PlayerInformation::SetDisplayName(const Chat &c)
    {
        display_name = c;
    }

    void PlayerInformation::SetProperties(const std::vector<PlayerProperty> &p)
    {
        properties = p;
    }

    const picojson::value PlayerInformation::SerializeImpl() const
    {
        picojson::value val(picojson::object_type, false);
        picojson::object& object = val.get<picojson::object>();

        object["uuid"] = picojson::value(uuid);
        object["name"] = picojson::value(name);
        object["gamemode"] = picojson::value((double)gamemode);
        object["ping"] = picojson::value((double)ping);
        object["has_display_name"] = picojson::value(has_display_name);
        object["display_name"] = display_name.Serialize();
        object["properties"] = picojson::value(picojson::array_type, false);
        
        picojson::array& array = object["properties"].get<picojson::array>();
        array.reserve(properties.size());
        for (int i = 0; i < properties.size(); ++i)
        {
            array.push_back(properties[i].Serialize());
        }

        return val;
    }

} //Botcraft
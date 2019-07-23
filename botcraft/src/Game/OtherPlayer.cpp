#include "botcraft/Game/OtherPlayer.hpp"

namespace Botcraft
{
    OtherPlayer::OtherPlayer()
    {

    }

    const std::string& OtherPlayer::GetUUID() const
    {
        return uuid;
    }

    const std::string& OtherPlayer::GetName() const
    {
        return name;
    }

    const GameMode OtherPlayer::GetGamemode() const
    {
        return gamemode;
    }

    const int OtherPlayer::GetPing() const
    {
        return ping;
    }

    const bool OtherPlayer::GetHasDisplayName() const
    {
        return has_display_name;
    }

    const Chat& OtherPlayer::GetDisplayName() const
    {
        return display_name;
    }

    const std::vector<PlayerProperty>& OtherPlayer::GetProperties() const
    {
        return properties;
    }

    std::vector<PlayerProperty>& OtherPlayer::GetProperties()
    {
        return properties;
    }

    void OtherPlayer::SetUUID(const std::string &s)
    {
        uuid = s;
    }

    void OtherPlayer::SetName(const std::string &s)
    {
        name = s;
    }

    void OtherPlayer::SetGamemode(const GameMode g)
    {
        gamemode = g;
    }

    void OtherPlayer::SetPing(const int i)
    {
        ping = i;
    }

    void OtherPlayer::SetHasDisplayName(const bool b)
    {
        has_display_name = b;
    }

    void OtherPlayer::SetDisplayName(const Chat &c)
    {
        display_name = c;
    }

    void OtherPlayer::SetProperties(const std::vector<PlayerProperty> &p)
    {
        properties = p;
    }

} //Botcraft
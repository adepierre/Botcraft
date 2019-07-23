#pragma once

#include <string>

#include "botcraft/Game/Enums.hpp"

#include "botcraft/Protocol/Types/Chat.hpp"
#include "botcraft/Protocol/Types/PlayerProperty.hpp"


namespace Botcraft 
{
    class OtherPlayer
    {
    public:
        OtherPlayer();

        const std::string& GetUUID() const;
        const std::string& GetName() const;
        const GameMode GetGamemode() const;
        const int GetPing() const;
        const bool GetHasDisplayName() const;
        const Chat& GetDisplayName() const;
        const std::vector<PlayerProperty>& GetProperties() const;
        std::vector<PlayerProperty>& GetProperties();

        void SetUUID(const std::string &s);
        void SetName(const std::string &s);
        void SetGamemode(const GameMode g);
        void SetPing(const int i);
        void SetHasDisplayName(const bool b);
        void SetDisplayName(const Chat &c);
        void SetProperties(const std::vector<PlayerProperty> &p);

    private:
        std::string uuid;
        std::string name;
        GameMode gamemode;
        int ping;
        bool has_display_name;
        Chat display_name;
        std::vector<PlayerProperty> properties;
    };
} // Botcraft
#pragma once

#include <string>

#include "botcraft/Game/Enums.hpp"

#include "botcraft/Protocol/NetworkType.hpp"
#include "botcraft/Protocol/Types/Chat.hpp"
#include "botcraft/Protocol/Types/PlayerProperty.hpp"


namespace Botcraft 
{
    class PlayerInformation : public NetworkType
    {
    public:
        PlayerInformation();

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

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            name = ReadString(iter, length);
            const int number_of_properties = ReadVarInt(iter, length);
            properties = std::vector<PlayerProperty>(number_of_properties);
            for (int i = 0; i < number_of_properties; ++i)
            {
                properties[i].Read(iter, length);
            }
            gamemode = (GameMode)ReadVarInt(iter, length);
            ping = ReadVarInt(iter, length);
            has_display_name = ReadData<bool>(iter, length);
            if (has_display_name)
            {
                display_name.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            std::cerr << "Clientbound type" << std::endl;
        }

        virtual const picojson::value SerializeImpl() const override;

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
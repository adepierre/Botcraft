#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat.hpp"
#include "protocolCraft/Types/PlayerProperty.hpp"


namespace ProtocolCraft 
{
    class PlayerInformation : public NetworkType
    {
    public:
        
        void SetUUID(const std::string& s)
        {
            uuid = s;
        }

        void SetName(const std::string& s)
        {
            name = s;
        }

        void SetGamemode(const int g)
        {
            gamemode = g;
        }

        void SetPing(const int i)
        {
            ping = i;
        }

        void SetHasDisplayName(const bool b)
        {
            has_display_name = b;
        }

        void SetDisplayName(const Chat& c)
        {
            display_name = c;
        }

        void SetProperties(const std::vector<PlayerProperty>& p)
        {
            properties = p;
        }

        const std::string& GetUUID() const
        {
            return uuid;
        }

        const std::string& GetName() const
        {
            return name;
        }

        const int GetGamemode() const
        {
            return gamemode;
        }

        const int GetPing() const
        {
            return ping;
        }

        const bool GetHasDisplayName() const
        {
            return has_display_name;
        }

        const Chat& GetDisplayName() const
        {
            return display_name;
        }

        const std::vector<PlayerProperty>& GetProperties() const
        {
            return properties;
        }

        std::vector<PlayerProperty>& GetProperties()
        {
            return properties;
        }

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
            gamemode = ReadVarInt(iter, length);
            ping = ReadVarInt(iter, length);
            has_display_name = ReadData<bool>(iter, length);
            if (has_display_name)
            {
                display_name.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(name, container);
            WriteVarInt(properties.size(), container);
            for (int i = 0; i < properties.size(); ++i)
            {
                properties[i].Write(container);
            }
            WriteVarInt(gamemode, container);
            WriteVarInt(ping, container);
            WriteData<bool>(has_display_name, container);
            if (has_display_name)
            {
                display_name.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
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

    private:
        std::string uuid;
        std::string name;
        int gamemode;
        int ping;
        bool has_display_name;
        Chat display_name;
        std::vector<PlayerProperty> properties;
    };
} // Botcraft
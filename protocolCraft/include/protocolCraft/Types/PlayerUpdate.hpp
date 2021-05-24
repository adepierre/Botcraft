#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat.hpp"
#include "protocolCraft/Types/PlayerProperty.hpp"


namespace ProtocolCraft 
{
    class PlayerUpdate : public NetworkType
    {
    public:
        virtual ~PlayerUpdate() override
        {

        }

        void SetName(const std::string& s)
        {
            name = s;
        }

        void SetGameMode(const int g)
        {
            game_mode = g;
        }

        void SetLatency(const int i)
        {
            latency = i;
        }

        void SetDisplayName(const Chat& c)
        {
            display_name = c;
        }

        void SetProperties(const std::vector<PlayerProperty>& p)
        {
            properties = p;
        }


        const std::string& GetName() const
        {
            return name;
        }

        const int GetGameMode() const
        {
            return game_mode;
        }

        const int GetLatency() const
        {
            return latency;
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
            game_mode = ReadVarInt(iter, length);
            latency = ReadVarInt(iter, length);
            const bool has_display_name = ReadData<bool>(iter, length);
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
            WriteVarInt(game_mode, container);
            WriteVarInt(latency, container);
            WriteData<bool>(!display_name.GetText().empty() , container);
            if (!display_name.GetText().empty())
            {
                display_name.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

            object["name"] = picojson::value(name);
            object["game_mode"] = picojson::value((double)game_mode);
            object["latency"] = picojson::value((double)latency);
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
        std::string name;
        int game_mode;
        int latency;
        Chat display_name;
        std::vector<PlayerProperty> properties;
    };
} // Botcraft
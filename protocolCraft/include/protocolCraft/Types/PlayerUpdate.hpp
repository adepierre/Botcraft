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
            name = ReadData<std::string>(iter, length);
            const int number_of_properties = ReadData<VarInt>(iter, length);
            properties = std::vector<PlayerProperty>(number_of_properties);
            for (int i = 0; i < number_of_properties; ++i)
            {
                properties[i].Read(iter, length);
            }
            game_mode = ReadData<VarInt>(iter, length);
            latency = ReadData<VarInt>(iter, length);
            const bool has_display_name = ReadData<bool>(iter, length);
            if (has_display_name)
            {
                display_name.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name, container);
            WriteData<VarInt>(properties.size(), container);
            for (int i = 0; i < properties.size(); ++i)
            {
                properties[i].Write(container);
            }
            WriteData<VarInt>(game_mode, container);
            WriteData<VarInt>(latency, container);
            WriteData<bool>(!display_name.GetText().empty() , container);
            if (!display_name.GetText().empty())
            {
                display_name.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["name"] = name;
            output["game_mode"] = game_mode;
            output["latency"] = latency;
            output["display_name"] = display_name.Serialize();
            output["properties"] = nlohmann::json::array();
            for (int i = 0; i < properties.size(); ++i)
            {
                output["properties"].push_back(properties[i].Serialize());
            }

            return output;
        }

    private:
        std::string name;
        int game_mode;
        int latency;
        Chat display_name;
        std::vector<PlayerProperty> properties;
    };
} // Botcraft
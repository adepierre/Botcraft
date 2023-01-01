#if PROTOCOL_VERSION < 761
#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"
#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

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

        void SetProperties(const std::vector<GameProfileProperty>& p)
        {
            properties = p;
        }

#if PROTOCOL_VERSION > 758
        void SetProfilePublicKey(const ProfilePublicKey& profile_public_key_)
        {
            profile_public_key = profile_public_key_;
        }
#endif


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

        const std::vector<GameProfileProperty>& GetProperties() const
        {
            return properties;
        }

        std::vector<GameProfileProperty>& GetProperties()
        {
            return properties;
        }

#if PROTOCOL_VERSION > 758
        const ProfilePublicKey& GetProfilePublicKey() const
        {
            return profile_public_key;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            name = ReadData<std::string>(iter, length);
            const int number_of_properties = ReadData<VarInt>(iter, length);
            properties = std::vector<GameProfileProperty>(number_of_properties);
            for (int i = 0; i < number_of_properties; ++i)
            {
                properties[i].Read(iter, length);
            }
            game_mode = ReadData<VarInt>(iter, length);
            latency = ReadData<VarInt>(iter, length);
            const bool has_display_name = ReadData<bool>(iter, length);
            display_name = Chat();
            if (has_display_name)
            {
                display_name = ReadData<Chat>(iter, length);
            }
#if PROTOCOL_VERSION > 758
            const bool has_profile_public_key = ReadData<bool>(iter, length);
            profile_public_key = ProfilePublicKey();
            if (has_profile_public_key)
            {
                profile_public_key = ReadData<ProfilePublicKey>(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name, container);
            WriteData<VarInt>(static_cast<int>(properties.size()), container);
            for (int i = 0; i < properties.size(); ++i)
            {
                properties[i].Write(container);
            }
            WriteData<VarInt>(game_mode, container);
            WriteData<VarInt>(latency, container);
            WriteData<bool>(!display_name.GetText().empty() , container);
            if (!display_name.GetText().empty())
            {
                WriteData<Chat>(display_name, container);
            }
#if PROTOCOL_VERSION > 758
            WriteData<bool>(!profile_public_key.GetKey().empty(), container);
            if (!profile_public_key.GetKey().empty())
            {
                WriteData<ProfilePublicKey>(profile_public_key, container);
            }
#endif
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
#if PROTOCOL_VERSION > 758
            if (!profile_public_key.GetKey().empty())
            {
                output["profile_public_key"] = profile_public_key.Serialize();
            }
#endif


            return output;
        }

    private:
        std::string name;
        int game_mode;
        int latency;
        Chat display_name;
        std::vector<GameProfileProperty> properties;
#if PROTOCOL_VERSION > 758
        ProfilePublicKey profile_public_key;
#endif
    };
} // ProtocolCraft
#endif

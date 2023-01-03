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

        void SetDisplayName(const std::optional<Chat>& c)
        {
            display_name = c;
        }

        void SetProperties(const std::vector<GameProfileProperty>& p)
        {
            properties = p;
        }

#if PROTOCOL_VERSION > 758
        void SetProfilePublicKey(const std::optional<ProfilePublicKey>& profile_public_key_)
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

        const std::optional<Chat>& GetDisplayName() const
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
        const std::optional<ProfilePublicKey>& GetProfilePublicKey() const
        {
            return profile_public_key;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            name = ReadData<std::string>(iter, length);
            properties = ReadVector<GameProfileProperty>(iter, length);
            game_mode = ReadData<VarInt>(iter, length);
            latency = ReadData<VarInt>(iter, length);
            display_name = ReadOptional<Chat>(iter, length);
#if PROTOCOL_VERSION > 758
            profile_public_key = ReadOptional<ProfilePublicKey>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name, container);
            WriteVector<GameProfileProperty>(properties, container);
            WriteData<VarInt>(game_mode, container);
            WriteData<VarInt>(latency, container);
            WriteOptional<Chat>(display_name, container);
#if PROTOCOL_VERSION > 758
            WriteOptional<ProfilePublicKey>(profile_public_key, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["name"] = name;
            output["game_mode"] = game_mode;
            output["latency"] = latency;
            if (display_name.has_value())
            {
                output["display_name"] = display_name.value().Serialize();
            }
            output["properties"] = nlohmann::json::array();
            for (const auto& p : properties)
            {
                output["properties"].push_back(p.Serialize());
            }
#if PROTOCOL_VERSION > 758
            if (profile_public_key.has_value())
            {
                output["profile_public_key"] = profile_public_key.value().Serialize();
            }
#endif


            return output;
        }

    private:
        std::string name;
        int game_mode;
        int latency;
        std::optional<Chat> display_name;
        std::vector<GameProfileProperty> properties;
#if PROTOCOL_VERSION > 758
        std::optional<ProfilePublicKey> profile_public_key;
#endif
    };
} // ProtocolCraft
#endif

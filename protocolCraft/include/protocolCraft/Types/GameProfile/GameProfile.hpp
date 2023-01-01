#if PROTOCOL_VERSION > 758
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <string>
#include <map>

namespace ProtocolCraft 
{
    class GameProfile : public NetworkType
    {
    public:

        GameProfile()
        {

        }

        virtual ~GameProfile() override
        {

        }


        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetName(const std::string& name_)
        {
            name = name_;
        }

        void SetProperties(const std::map<std::string, GameProfileProperty>& properties_)
        {
            properties = properties_;
        }


        const UUID& GetUUID() const
        {
            return uuid;
        }

        const std::string& GetName() const
        {
            return name;
        }

        const std::map<std::string, GameProfileProperty>& GetProperties() const
        {
            return properties;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            uuid = ReadData<UUID>(iter, length);
            name = ReadData<std::string>(iter, length);
            properties.clear();
            const int properties_length = ReadData<VarInt>(iter, length);
            for (size_t i = 0; i < properties_length; ++i)
            {
                GameProfileProperty prop;
                prop = ReadData<GameProfileProperty>(iter, length);
                properties[prop.GetName()] = prop;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<UUID>(uuid, container);
            WriteData<std::string>(name, container);
            WriteData<VarInt>(static_cast<int>(properties.size()), container);
            for (const auto& p : properties)
            {
                WriteData<GameProfileProperty>(p.second, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["uuid"] = uuid;
            output["name"] = name;
            output["properties"] = nlohmann::json::array();
            for (const auto& p: properties)
            {
                output["properties"].push_back(p.second.Serialize());
            }


            return output;
        }

    private:
        UUID uuid;
        std::string name;
        std::map<std::string, GameProfileProperty> properties;
    };
} // ProtocolCraft
#endif

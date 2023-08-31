#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <string>

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

        void SetProperties(const std::vector<GameProfileProperty>& properties_)
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

        const std::vector<GameProfileProperty>& GetProperties() const
        {
            return properties;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            uuid = ReadData<UUID>(iter, length);
            name = ReadData<std::string>(iter, length);
            properties = ReadVector<GameProfileProperty>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<UUID>(uuid, container);
            WriteData<std::string>(name, container);
            WriteVector<GameProfileProperty>(properties, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["uuid"] = uuid;
            output["name"] = name;
            output["properties"] = properties;


            return output;
        }

    private:
        UUID uuid = {};
        std::string name;
        std::vector<GameProfileProperty> properties;
    };
} // ProtocolCraft
#endif

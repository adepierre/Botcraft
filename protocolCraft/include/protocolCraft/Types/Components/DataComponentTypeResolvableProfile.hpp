#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"

#include <optional>
#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeResolvableProfile : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeResolvableProfile()
            {

            }


            const std::optional<std::string>& GetName() const
            {
                return name;
            }

            const std::optional<UUID>& GetUUID() const
            {
                return uuid;
            }

            const std::vector<GameProfileProperty>& GetProperties() const
            {
                return properties;
            }


            void SetName(const std::optional<std::string>& name_)
            {
                name = name_;
            }

            void SetUUID(const std::optional<UUID>& uuid_)
            {
                uuid = uuid_;
            }

            void SetProperties(const std::vector<GameProfileProperty>& properties_)
            {
                properties = properties_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                name = ReadData<std::optional<std::string>>(iter, length);
                uuid = ReadData<std::optional<UUID>>(iter, length);
                properties = ReadData<std::vector<GameProfileProperty>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::optional<std::string>>(name, container);
                WriteData<std::optional<UUID>>(uuid, container);
                WriteData<std::vector<GameProfileProperty>>(properties, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                if (name.has_value())
                {
                    output["name"] = name.value();
                }
                if (uuid.has_value())
                {
                    output["uuid"] = uuid.value();
                }
                output["properties"] = properties;

                return output;
            }

        private:
            std::optional<std::string> name;
            std::optional<UUID> uuid;
            std::vector<GameProfileProperty> properties;

        };
    }
}
#endif

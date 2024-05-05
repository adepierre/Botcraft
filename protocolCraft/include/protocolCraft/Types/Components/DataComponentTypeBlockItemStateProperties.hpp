#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include <map>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBlockItemStateProperties : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeBlockItemStateProperties()
            {

            }


            const std::map<std::string, std::string>& GetProperties() const
            {
                return properties;
            }


            void SetProperties(const std::map<std::string, std::string>& properties_)
            {
                properties = properties_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                properties = ReadMap<std::string, std::string>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteMap<std::string, std::string>(properties, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["properties"] = properties;

                return output;
            }

        private:
            std::map<std::string, std::string> properties;

        };
    }
}
#endif

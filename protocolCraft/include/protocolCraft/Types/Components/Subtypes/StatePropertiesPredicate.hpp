#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/PropertyMatcher.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class StatePropertiesPredicate : public NetworkType
        {
        public:
            virtual ~StatePropertiesPredicate()
            {

            }


            const std::vector<PropertyMatcher>& GetProperties() const
            {
                return properties;
            }


            void SetProperties(const std::vector<PropertyMatcher>& properties_)
            {
                properties = properties_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                properties = ReadData<std::vector<PropertyMatcher>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<PropertyMatcher>>(properties, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["properties"] = properties;

                return output;
            }

        private:
            std::vector<PropertyMatcher> properties;

        };
    }
}
#endif

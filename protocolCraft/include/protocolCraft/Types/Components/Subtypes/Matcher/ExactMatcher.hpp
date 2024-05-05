#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/Subtypes/Matcher/ValueMatcher.hpp"

#include <string>

namespace ProtocolCraft
{
    namespace Components
    {
        class ExactMatcher : public ValueMatcher
        {
        public:
            virtual ~ExactMatcher()
            {

            }


            const std::string& GetValue() const
            {
                return value;
            }


            void SetValue(const std::string& value_)
            {
                value = value_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                value = ReadData<std::string>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::string>(value, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["value"] = value;

                return output;
            }

        private:
            std::string value;

        };
    }
}
#endif

#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/Subtypes/Matcher/ValueMatcher.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class RangedMatcher : public ValueMatcher
        {
        public:
            virtual ~RangedMatcher()
            {

            }


            const std::optional<std::string>& GetMinValue() const
            {
                return min_value;
            }

            const std::optional<std::string>& GetMaxValue() const
            {
                return max_value;
            }


            void SetMinValue(const std::optional<std::string>& min_value_)
            {
                min_value = min_value_;
            }

            void SetMaxValue(const std::optional<std::string>& max_value_)
            {
                max_value = max_value_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                min_value = ReadOptional<std::string>(iter, length);
                max_value = ReadOptional<std::string>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteOptional<std::string>(min_value, container);
                WriteOptional<std::string>(max_value, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                if (min_value.has_value())
                {
                    output["min_value"] = min_value.value();
                }
                if (max_value.has_value())
                {
                    output["max_value"] = max_value.value();
                }

                return output;
            }

        private:
            std::optional<std::string> min_value;
            std::optional<std::string> max_value;

        };
    }
}
#endif

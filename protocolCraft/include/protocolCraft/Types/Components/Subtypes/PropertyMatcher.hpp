#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/ValueMatcher.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/ExactMatcher.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/RangedMatcher.hpp"

#include <string>
#include <memory>

namespace ProtocolCraft
{
    namespace Components
    {
        enum class ValueMatcherType
        {
            None = -1,
            Exact,
            Ranged,
            NUM_VALUE_MATCHER_TYPES
        };

        class PropertyMatcher : public NetworkType
        {
        public:
            virtual ~PropertyMatcher()
            {

            }


            const std::string& GetName() const
            {
                return name;
            }

            ValueMatcherType GetValueMatcherType() const
            {
                return value_matcher_type;
            }

            std::shared_ptr<ValueMatcher> GetValueMatcher() const
            {
                return value_matcher;
            }


            void SetName(const std::string& name_)
            {
                name = name_;
            }

            void SetValueMatcherType(const ValueMatcherType value_matcher_type_)
            {
                value_matcher_type = value_matcher_type_;
                if (value_matcher_type_ == ValueMatcherType::None || value_matcher_type >= ValueMatcherType::NUM_VALUE_MATCHER_TYPES)
                {
                    throw std::runtime_error("Unable to create value matcher with id: " + std::to_string(static_cast<int>(value_matcher_type_)) + ".");
                }
                switch (value_matcher_type)
                {
                case ValueMatcherType::Exact:
                    value_matcher = std::make_shared<ExactMatcher>();
                    break;
                case ValueMatcherType::Ranged:
                    value_matcher = std::make_shared<RangedMatcher>();
                    break;
                default:
                    // Should not happen
                    value_matcher = nullptr;
                    break;
                }
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                name = ReadData<std::string>(iter, length);
                SetValueMatcherType(ReadData<bool>(iter, length) ? ValueMatcherType::Exact : ValueMatcherType::Ranged);
                value_matcher->Read(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::string>(name, container);
                WriteData<bool>(value_matcher_type == ValueMatcherType::Ranged, container);
                if (value_matcher != nullptr)
                {
                    value_matcher->Write(container);
                }
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["name"] = name;
                if (value_matcher != nullptr)
                {
                    output["value_matcher"] = *value_matcher;
                }

                return output;
            }

        private:
            std::string name;
            ValueMatcherType value_matcher_type = ValueMatcherType::None;
            std::shared_ptr<ValueMatcher> value_matcher;

        };
    }
}
#endif

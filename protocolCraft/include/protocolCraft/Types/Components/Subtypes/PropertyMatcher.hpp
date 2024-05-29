#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
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
            DECLARE_FIELDS_TYPES(std::string, ValueMatcherType, std::shared_ptr<ValueMatcher>);
            DECLARE_FIELDS_NAMES(Name,        ValueMatcherType, ValueMatcher);

            GETTER_SETTER(Name);
            GETTER_SETTER(ValueMatcher);
        public:
            ValueMatcherType GetValueMatcherType() const
            {
                return std::get<static_cast<size_t>(FieldsEnum::ValueMatcherType)>(fields);
            }

            void SetValueMatcherType(const ValueMatcherType value_matcher_type_)
            {
                std::get<static_cast<size_t>(FieldsEnum::ValueMatcherType)>(fields) = value_matcher_type_;
                if (value_matcher_type_ == ValueMatcherType::None || value_matcher_type_ >= ValueMatcherType::NUM_VALUE_MATCHER_TYPES)
                {
                    throw std::runtime_error("Unable to create value matcher with id: " + std::to_string(static_cast<int>(value_matcher_type_)) + ".");
                }
                switch (value_matcher_type_)
                {
                case ValueMatcherType::Exact:
                    std::get<static_cast<size_t>(FieldsEnum::ValueMatcher)>(fields) = std::make_shared<ExactMatcher>();
                    break;
                case ValueMatcherType::Ranged:
                    std::get<static_cast<size_t>(FieldsEnum::ValueMatcher)>(fields) = std::make_shared<RangedMatcher>();
                    break;
                default:
                    // Should not happen
                    std::get<static_cast<size_t>(FieldsEnum::ValueMatcher)>(fields) = nullptr;
                    break;
                }
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                SetName(ReadData<std::string>(iter, length));
                SetValueMatcherType(ReadData<bool>(iter, length) ? ValueMatcherType::Exact : ValueMatcherType::Ranged);
                GetValueMatcher()->Read(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::string>(GetName(), container);
                WriteData<bool>(GetValueMatcherType() == ValueMatcherType::Ranged, container);
                if (GetValueMatcher() != nullptr)
                {
                    GetValueMatcher()->Write(container);
                }
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Name)])] = GetName();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ValueMatcherType)])] = GetValueMatcherType();
                if (GetValueMatcher() != nullptr)
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::ValueMatcher)])] = *GetValueMatcher();
                }

                return output;
            }
        };
    }
}
#endif

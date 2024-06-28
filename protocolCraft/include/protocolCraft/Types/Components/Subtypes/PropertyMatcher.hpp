#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/ExactMatcher.hpp"
#include "protocolCraft/Types/Components/Subtypes/Matcher/RangedMatcher.hpp"

#include <string>
#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class PropertyMatcher : public NetworkType
        {
        private: using THIS = PropertyMatcher;

            DECLARE_CONDITION(IsExactMatcher, GetIsExactMatcher());
            DECLARE_CONDITION(IsRangedMatcher, !GetIsExactMatcher());

            DECLARE_FIELDS(
                (std::string, bool,           Internal::Conditioned<RangedMatcher, &THIS::IsRangedMatcher>, Internal::Conditioned<ExactMatcher, &THIS::IsExactMatcher>),
                (Name,        IsExactMatcher, RangedMatcher,                                                ExactMatcher)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Name);
            GETTER       (RangedMatcher);
            GETTER       (ExactMatcher);

        protected:
            bool GetIsExactMatcher() const
            {
                return std::get<static_cast<size_t>(FieldsEnum::IsExactMatcher)>(fields);
            }

        public:
            auto& SetRangedMatcher(const std::optional<RangedMatcher>& ranged_matcher)
            {
                std::get<static_cast<size_t>(FieldsEnum::RangedMatcher)>(fields) = ranged_matcher;
                std::get<static_cast<size_t>(FieldsEnum::IsExactMatcher)>(fields) = !ranged_matcher.has_value();
                if (ranged_matcher.has_value())
                {
                    std::get<static_cast<size_t>(FieldsEnum::ExactMatcher)>(fields) = std::nullopt;
                }
                return *this;
            }

            auto& SetExactMatcher(const std::optional<ExactMatcher>& exact_matcher)
            {
                std::get<static_cast<size_t>(FieldsEnum::ExactMatcher)>(fields) = exact_matcher;
                std::get<static_cast<size_t>(FieldsEnum::IsExactMatcher)>(fields) = exact_matcher.has_value();
                if (exact_matcher.has_value())
                {
                    std::get<static_cast<size_t>(FieldsEnum::RangedMatcher)>(fields) = std::nullopt;
                }
                return *this;
            }
        };
    }
}
#endif

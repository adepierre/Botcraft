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
            DECLARE_FIELDS_TYPES(std::string, std::optional<RangedMatcher>, std::optional<ExactMatcher>);
            DECLARE_FIELDS_NAMES(Name,        RangedMatcher,                ExactMatcher);
            DECLARE_SERIALIZE;

            GETTER_SETTER(Name);

            const std::optional<RangedMatcher>& GetRangedMatcher() const
            {
                return std::get<static_cast<size_t>(FieldsEnum::RangedMatcher)>(fields);
            }

            auto& SetRangedMatcher(const std::optional<RangedMatcher>& ranged_matcher)
            {
                std::get<static_cast<size_t>(FieldsEnum::RangedMatcher)>(fields) = ranged_matcher;
                if (ranged_matcher.has_value())
                {
                    std::get<static_cast<size_t>(FieldsEnum::ExactMatcher)>(fields) = {};
                }
                return *this;
            }


            const std::optional<ExactMatcher>& GetExactMatcher() const
            {
                return std::get<static_cast<size_t>(FieldsEnum::ExactMatcher)>(fields);
            }

            auto& SetExactMatcher(const std::optional<ExactMatcher>& exact_matcher)
            {
                std::get<static_cast<size_t>(FieldsEnum::ExactMatcher)>(fields) = exact_matcher;
                if (exact_matcher.has_value())
                {
                    std::get<static_cast<size_t>(FieldsEnum::RangedMatcher)>(fields) = {};
                }
                return *this;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                SetName(ReadData<std::string>(iter, length));
                const bool is_exact_matcher = ReadData<bool>(iter, length);
                if (is_exact_matcher)
                {
                    SetExactMatcher(ReadData<ExactMatcher>(iter, length));
                }
                else
                {
                    SetRangedMatcher(ReadData<RangedMatcher>(iter, length));
                }
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::string>(GetName(), container);
                const bool is_exact_matcher = GetExactMatcher().has_value();
                WriteData<bool>(is_exact_matcher, container);
                if (is_exact_matcher)
                {
                    WriteData<ExactMatcher>(GetExactMatcher().value(), container);
                }
                else
                {
                    WriteData<RangedMatcher>(GetRangedMatcher().value(), container);
                }
            }
        };
    }
}
#endif

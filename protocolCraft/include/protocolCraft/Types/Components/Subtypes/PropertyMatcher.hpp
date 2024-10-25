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

            DEFINE_CONDITION(IsExactMatcher, GetIsExactMatcher());
            DEFINE_CONDITION(IsRangedMatcher, !GetIsExactMatcher());

            SERIALIZED_FIELD(Name, std::string);
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(IsExactMatcher_, bool);
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(RangedMatcher, Internal::Conditioned<ProtocolCraft::Components::RangedMatcher, &THIS::IsRangedMatcher>);
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ExactMatcher, Internal::Conditioned<ProtocolCraft::Components::ExactMatcher, &THIS::IsExactMatcher>);

            DECLARE_READ_WRITE_SERIALIZE;

            GETTER(RangedMatcher);
            GETTER(ExactMatcher);

        protected:
            bool GetIsExactMatcher() const
            {
                return IsExactMatcher_;
            }

        public:
            auto& SetRangedMatcher(const std::optional<ProtocolCraft::Components::RangedMatcher>& RangedMatcher_)
            {
                RangedMatcher = RangedMatcher_;
                IsExactMatcher_ = !RangedMatcher.has_value();
                if (RangedMatcher.has_value())
                {
                    ExactMatcher = std::nullopt;
                }
                return *this;
            }

            auto& SetExactMatcher(const std::optional<ProtocolCraft::Components::ExactMatcher>& ExactMatcher_)
            {
                ExactMatcher = ExactMatcher_;
                IsExactMatcher_ = ExactMatcher.has_value();
                if (ExactMatcher.has_value())
                {
                    RangedMatcher = std::nullopt;
                }
                return *this;
            }
        };
    }
}
#endif

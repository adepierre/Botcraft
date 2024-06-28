#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class FilterMask : public NetworkType
    {
        DECLARE_CONDITION(IsType2, GetType() == 2);

        DECLARE_FIELDS(
            (VarInt, Internal::Conditioned<std::vector<long long int>, &FilterMask::IsType2>),
            (Type,   Mask)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Type);
    public:
        const std::optional<std::vector<long long int>>& GetMask() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::Mask)>(fields);
        }

        auto& SetMask(const std::optional<std::vector<long long int>>& Mask)
        {
            if (Mask.has_value())
            {
                SetType(2);
            }
            std::get<static_cast<size_t>(FieldsEnum::Mask)>(fields) = Mask;
            return *this;
        }
    };
}
#endif

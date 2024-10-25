#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class FilterMask : public NetworkType
    {
        DEFINE_CONDITION(IsType2, GetType() == 2);

        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Mask, Internal::Conditioned<std::vector<long long int>, &FilterMask::IsType2>);

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(Mask);

    public:
        auto& SetMask(const std::optional<std::vector<long long int>>& Mask_)
        {
            if (Mask_.has_value())
            {
                SetType(2);
            }
            Mask = Mask_;
            return *this;
        }
    };
}
#endif

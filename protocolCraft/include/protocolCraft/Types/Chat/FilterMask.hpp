#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class FilterMask : public NetworkType
    {
        DECLARE_FIELDS_TYPES(VarInt, std::optional<std::vector<long long int>>);
        DECLARE_FIELDS_NAMES(Type, Mask);
        DECLARE_SERIALIZE;

    public:
        GETTER_SETTER(Type);
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

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetType(ReadData<VarInt>(iter, length));
            if (GetType() == 2)
            {
                SetMask(ReadData<std::vector<long long int>>(iter, length));
            }
            else
            {
                SetMask({});
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetType(), container);
            if (GetType() == 2) // Should always have value if type is 2
            {
                WriteData<std::vector<long long int>>(GetMask().value(), container);
            }
        }
    };
}
#endif

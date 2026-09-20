#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include <optional>

namespace ProtocolCraft
{
    class OptionalVarInt : public NetworkType
    {
    private:
        std::optional<int> ReadValue(ReadIterator& iter, size_t& length) const
        {
            const int i = ReadData<VarInt>(iter, length);
            if (i == 0)
            {
                return std::nullopt;
            }
            return i - 1;
        }

        void WriteValue(const std::optional<int>& i, WriteContainer& container) const
        {
            if (i.has_value())
            {
                WriteData<VarInt>(i.value() + 1, container);
            }
            else
            {
                WriteData<VarInt>(0, container);
            }
        }

        SERIALIZED_FIELD(Value, Internal::CustomType<std::optional<int>, &OptionalVarInt::ReadValue, &OptionalVarInt::WriteValue, nullptr>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

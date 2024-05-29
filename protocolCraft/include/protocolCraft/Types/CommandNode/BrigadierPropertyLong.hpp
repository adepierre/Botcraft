#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyLong : public BrigadierProperty
    {
        DECLARE_FIELDS_TYPES(char,  long long int, long long int);
        DECLARE_FIELDS_NAMES(Flags, Min,           Max);
        DECLARE_SERIALIZE;

        GETTER_SETTER(Flags);
        GETTER_SETTER(Min);
        GETTER_SETTER(Max);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetFlags(ReadData<char>(iter, length));
            if (GetFlags() & 0x01)
            {
                SetMin(ReadData<long long int>(iter, length));
            }
            else
            {
                SetMin(std::numeric_limits<long long int>::min());
            }
            if (GetFlags() & 0x02)
            {
                SetMax(ReadData<long long int>(iter, length));
            }
            else
            {
                SetMax(std::numeric_limits<long long int>::max());
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(GetFlags(), container);
            if (GetFlags() & 0x01)
            {
                WriteData<long long int>(GetMin(), container);
            }
            if (GetFlags() & 0x02)
            {
                WriteData<long long int>(GetMax(), container);
            }
        }
    };
}
#endif

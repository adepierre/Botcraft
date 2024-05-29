#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include <limits>

#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyFloat : public BrigadierProperty
    {
        DECLARE_FIELDS_TYPES(char,  float, float);
        DECLARE_FIELDS_NAMES(Flags, Min,   Max);
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
                SetMin(ReadData<float>(iter, length));
            }
            else
            {
                SetMin(-std::numeric_limits<float>::max());
            }
            if (GetFlags() & 0x02)
            {
                SetMax(ReadData<float>(iter, length));
            }
            else
            {
                SetMax(std::numeric_limits<float>::max());
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(GetFlags(), container);
            if (GetFlags() & 0x01)
            {
                WriteData<float>(GetMin(), container);
            }
            if (GetFlags() & 0x02)
            {
                WriteData<float>(GetMax(), container);
            }
        }
    };
}
#endif

#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

#include <limits>

namespace ProtocolCraft
{
    class BrigadierPropertyInteger : public BrigadierProperty
    {
        DECLARE_FIELDS(
            (char,  int, int),
            (Flags, Min, Max)
        );
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
                SetMin(ReadData<int>(iter, length));
            }
            else
            {
                SetMin(std::numeric_limits<int>::min());
            }
            if (GetFlags() & 0x02)
            {
                SetMax(ReadData<int>(iter, length));
            }
            else
            {
                SetMax(std::numeric_limits<int>::max());
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(GetFlags(), container);
            if (GetFlags() & 0x01)
            {
                WriteData<int>(GetMin(), container);
            }
            if (GetFlags() & 0x02)
            {
                WriteData<int>(GetMax(), container);
            }
        }
    };
}
#endif

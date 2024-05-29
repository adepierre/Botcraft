#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class NumberFormat : public NetworkType
    {
        DECLARE_FIELDS_TYPES(VarInt, std::optional<Chat>);
        DECLARE_FIELDS_NAMES(Type,   Format);
        DECLARE_SERIALIZE;

        GETTER_SETTER(Type);
        GETTER_SETTER(Format);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetType(ReadData<VarInt>(iter, length));
            if (GetType() != 0)
            {
                SetFormat(ReadData<Chat>(iter, length));
            }
            else
            {
                SetFormat({});
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetType(), container);
            if (GetType() != 0)
            {
                WriteData<Chat>(GetFormat().value(), container);
            }
        }
    };
} // ProtocolCraft
#endif

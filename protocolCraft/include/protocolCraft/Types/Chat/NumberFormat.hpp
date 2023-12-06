#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class NumberFormat : public NetworkType
    {
    public:
        virtual ~NumberFormat() override
        {

        }


        void SetType(const int type_)
        {
            type = type_;
        }

        void SetFormat(const Chat& format_)
        {
            format = format_;
        }


        int GetType() const
        {
            return type;
        }

        const Chat& GetFormat() const
        {
            return format;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = ReadData<VarInt>(iter, length);
            if (type != 0)
            {
                format = ReadData<Chat>(iter, length);
            }
            else
            {
                format = Chat();
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(type, container);
            if (type != 0)
            {
                WriteData<Chat>(format, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["type"] = type;
            if (type != 0)
            {
                output["format"] = format;
            }

            return output;
        }

    private:
        int type = 0;
        Chat format;
    };
} // ProtocolCraft
#endif

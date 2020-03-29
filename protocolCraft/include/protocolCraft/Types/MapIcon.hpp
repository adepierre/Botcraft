#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class MapIcon : public NetworkType
    {
    public:

#if PROTOCOL_VERSION < 373
        const char GetDirectionAndType() const
        {
            return direction_and_type;
        }
#else
        const int GetType() const
        {
            return type;
        }
#endif
        const char GetX() const
        {
            return x;
        }

        const char GetZ() const
        {
            return z;
        }

#if PROTOCOL_VERSION > 372
        const char GetDirection() const
        {
            return direction;
        }
#endif

#if PROTOCOL_VERSION > 363
        const bool GetHasDisplayName() const
        {
            return has_display_name;
        }

        const Chat& GetDisplayName() const
        {
            return display_name;
        }
#endif


#if PROTOCOL_VERSION < 373
        void SetDirectionAndType(const char direction_and_type_)
        {
            direction_and_type = direction_and_type_;
        }
#else
        void SetType(const int type_)
        {
            type = type_;
        }
#endif

        void SetX(const char x_)
        {
            x = x_;
        }

        void SetZ(const char z_)
        {
            z = z_;
        }

#if PROTOCOL_VERSION > 372
        void SetDirection(const char direction_)
        {
            direction = direction_;
        }
#endif

#if PROTOCOL_VERSION > 363
        void SetHasDisplayName(const bool has_display_name_)
        {
            has_display_name = has_display_name_;
        }

        void SetDisplayName(const Chat& display_name_)
        {
            display_name = display_name_;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 373
            direction_and_type = ReadData<char>(iter, length);
#else
            type = ReadVarInt(iter, length);
#endif
            x = ReadData<char>(iter, length);
            z = ReadData<char>(iter, length);

#if PROTOCOL_VERSION > 372
            direction = ReadData<char>(iter, length);
#endif

#if PROTOCOL_VERSION > 363
            has_display_name = ReadData<bool>(iter, length);
            if (has_display_name)
            {
                display_name.Read(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION < 373
            WriteData<char>(direction_and_type, container);
#else
            WriteVarInt(type, container);
#endif
            WriteData<char>(x, container);
            WriteData<char>(z, container);
#if PROTOCOL_VERSION > 372
            WriteData<char>(direction, container);
#endif

#if PROTOCOL_VERSION > 363
            WriteData<bool>(has_display_name, container);
            if (has_display_name)
            {
                display_name.Write(container);
            }
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

#if PROTOCOL_VERSION < 373
            object["direction_and_type"] = picojson::value((double)direction_and_type);
#else
            object["type"] = picojson::value((double)type);
#endif
            object["x"] = picojson::value((double)x);
            object["z"] = picojson::value((double)z);

#if PROTOCOL_VERSION > 372
            object["direction"] = picojson::value((double)direction);
#endif
#if PROTOCOL_VERSION > 363
            object["has_display_name"] = picojson::value(has_display_name);
            if (has_display_name)
            {
                object["display_name"] = display_name.Serialize();
            }
#endif

            return val;
        }

    private:
#if PROTOCOL_VERSION < 373
        char direction_and_type;
#else
        int type;
#endif
        char x;
        char z;
#if PROTOCOL_VERSION > 372
        char direction;
#endif
#if PROTOCOL_VERSION > 363
        bool has_display_name;
        Chat display_name;
#endif
    };
}
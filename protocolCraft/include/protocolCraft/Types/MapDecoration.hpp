#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class MapDecoration : public NetworkType
    {
    public:
        virtual ~MapDecoration() override
        {

        }

#if PROTOCOL_VERSION < 373
        char GetRotAndType() const
        {
            return rot_and_type;
        }
#else
        int GetType() const
        {
            return type;
        }
#endif
        char GetX() const
        {
            return x;
        }

        char GetZ() const
        {
            return z;
        }

#if PROTOCOL_VERSION > 372
        char GetRot() const
        {
            return rot;
        }
#endif

#if PROTOCOL_VERSION > 363
        const std::optional<Chat>& GetDisplayName() const
        {
            return display_name;
        }
#endif


#if PROTOCOL_VERSION < 373
        void SetRotAndType(const char rot_and_type_)
        {
            rot_and_type = rot_and_type_;
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
        void SetRot(const char rot_)
        {
            rot = rot_;
        }
#endif

#if PROTOCOL_VERSION > 363
        void SetDisplayName(const std::optional<Chat>& display_name_)
        {
            display_name = display_name_;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 373
            rot_and_type = ReadData<char>(iter, length);
#else
            type = ReadData<VarInt>(iter, length);
#endif
            x = ReadData<char>(iter, length);
            z = ReadData<char>(iter, length);

#if PROTOCOL_VERSION > 372
            rot = ReadData<char>(iter, length);
#endif

#if PROTOCOL_VERSION > 363
            display_name = ReadOptional<Chat>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION < 373
            WriteData<char>(rot_and_type, container);
#else
            WriteData<VarInt>(type, container);
#endif
            WriteData<char>(x, container);
            WriteData<char>(z, container);
#if PROTOCOL_VERSION > 372
            WriteData<char>(rot, container);
#endif

#if PROTOCOL_VERSION > 363
            WriteOptional<Chat>(display_name, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 373
            output["rot_and_type"] = rot_and_type;
#else
            output["type"] = type;
#endif
            output["x"] = x;
            output["z"] = z;

#if PROTOCOL_VERSION > 372
            output["rot"] = rot;
#endif
#if PROTOCOL_VERSION > 363
            if (display_name.has_value())
            {
                output["display_name"] = display_name.value().Serialize();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 373
        char rot_and_type;
#else
        int type;
#endif
        char x;
        char z;
#if PROTOCOL_VERSION > 372
        char rot;
#endif
#if PROTOCOL_VERSION > 363
        std::optional<Chat> display_name;
#endif
    };
}
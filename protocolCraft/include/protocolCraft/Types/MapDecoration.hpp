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

#if PROTOCOL_VERSION < 373 /* < 1.13 */
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

#if PROTOCOL_VERSION > 372 /* > 1.12.2 */
        char GetRot() const
        {
            return rot;
        }
#endif

#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
        const std::optional<Chat>& GetDisplayName() const
        {
            return display_name;
        }
#endif


#if PROTOCOL_VERSION < 373 /* < 1.13 */
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

#if PROTOCOL_VERSION > 372 /* > 1.12.2 */
        void SetRot(const char rot_)
        {
            rot = rot_;
        }
#endif

#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
        void SetDisplayName(const std::optional<Chat>& display_name_)
        {
            display_name = display_name_;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 373 /* < 1.13 */
            rot_and_type = ReadData<char>(iter, length);
#else
            type = ReadData<VarInt>(iter, length);
#endif
            x = ReadData<char>(iter, length);
            z = ReadData<char>(iter, length);

#if PROTOCOL_VERSION > 372 /* > 1.12.2 */
            rot = ReadData<char>(iter, length);
#endif

#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
            display_name = ReadData<std::optional<Chat>>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 373 /* < 1.13 */
            WriteData<char>(rot_and_type, container);
#else
            WriteData<VarInt>(type, container);
#endif
            WriteData<char>(x, container);
            WriteData<char>(z, container);
#if PROTOCOL_VERSION > 372 /* > 1.12.2 */
            WriteData<char>(rot, container);
#endif

#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
            WriteData<std::optional<Chat>>(display_name, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 373 /* < 1.13 */
            output["rot_and_type"] = rot_and_type;
#else
            output["type"] = type;
#endif
            output["x"] = x;
            output["z"] = z;

#if PROTOCOL_VERSION > 372 /* > 1.12.2 */
            output["rot"] = rot;
#endif
#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
            if (display_name.has_value())
            {
                output["display_name"] = display_name.value();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 373 /* < 1.13 */
        char rot_and_type = 0;
#else
        int type = 0;
#endif
        char x = 0;
        char z = 0;
#if PROTOCOL_VERSION > 372 /* > 1.12.2 */
        char rot = 0;
#endif
#if PROTOCOL_VERSION > 363 /* > 1.12.2 */
        std::optional<Chat> display_name;
#endif
    };
}
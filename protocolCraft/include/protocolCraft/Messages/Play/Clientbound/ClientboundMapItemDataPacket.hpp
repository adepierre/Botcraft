#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/MapDecoration.hpp"

namespace ProtocolCraft
{
    class ClientboundMapItemDataPacket : public BaseMessage<ClientboundMapItemDataPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x24;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x26;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x26;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x27;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x26;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x25;
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x27;
#else
    #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Map Item Data";
        }

        virtual ~ClientboundMapItemDataPacket() override
        {

        }

        void SetMapId(const int map_id_)
        {
            map_id = map_id_;
        }

        void SetScale(const char scale_)
        {
            scale = scale_;
        }

#if PROTOCOL_VERSION < 755
        void SetTrackingPosition(const bool tracking_position_)
        {
            tracking_position = tracking_position_;
        }
#endif

#if PROTOCOL_VERSION > 451
        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }
#endif

        void SetDecorations(const std::vector<MapDecoration>& decorations_)
        {
            decorations = decorations_;
        }

        void SetStartX(const char start_x_)
        {
            start_x = start_x_;
        }

        void SetStartZ(const char start_z_)
        {
            start_z = start_z_;
        }

        void SetWidth(const char width_)
        {
            width = width_;
        }

        void SetHeight(const char height_)
        {
            height = height_;
        }

        void SetMapColors(const std::vector<unsigned char>& map_colors_)
        {
            map_colors = map_colors_;
        }


        const int GetMapId() const
        {
            return map_id;
        }

        const char GetScale() const
        {
            return scale;
        }

#if PROTOCOL_VERSION < 755
        const bool GetTrackingPosition() const
        {
            return tracking_position;
        }
#endif

#if PROTOCOL_VERSION > 451
        const bool GetLocked() const
        {
            return locked;
        }
#endif

        const std::vector<MapDecoration>& GetDecorations() const
        {
            return decorations;
        }

        const char GetStartX() const
        {
            return start_x;
        }

        const char GetStartZ() const
        {
            return start_z;
        }

        const char GetWidth() const
        {
            return width;
        }

        const char GetHeight() const
        {
            return height;
        }

        const std::vector<unsigned char>& GetMapColors() const
        {
            return map_colors;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            map_id = ReadVarInt(iter, length);
            scale = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 755
            tracking_position = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 451
            locked = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 754
            const bool has_decorations = ReadData<bool>(iter, length);
            if (has_decorations)
            {
#endif
                int decorations_count = ReadVarInt(iter, length);
                decorations = std::vector<MapDecoration>(decorations_count);
                for (int i = 0; i < decorations_count; ++i)
                {
                    decorations[i].Read(iter, length);
                }
#if PROTOCOL_VERSION > 754
            }
#endif

            width = ReadData<char>(iter, length);
            if (width > 0)
            {
                height = ReadData<char>(iter, length);
                start_x = ReadData<char>(iter, length);
                start_z = ReadData<char>(iter, length);
                int map_colors_size = ReadVarInt(iter, length);
                map_colors = ReadByteArray(iter, length, map_colors_size);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(map_id, container);
            WriteData<char>(scale, container);
#if PROTOCOL_VERSION < 755
            WriteData<bool>(tracking_position, container);
#endif
#if PROTOCOL_VERSION > 451
            WriteData<bool>(locked, container);
#endif
#if PROTOCOL_VERSION > 754
            WriteData<bool>(decorations.size() > 0, container);
            if (decorations.size() > 0)
            {
#endif
                WriteVarInt(decorations.size(), container);
                for (int i = 0; i < decorations.size(); ++i)
                {
                    decorations[i].Write(container);
                }
#if PROTOCOL_VERSION > 754
            }
#endif

            WriteData<char>(width, container);
            if (width > 0)
            {
                WriteData<char>(height, container);
                WriteData<char>(start_x, container);
                WriteData<char>(start_z, container);
                WriteVarInt(map_colors.size(), container);
                WriteByteArray(map_colors, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["map_id"] = picojson::value((double)map_id);
            object["scale"] = picojson::value((double)scale);
#if PROTOCOL_VERSION < 755
            object["tracking_position"] = picojson::value((double)tracking_position);
#endif
#if PROTOCOL_VERSION > 451
            object["locked"] = picojson::value((double)locked);
#endif
            object["decorations"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["decorations"].get<picojson::array>();
            for (int i = 0; i < decorations.size(); ++i)
            {
                array.push_back(decorations[i].Serialize());
            }
            object["width"] = picojson::value((double)width);
            if (width > 0)
            {
                object["height"] = picojson::value((double)height);
                object["start_x"] = picojson::value((double)start_x);
                object["start_z"] = picojson::value((double)start_z);
                object["map_colors"] = picojson::value("Vector of " + std::to_string(map_colors.size()) + " unsigned chars");
            }

            return value;
        }

    private:
        int map_id;
        char scale;
#if PROTOCOL_VERSION < 755
        bool tracking_position;
#endif
#if PROTOCOL_VERSION > 451
        bool locked;
#endif
        std::vector<MapDecoration> decorations;
        char start_x;
        char start_z;
        char width;
        char height;
        std::vector<unsigned char> map_colors;
    };
} //ProtocolCraft
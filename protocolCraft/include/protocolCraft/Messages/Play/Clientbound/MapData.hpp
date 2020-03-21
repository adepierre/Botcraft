#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/MapIcon.hpp"

namespace ProtocolCraft
{
    class MapData : public BaseMessage<MapData>
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
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Map Data";
        }

        void SetMapId(const int map_id_)
        {
            map_id = map_id_;
        }

        void SetScale(const char scale_)
        {
            scale = scale_;
        }

        void SetTrackingPosition(const bool tracking_position_)
        {
            tracking_position = tracking_position_;
        }

#if PROTOCOL_VERSION > 451
        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }
#endif

        void SetIconCount(const int icon_count_)
        {
            icon_count = icon_count_;
        }

        void SetIcons(const std::vector<MapIcon>& icons_)
        {
            icons = icons_;
        }

#if PROTOCOL_VERSION < 401
        void SetColumns(const char columns_)
        {
            columns = columns_;
        }
#else
        void SetColumns(const unsigned char columns_)
        {
            columns = columns_;
        }
#endif

        void SetRows(const char rows_)
        {
            rows = rows_;
        }

        void SetX(const char x_)
        {
            x = x_;
        }

        void SetZ(const char z_)
        {
            z = z_;
        }

        void SetLength(const int length_)
        {
            length = length_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }


        const int GetMapId() const
        {
            return map_id;
        }

        const char GetScale() const
        {
            return scale;
        }

        const bool GetTrackingPosition() const
        {
            return tracking_position;
        }

#if PROTOCOL_VERSION > 451
        const bool GetLocked() const
        {
            return locked;
        }
#endif

        const int GetIconCount() const
        {
            return icon_count;
        }

        const std::vector<MapIcon>& GetIcons() const
        {
            return icons;
        }

#if PROTOCOL_VERSION < 401
        const char GetColumns() const
        {
            return columns;
        }
#else
        const unsigned char GetColumns() const
        {
            return columns;
        }
#endif

        const char GetRows() const
        {
            return rows;
        }

        const char GetX() const
        {
            return x;
        }

        const char GetZ() const
        {
            return z;
        }

        const int GetLength() const
        {
            return length;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            map_id = ReadVarInt(iter, length);
            scale = ReadData<char>(iter, length);
            tracking_position = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 451
            locked = ReadData<bool>(iter, length);
#endif
            icon_count = ReadVarInt(iter, length);
            icons = std::vector<MapIcon>(icon_count);
            for (int i = 0; i < icon_count; ++i)
            {
                icons[i].Read(iter, length);
            }
#if PROTOCOL_VERSION < 401
            columns = ReadData<char>(iter, length);
#else
            columns = ReadData<unsigned char>(iter, length);
#endif
            if (columns > 0)
            {
                rows = ReadData<char>(iter, length);
                x = ReadData<char>(iter, length);
                z = ReadData<char>(iter, length);
                length = ReadVarInt(iter, length);
                data = ReadByteArray(iter, length, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(map_id, container);
            WriteData<char>(scale, container);
            WriteData<bool>(tracking_position, container);
#if PROTOCOL_VERSION > 451
            WriteData<bool>(locked, container);
#endif
            WriteVarInt(icon_count, container);
            for (int i = 0; i < icon_count; ++i)
            {
                icons[i].Write(container);
            }
#if PROTOCOL_VERSION < 401
            WriteData<char>(columns, container);
#else
            WriteData<unsigned char>(columns, container);
#endif
            if (columns > 0)
            {
                WriteData<char>(rows, container);
                WriteData<char>(x, container);
                WriteData<char>(z, container);
                WriteVarInt(length, container);
                WriteByteArray(data, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["map_id"] = picojson::value((double)map_id);
            object["scale"] = picojson::value((double)scale);
            object["tracking_position"] = picojson::value((double)tracking_position);
#if PROTOCOL_VERSION > 451
            object["locked"] = picojson::value((double)locked);
#endif
            object["icon_count"] = picojson::value((double)icon_count);

            object["icons"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["icons"].get<picojson::array>();
            for (int i = 0; i < icon_count; ++i)
            {
                array.push_back(icons[i].Serialize());
            }
            object["columns"] = picojson::value((double)columns);
            if (columns > 0)
            {
                object["rows"] = picojson::value((double)rows);
                object["x"] = picojson::value((double)x);
                object["z"] = picojson::value((double)z);
                object["length"] = picojson::value((double)length);
                object["data"] = picojson::value("Vector of " + std::to_string(data.size()) + " unsigned chars");
            }

            return value;
        }

    private:
        int map_id;
        char scale;
        bool tracking_position;
#if PROTOCOL_VERSION > 451
        bool locked;
#endif
        int icon_count;
        std::vector<MapIcon> icons;
#if PROTOCOL_VERSION < 401
        char columns;
#else
        unsigned char columns;
#endif
        char rows;
        char x;
        char z;
        int length;
        std::vector<unsigned char> data;

    };
} //ProtocolCraft
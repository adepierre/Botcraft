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
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x27;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
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

        void SetStartX(const unsigned char start_x_)
        {
            start_x = start_x_;
        }

        void SetStartZ(const unsigned char start_z_)
        {
            start_z = start_z_;
        }

        void SetWidth(const unsigned char width_)
        {
            width = width_;
        }

        void SetHeight(const unsigned char height_)
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

        const unsigned char GetStartX() const
        {
            return start_x;
        }

        const unsigned char GetStartZ() const
        {
            return start_z;
        }

        const unsigned char GetWidth() const
        {
            return width;
        }

        const unsigned char GetHeight() const
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
            map_id = ReadData<VarInt>(iter, length);
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
                int decorations_count = ReadData<VarInt>(iter, length);
                decorations = std::vector<MapDecoration>(decorations_count);
                for (int i = 0; i < decorations_count; ++i)
                {
                    decorations[i].Read(iter, length);
                }
#if PROTOCOL_VERSION > 754
            }
#endif

            width = ReadData<unsigned char>(iter, length);
            if (width > 0)
            {
                height = ReadData<unsigned char>(iter, length);
                start_x = ReadData<unsigned char>(iter, length);
                start_z = ReadData<unsigned char>(iter, length);
                int map_colors_size = ReadData<VarInt>(iter, length);
                map_colors = ReadByteArray(iter, length, map_colors_size);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(map_id, container);
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
                WriteData<VarInt>(decorations.size(), container);
                for (int i = 0; i < decorations.size(); ++i)
                {
                    decorations[i].Write(container);
                }
#if PROTOCOL_VERSION > 754
            }
#endif

            WriteData<unsigned char>(width, container);
            if (width > 0)
            {
                WriteData<unsigned char>(height, container);
                WriteData<unsigned char>(start_x, container);
                WriteData<unsigned char>(start_z, container);
                WriteData<VarInt>(map_colors.size(), container);
                WriteByteArray(map_colors, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["map_id"] = map_id;
            output["scale"] = scale;
#if PROTOCOL_VERSION < 755
            output["tracking_position"] = tracking_position;
#endif
#if PROTOCOL_VERSION > 451
            output["locked"] = locked;
#endif
            output["decorations"] = nlohmann::json::array();
            for (int i = 0; i < decorations.size(); ++i)
            {
                output["decorations"].push_back(decorations[i].Serialize());
            }
            output["width"] = width;
            if (width > 0)
            {
                output["height"] = height;
                output["start_x"] = start_x;
                output["start_z"] = start_z;
                output["map_colors"] = "Vector of " + std::to_string(map_colors.size()) + " unsigned chars";
            }

            return output;
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
        unsigned char start_x;
        unsigned char start_z;
        unsigned char width;
        unsigned char height;
        std::vector<unsigned char> map_colors;
    };
} //ProtocolCraft
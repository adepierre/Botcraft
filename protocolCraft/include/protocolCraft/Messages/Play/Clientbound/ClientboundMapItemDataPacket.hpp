#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/MapDecoration.hpp"

namespace ProtocolCraft
{
    class ClientboundMapItemDataPacket : public BaseMessage<ClientboundMapItemDataPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x29;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Map Item Data";

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

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetTrackingPosition(const bool tracking_position_)
        {
            tracking_position = tracking_position_;
        }
#endif

#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        void SetDecorations(const std::optional<std::vector<MapDecoration>>& decorations_)
        {
            decorations = decorations_;
        }
#else
        void SetDecorations(const std::vector<MapDecoration>& decorations_)
        {
            decorations = decorations_;
        }
#endif

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


        int GetMapId() const
        {
            return map_id;
        }

        char GetScale() const
        {
            return scale;
        }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        bool GetTrackingPosition() const
        {
            return tracking_position;
        }
#endif

#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
        bool GetLocked() const
        {
            return locked;
        }
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        const std::optional<std::vector<MapDecoration>>& GetDecorations() const
        {
            return decorations;
        }
#else
        const std::vector<MapDecoration>& GetDecorations() const
        {
            return decorations;
        }
#endif

        unsigned char GetStartX() const
        {
            return start_x;
        }

        unsigned char GetStartZ() const
        {
            return start_z;
        }

        unsigned char GetWidth() const
        {
            return width;
        }

        unsigned char GetHeight() const
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
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            tracking_position = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
            locked = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
            decorations = ReadOptional<std::vector<MapDecoration>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<MapDecoration>(i, l);
                }
            );
#else
            decorations = ReadVector<MapDecoration>(iter, length);
#endif

            width = ReadData<unsigned char>(iter, length);
            if (width > 0)
            {
                height = ReadData<unsigned char>(iter, length);
                start_x = ReadData<unsigned char>(iter, length);
                start_z = ReadData<unsigned char>(iter, length);
                map_colors = ReadVector<unsigned char>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer & container) const override
        {
            WriteData<VarInt>(map_id, container);
            WriteData<char>(scale, container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<bool>(tracking_position, container);
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
            WriteData<bool>(locked, container);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
            WriteOptional<std::vector<MapDecoration>>(decorations, container,
                [](const std::vector<MapDecoration>& v, WriteContainer& c)
                {
                    WriteVector<MapDecoration>(v, c);
                }
            );
#else
            WriteVector<MapDecoration>(decorations, container);
#endif

            WriteData<unsigned char>(width, container);
            if (width > 0)
            {
                WriteData<unsigned char>(height, container);
                WriteData<unsigned char>(start_x, container);
                WriteData<unsigned char>(start_z, container);
                WriteVector<unsigned char>(map_colors, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["map_id"] = map_id;
            output["scale"] = scale;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output["tracking_position"] = tracking_position;
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
            output["locked"] = locked;
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
            if (decorations.has_value())
            {
                output["decorations"] = decorations.value();
            }
#else
            output["decorations"] = decorations;
#endif
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
        int map_id = 0;
        char scale = 0;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        bool tracking_position = false;
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
        bool locked = false;
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        std::optional<std::vector<MapDecoration>> decorations;
#else
        std::vector<MapDecoration> decorations;
#endif
        unsigned char start_x = 0;
        unsigned char start_z = 0;
        unsigned char width = 0;
        unsigned char height = 0;
        std::vector<unsigned char> map_colors;
    };
} //ProtocolCraft

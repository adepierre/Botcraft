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
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x2C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Map Item Data";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS_TYPES(VarInt, char,  bool,             std::vector<MapDecoration>, unsigned char, unsigned char, unsigned char, unsigned char, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(MapId,  Scale, TrackingPosition, Decorations,                Width,         Height,        StartX,        StartZ,        MapColors);
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS_TYPES(VarInt, char,  bool,             bool,   std::vector<MapDecoration>, unsigned char, unsigned char, unsigned char, unsigned char, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(MapId,  Scale, TrackingPosition, Locked, Decorations,                Width,         Height,        StartX,        StartZ,        MapColors);
#else
        DECLARE_FIELDS_TYPES(VarInt, char,  bool,   std::optional<std::vector<MapDecoration>>, unsigned char, unsigned char, unsigned char, unsigned char, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(MapId,  Scale, Locked, Decorations,                               Width,         Height,        StartX,        StartZ,        MapColors);
#endif
        GETTER_SETTER(MapId);
        GETTER_SETTER(Scale);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(TrackingPosition);
#endif
        GETTER_SETTER(Decorations);
        GETTER_SETTER(Width);
        GETTER_SETTER(Height);
        GETTER_SETTER(StartX);
        GETTER_SETTER(StartZ);
        GETTER_SETTER(MapColors);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        GETTER_SETTER(Locked);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetMapId(ReadData<VarInt>(iter, length));
            SetScale(ReadData<char>(iter, length));
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            SetTrackingPosition(ReadData<bool>(iter, length));
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
            SetLocked(ReadData<bool>(iter, length));
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            SetDecorations(ReadData<std::optional<std::vector<MapDecoration>>>(iter, length));
#else
            SetDecorations(ReadData<std::vector<MapDecoration>>(iter, length));
#endif

            SetWidth(ReadData<unsigned char>(iter, length));
            if (GetWidth() > 0)
            {
                SetHeight(ReadData<unsigned char>(iter, length));
                SetStartX(ReadData<unsigned char>(iter, length));
                SetStartZ(ReadData<unsigned char>(iter, length));
                SetMapColors(ReadData<std::vector<unsigned char>>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer & container) const override
        {
            WriteData<VarInt>(GetMapId(), container);
            WriteData<char>(GetScale(), container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<bool>(GetTrackingPosition(), container);
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
            WriteData<bool>(GetLocked(), container);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            WriteData<std::optional<std::vector<MapDecoration>>>(GetDecorations(), container);
#else
            WriteData<std::vector<MapDecoration>>(GetDecorations(), container);
#endif

            WriteData<unsigned char>(GetWidth(), container);
            if (GetWidth() > 0)
            {
                WriteData<unsigned char>(GetHeight(), container);
                WriteData<unsigned char>(GetStartX(), container);
                WriteData<unsigned char>(GetStartZ(), container);
                WriteData<std::vector<unsigned char>>(GetMapColors(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::MapId)])] = GetMapId();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Scale)])] = GetScale();
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::TrackingPosition)])] = GetTrackingPosition();
#endif
#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Locked)])] = GetLocked();
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            if (GetDecorations().has_value())
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Decorations)])] = GetDecorations().value();
            }
#else
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Decorations)])] = GetDecorations();
#endif
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Width)])] = GetWidth();
            if (GetWidth() > 0)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Height)])] = GetHeight();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::StartX)])] = GetStartX();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::StartZ)])] = GetStartZ();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::MapColors)])] = "Vector of " + std::to_string(GetMapColors().size()) + " unsigned chars";
            }

            return output;
        }
    };
} //ProtocolCraft

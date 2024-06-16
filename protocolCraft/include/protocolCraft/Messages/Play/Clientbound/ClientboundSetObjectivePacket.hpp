#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 389 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/NumberFormat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetObjectivePacket : public BaseMessage<ClientboundSetObjectivePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x5E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Objective";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::string,   char,   std::string, std::string),
            (ObjectiveName, Method, DisplayName, RenderType)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (std::string,   char,   Chat,        VarInt),
            (ObjectiveName, Method, DisplayName, RenderType)
        );
#else
        DECLARE_FIELDS(
            (std::string,   char,   Chat,        VarInt,     NumberFormat),
            (ObjectiveName, Method, DisplayName, RenderType, NumberFormat)
        );
#endif

        GETTER_SETTER(ObjectiveName);
        GETTER_SETTER(Method);
        GETTER_SETTER(DisplayName);
        GETTER_SETTER(RenderType);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(NumberFormat);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetObjectiveName(ReadData<std::string>(iter, length));
            SetMethod(ReadData<char>(iter, length));
            if (GetMethod() == 0 || GetMethod() == 2)
            {
#if PROTOCOL_VERSION < 390 /* < 1.13 */
                SetDisplayName(ReadData<std::string>(iter, length));
#else
                SetDisplayName(ReadData<Chat>(iter, length));
#endif
#if PROTOCOL_VERSION < 349 /* < 1.13 */
                SetRenderType(ReadData<std::string>(iter, length));
#else
                SetRenderType(ReadData<VarInt>(iter, length));
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
                SetNumberFormat(ReadData<NumberFormat>(iter, length));
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(GetObjectiveName(), container);
            WriteData<char>(GetMethod(), container);
            if (GetMethod() == 0 || GetMethod() == 2)
            {
#if PROTOCOL_VERSION < 390 /* < 1.13 */
                WriteData<std::string>(GetDisplayName(), container);
#else
                WriteData<Chat>(GetDisplayName(), container);
#endif
#if PROTOCOL_VERSION < 349 /* < 1.13 */
                WriteData<std::string>(GetRenderType(), container);
#else
                WriteData<VarInt>(GetRenderType(), container);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
                WriteData<NumberFormat>(GetNumberFormat(), container);
#endif
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::ObjectiveName)])] = GetObjectiveName();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Method)])] = GetMethod();
            if (GetMethod() == 0 || GetMethod() == 2)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::DisplayName)])] = GetDisplayName();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::RenderType)])] = GetRenderType();
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NumberFormat)])] = GetNumberFormat();
#endif
            }

            return output;
        }
    };
} //ProtocolCraft

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

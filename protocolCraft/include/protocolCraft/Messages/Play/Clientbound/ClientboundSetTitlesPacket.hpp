#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    enum class SetTitlesType
    {
        Title = 0,
        Subtitle = 1,
        ActionBar = 2,
        Times = 3,
        Clear = 4,
        Reset = 5
    };

    class ClientboundSetTitlesPacket : public BaseMessage<ClientboundSetTitlesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Titles";

        DECLARE_FIELDS(
            (DiffType<SetTitlesType, VarInt>, Chat, int,        int,      int),
            (Type,                            Text, FadeInTime, StayTime, FadeOutTime)
        );

        GETTER_SETTER(Type);
        GETTER_SETTER(Text);
        GETTER_SETTER(FadeInTime);
        GETTER_SETTER(StayTime);
        GETTER_SETTER(FadeOutTime);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetType(ReadData<SetTitlesType, VarInt>(iter, length));
            switch (GetType())
            {
            case SetTitlesType::Title:
            case SetTitlesType::Subtitle:
            case SetTitlesType::ActionBar:
                SetText(ReadData<Chat>(iter, length));
                break;
            case SetTitlesType::Times:
                SetFadeInTime(ReadData<int>(iter, length));
                SetStayTime(ReadData<int>(iter, length));
                SetFadeOutTime(ReadData<int>(iter, length));
                break;
            case SetTitlesType::Clear:
                break;
            case SetTitlesType::Reset:
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<SetTitlesType, VarInt>(GetType(), container);
            switch (GetType())
            {
            case SetTitlesType::Title:
            case SetTitlesType::Subtitle:
            case SetTitlesType::ActionBar:
                WriteData<Chat>(GetText(), container);
                break;
            case SetTitlesType::Times:
                WriteData<int>(GetFadeInTime(), container);
                WriteData<int>(GetStayTime(), container);
                WriteData<int>(GetFadeOutTime(), container);
                break;
            case SetTitlesType::Clear:
                break;
            case SetTitlesType::Reset:
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Type)])] = GetType();
            switch (GetType())
            {
            case SetTitlesType::Title:
            case SetTitlesType::Subtitle:
            case SetTitlesType::ActionBar:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Text)])] = GetText();
                break;
            case SetTitlesType::Times:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::FadeInTime)])] = GetFadeInTime();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::StayTime)])] = GetStayTime();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::FadeOutTime)])] = GetFadeOutTime();
                break;
            case SetTitlesType::Clear:
            case SetTitlesType::Reset:
                break;
            default:
                break;
            }

            return output;
        }
    };
} //ProtocolCraft
#endif

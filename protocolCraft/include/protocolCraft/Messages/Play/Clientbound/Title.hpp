#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    enum class TitleAction
    {
        SetTitle = 0,
        SetSubtitle = 1,
        SetActionBar = 2,
        SetTimesAndDisplay = 3,
        Hide = 4,
        Reset = 5
    };

    class Title : public BaseMessage<Title>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x48;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x4B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x50;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Title";
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetTitleText(const Chat& title_text_)
        {
            title_text = title_text_;
        }

        void SetSubtitleText(const Chat& subtitle_text_)
        {
            subtitle_text = subtitle_text_;
        }

        void SetActionBarText(const Chat& action_bar_text_)
        {
            action_bar_text = action_bar_text_;
        }

        void SetFadeIn(const int fade_int_)
        {
            fade_in = fade_int_;
        }

        void SetStay(const int stay_)
        {
            stay = stay_;
        }

        void SetFadeOut(const int fade_out_)
        {
            fade_out = fade_out_;
        }


        const int GetAction() const
        {
            return action;
        }

        const Chat& GetTitleText() const
        {
            return title_text;
        }

        const Chat& GetSubtitleText() const
        {
            return subtitle_text;
        }

        const Chat& GetActionBarText() const
        {
            return action_bar_text;
        }

        const int GetFadeIn() const
        {
            return fade_in;
        }

        const int GetStay() const
        {
            return stay;
        }

        const int GetFadeOut() const
        {
            return fade_out;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = ReadVarInt(iter, length);
            switch ((TitleAction)action)
            {
            case TitleAction::SetTitle:
                title_text.Read(iter, length);
                break;
            case TitleAction::SetSubtitle:
                subtitle_text.Read(iter, length);
                break;
            case TitleAction::SetActionBar:
                action_bar_text.Read(iter, length);
                break;
            case TitleAction::SetTimesAndDisplay:
                fade_in = ReadData<int>(iter, length);
                stay = ReadData<int>(iter, length);
                fade_out = ReadData<int>(iter, length);
                break;
            case TitleAction::Hide:

                break;

            case TitleAction::Reset:

                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(action, container);
            switch ((TitleAction)action)
            {
            case TitleAction::SetTitle:
                title_text.Write(container);
                break;
            case TitleAction::SetSubtitle:
                subtitle_text.Write(container);
                break;
            case TitleAction::SetActionBar:
                action_bar_text.Write(container);
                break;
            case TitleAction::SetTimesAndDisplay:
                WriteData<int>(fade_in, container);
                WriteData<int>(stay, container);
                WriteData<int>(fade_out, container);
                break;
            case TitleAction::Hide:

                break;

            case TitleAction::Reset:

                break;
            default:
                break;
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["action"] = picojson::value((double)action);
            switch ((TitleAction)action)
            {
            case TitleAction::SetTitle:
                object["title_text"] = title_text.Serialize();
                break;
            case TitleAction::SetSubtitle:
                object["subtitle_text"] = subtitle_text.Serialize();
                break;
            case TitleAction::SetActionBar:
                object["action_bar_text"] = action_bar_text.Serialize();
                break;
            case TitleAction::SetTimesAndDisplay:
                object["fade_int"] = picojson::value((double)fade_in);
                object["stay"] = picojson::value((double)stay);
                object["fade_out"] = picojson::value((double)fade_out);
                break;
            case TitleAction::Hide:

                break;

            case TitleAction::Reset:

                break;
            default:
                break;
            }

            return value;
        }

    private:
        int action;
        Chat title_text;
        Chat subtitle_text;
        Chat action_bar_text;
        int fade_in;
        int stay;
        int fade_out;

    };
} //ProtocolCraft
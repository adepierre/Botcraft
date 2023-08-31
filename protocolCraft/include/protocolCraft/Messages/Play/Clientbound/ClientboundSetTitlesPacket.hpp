#pragma once

#if PROTOCOL_VERSION < 755 /* < 1.17 */
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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x4F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Titles";

        virtual ~ClientboundSetTitlesPacket() override
        {

        }

        void SetType(const SetTitlesType type_)
        {
            type = type_;
        }

        void SetText(const Chat& text_)
        {
            text = text_;
        }

        void SetFadeInTime(const int fade_in_time_)
        {
            fade_in_time = fade_in_time_;
        }

        void SetStayTime(const int stay_time_)
        {
            stay_time = stay_time_;
        }

        void SetFadeOutTime(const int fade_out_time_)
        {
            fade_out_time = fade_out_time_;
        }


        SetTitlesType GetType() const
        {
            return type;
        }

        const Chat& GetText() const
        {
            return text;
        }

        int GetFadeInTime() const
        {
            return fade_in_time;
        }

        int GetStayTime() const
        {
            return stay_time;
        }

        int GetFadeOutTime() const
        {
            return fade_out_time;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = static_cast<SetTitlesType>(static_cast<int>(ReadData<VarInt>(iter, length)));
            switch (type)
            {
            case SetTitlesType::Title:
            case SetTitlesType::Subtitle:
            case SetTitlesType::ActionBar:
                text = ReadData<Chat>(iter, length);
                break;
            case SetTitlesType::Times:
                fade_in_time = ReadData<int>(iter, length);
                stay_time = ReadData<int>(iter, length);
                fade_out_time = ReadData<int>(iter, length);
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
            WriteData<VarInt>(static_cast<int>(type), container);
            switch (type)
            {
            case SetTitlesType::Title:
            case SetTitlesType::Subtitle:
            case SetTitlesType::ActionBar:
                WriteData<Chat>(text, container);
                break;
            case SetTitlesType::Times:
                WriteData<int>(fade_in_time, container);
                WriteData<int>(stay_time, container);
                WriteData<int>(fade_out_time, container);
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

            output["type"] = type;
            switch (type)
            {
            case SetTitlesType::Title:
            case SetTitlesType::Subtitle:
            case SetTitlesType::ActionBar:
                output["text"] = text;
                break;
            case SetTitlesType::Times:
                output["fade_in_time"] = fade_in_time;
                output["stay_time"] = stay_time;
                output["fade_out_time"] = fade_out_time;
                break;
            case SetTitlesType::Clear:
            case SetTitlesType::Reset:
                break;
            default:
                break;
            }

            return output;
        }

    private:
        SetTitlesType type;
        Chat text;
        int fade_in_time = 0;
        int stay_time = 0;
        int fade_out_time = 0;

    };
} //ProtocolCraft
#endif

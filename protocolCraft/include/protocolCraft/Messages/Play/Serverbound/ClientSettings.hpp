#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientSettings : public BaseMessage<ClientSettings>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x04;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x04;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x05;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x05;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x05;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Client Settings";
        }

        void SetLocale(const std::string &s)
        {
            locale = s;
        }

        void SetViewDistance(const char c)
        {
            view_distance = c;
        }

        void SetChatMode(const int i)
        {
            chat_mode = i;
        }

        void SetChatColors(const bool b)
        {
            chat_colors = b;
        }

        void SetDisplayedSkinParts(const unsigned char c)
        {
            displayed_skin_parts = c;
        }

        void SetMainHand(const int i)
        {
            main_hand = i;
        }

        const std::string& GetLocale() const
        {
            return locale;
        }

        const char GetViewDistance() const
        {
            return view_distance;
        }

        const int GetChatMode() const
        {
            return chat_mode;
        }

        const bool GetChatColors() const
        {
            return chat_colors;
        }

        const unsigned char GetDisplayedSkinParts() const
        {
            return displayed_skin_parts;
        }

        const int GetMainHand() const
        {
            return main_hand;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            locale = ReadString(iter, length);
            view_distance = ReadData<char>(iter, length);
            chat_mode = ReadVarInt(iter, length);
            chat_colors = ReadData<bool>(iter, length);
            displayed_skin_parts = ReadData<unsigned char>(iter, length);
            main_hand = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(locale, container);
            WriteData<char>(view_distance, container);
            WriteVarInt(chat_mode, container);
            WriteData<bool>(chat_colors, container);
            WriteData<unsigned char>(displayed_skin_parts, container);
            WriteVarInt(main_hand, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["locale"] = picojson::value(locale);
            object["view_distance"] = picojson::value((double)view_distance);
            object["chat_mode"] = picojson::value((double)chat_mode);
            object["chat_colors"] = picojson::value(chat_colors);
            object["displayed_skin_parts"] = picojson::value((double)displayed_skin_parts);
            object["main_hand"] = picojson::value((double)main_hand);

            return value;
        }

    private:
        std::string locale;
        char view_distance;
        int chat_mode;
        bool chat_colors;
        unsigned char displayed_skin_parts;
        int main_hand;
    };
} //ProtocolCraft
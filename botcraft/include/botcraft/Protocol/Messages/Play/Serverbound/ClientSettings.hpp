#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
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
#elif PROTOCOL_VERSION == 573
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

        void SetChatMode(const ChatMode i)
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

        void SetMainHand(const Hand i)
        {
            main_hand = i;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(locale, container);
            WriteData<char>(view_distance, container);
            WriteVarInt((int)chat_mode, container);
            WriteData<bool>(chat_colors, container);
            WriteData<unsigned char>(displayed_skin_parts, container);
            WriteVarInt((int)main_hand, container);
        }

    private:
        std::string locale;
        char view_distance;
        ChatMode chat_mode;
        bool chat_colors;
        unsigned char displayed_skin_parts;
        Hand main_hand;
    };
} //Botcraft
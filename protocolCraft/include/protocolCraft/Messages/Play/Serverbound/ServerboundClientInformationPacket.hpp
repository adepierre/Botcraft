#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientInformationPacket : public BaseMessage<ServerboundClientInformationPacket>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x05;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x05;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x05;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Client Information";
        }

        virtual ~ServerboundClientInformationPacket() override
        {

        }

        void SetLanguage(const std::string &language_)
        {
            language = language_;
        }

        void SetViewDistance(const char view_distance_)
        {
            view_distance = view_distance_;
        }

        void SetChatVisibility(const int chat_visibility_)
        {
            chat_visibility = chat_visibility_;
        }

        void SetChatColors(const bool chat_colors_)
        {
            chat_colors = chat_colors_;
        }

        void SetModelCustomisation(const unsigned char model_customisation_)
        {
            model_customisation = model_customisation_;
        }

        void SetMainHand(const int main_hand_)
        {
            main_hand = main_hand_;
        }

#if PROTOCOL_VERSION > 754
        void SetTextFilteringEnabled(const int text_filtering_enabled_)
        {
            text_filtering_enabled = text_filtering_enabled_;
        }
#endif


        const std::string& GetLanguage() const
        {
            return language;
        }

        const char GetViewDistance() const
        {
            return view_distance;
        }

        const int GetChatVisibility() const
        {
            return chat_visibility;
        }

        const bool GetChatColors() const
        {
            return chat_colors;
        }

        const unsigned char GetModelCustomisation() const
        {
            return model_customisation;
        }

        const int GetMainHand() const
        {
            return main_hand;
        }

#if PROTOCOL_VERSION > 754
        const int GetTextFilteringEnabled() const
        {
            return text_filtering_enabled;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            language = ReadData<std::string>(iter, length);
            view_distance = ReadData<char>(iter, length);
            chat_visibility = ReadVarInt(iter, length);
            chat_colors = ReadData<bool>(iter, length);
            model_customisation = ReadData<unsigned char>(iter, length);
            main_hand = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 754
            text_filtering_enabled = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(language, container);
            WriteData<char>(view_distance, container);
            WriteVarInt(chat_visibility, container);
            WriteData<bool>(chat_colors, container);
            WriteData<unsigned char>(model_customisation, container);
            WriteVarInt(main_hand, container);
#if PROTOCOL_VERSION > 754
            WriteData<bool>(text_filtering_enabled, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["language"] = picojson::value(language);
            object["view_distance"] = picojson::value((double)view_distance);
            object["chat_visibility"] = picojson::value((double)chat_visibility);
            object["chat_colors"] = picojson::value(chat_colors);
            object["model_customisation"] = picojson::value((double)model_customisation);
            object["main_hand"] = picojson::value((double)main_hand);
#if PROTOCOL_VERSION > 754
            object["text_filtering_enabled"] = picojson::value(text_filtering_enabled);
#endif

            return value;
        }

    private:
        std::string language;
        char view_distance;
        int chat_visibility;
        bool chat_colors;
        unsigned char model_customisation;
        int main_hand;
#if PROTOCOL_VERSION > 754
        bool text_filtering_enabled;
#endif
    };
} //ProtocolCraft
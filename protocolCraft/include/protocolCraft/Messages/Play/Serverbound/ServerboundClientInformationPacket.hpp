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
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
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
        void SetTextFilteringEnabled(const bool text_filtering_enabled_)
        {
            text_filtering_enabled = text_filtering_enabled_;
        }
#endif
#if PROTOCOL_VERSION > 756
        void SetAllowListing(const bool allow_listing_)
        {
            allow_listing = allow_listing_;
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
        const bool GetTextFilteringEnabled() const
        {
            return text_filtering_enabled;
        }
#endif
#if PROTOCOL_VERSION > 756
        const bool GetAllowListing() const
        {
            return allow_listing;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            language = ReadData<std::string>(iter, length);
            view_distance = ReadData<char>(iter, length);
            chat_visibility = ReadData<VarInt>(iter, length);
            chat_colors = ReadData<bool>(iter, length);
            model_customisation = ReadData<unsigned char>(iter, length);
            main_hand = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 754
            text_filtering_enabled = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 756
            allow_listing = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(language, container);
            WriteData<char>(view_distance, container);
            WriteData<VarInt>(chat_visibility, container);
            WriteData<bool>(chat_colors, container);
            WriteData<unsigned char>(model_customisation, container);
            WriteData<VarInt>(main_hand, container);
#if PROTOCOL_VERSION > 754
            WriteData<bool>(text_filtering_enabled, container);
#endif
#if PROTOCOL_VERSION > 756
            WriteData<bool>(allow_listing, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["language"] = language;
            output["view_distance"] = view_distance;
            output["chat_visibility"] = chat_visibility;
            output["chat_colors"] = chat_colors;
            output["model_customisation"] = model_customisation;
            output["main_hand"] = main_hand;
#if PROTOCOL_VERSION > 754
            output["text_filtering_enabled"] = text_filtering_enabled;
#endif
#if PROTOCOL_VERSION > 756
            output["allow_listing"] = allow_listing;
#endif

            return output;
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
#if PROTOCOL_VERSION > 756
        bool allow_listing;
#endif
    };
} //ProtocolCraft
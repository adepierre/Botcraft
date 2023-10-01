#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientInformation : public NetworkType
    {
    public:
        virtual ~ClientInformation() override
        {

        }

        void SetLanguage(const std::string& language_)
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

        void SetTextFilteringEnabled(const bool text_filtering_enabled_)
        {
            text_filtering_enabled = text_filtering_enabled_;
        }

        void SetAllowsListing(const bool allows_listing_)
        {
            allows_listing = allows_listing_;
        }


        const std::string& GetLanguage() const
        {
            return language;
        }

        char GetViewDistance() const
        {
            return view_distance;
        }

        int GetChatVisibility() const
        {
            return chat_visibility;
        }

        bool GetChatColors() const
        {
            return chat_colors;
        }

        unsigned char GetModelCustomisation() const
        {
            return model_customisation;
        }

        int GetMainHand() const
        {
            return main_hand;
        }

        bool GetTextFilteringEnabled() const
        {
            return text_filtering_enabled;
        }

        bool GetAllowsListing() const
        {
            return allows_listing;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            language = ReadData<std::string>(iter, length);
            view_distance = ReadData<char>(iter, length);
            chat_visibility = ReadData<VarInt>(iter, length);
            chat_colors = ReadData<bool>(iter, length);
            model_customisation = ReadData<unsigned char>(iter, length);
            main_hand = ReadData<VarInt>(iter, length);
            text_filtering_enabled = ReadData<bool>(iter, length);
            allows_listing = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(language, container);
            WriteData<char>(view_distance, container);
            WriteData<VarInt>(chat_visibility, container);
            WriteData<bool>(chat_colors, container);
            WriteData<unsigned char>(model_customisation, container);
            WriteData<VarInt>(main_hand, container);
            WriteData<bool>(text_filtering_enabled, container);
            WriteData<bool>(allows_listing, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["language"] = language;
            output["view_distance"] = view_distance;
            output["chat_visibility"] = chat_visibility;
            output["chat_colors"] = chat_colors;
            output["model_customisation"] = model_customisation;
            output["main_hand"] = main_hand;
            output["text_filtering_enabled"] = text_filtering_enabled;
            output["allows_listing"] = allows_listing;

            return output;
        }

    private:
        std::string language;
        char view_distance = 0;
        int chat_visibility = 0;
        bool chat_colors = false;
        unsigned char model_customisation = 0;
        int main_hand = 0;
        bool text_filtering_enabled = false;
        bool allows_listing = false;
    };
}
#endif

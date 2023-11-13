#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ClientInformation.hpp"
#endif


namespace ProtocolCraft
{
    class ServerboundClientInformationPacket : public BaseMessage<ServerboundClientInformationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x09;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Client Information";

        virtual ~ServerboundClientInformationPacket() override
        {

        }


#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
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

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        void SetTextFilteringEnabled(const bool text_filtering_enabled_)
        {
            text_filtering_enabled = text_filtering_enabled_;
        }
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        void SetAllowListing(const bool allow_listing_)
        {
            allow_listing = allow_listing_;
        }
#endif
#else
        void SetClientInformation(const ClientInformation& client_information_)
        {
            client_information = client_information_;
        }
#endif


#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
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

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        bool GetTextFilteringEnabled() const
        {
            return text_filtering_enabled;
        }
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        bool GetAllowListing() const
        {
            return allow_listing;
        }
#endif
#else
        const ClientInformation& GetClientInformation() const
        {
            return client_information;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            language = ReadData<std::string>(iter, length);
            view_distance = ReadData<char>(iter, length);
            chat_visibility = ReadData<VarInt>(iter, length);
            chat_colors = ReadData<bool>(iter, length);
            model_customisation = ReadData<unsigned char>(iter, length);
            main_hand = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            text_filtering_enabled = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            allow_listing = ReadData<bool>(iter, length);
#endif
#else
            client_information = ReadData<ClientInformation>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<std::string>(language, container);
            WriteData<char>(view_distance, container);
            WriteData<VarInt>(chat_visibility, container);
            WriteData<bool>(chat_colors, container);
            WriteData<unsigned char>(model_customisation, container);
            WriteData<VarInt>(main_hand, container);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            WriteData<bool>(text_filtering_enabled, container);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            WriteData<bool>(allow_listing, container);
#endif
#else
            WriteData<ClientInformation>(client_information, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["language"] = language;
            output["view_distance"] = view_distance;
            output["chat_visibility"] = chat_visibility;
            output["chat_colors"] = chat_colors;
            output["model_customisation"] = model_customisation;
            output["main_hand"] = main_hand;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            output["text_filtering_enabled"] = text_filtering_enabled;
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            output["allow_listing"] = allow_listing;
#endif
#else
            output["client_information"] = client_information;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        std::string language;
        char view_distance = 0;
        int chat_visibility = 0;
        bool chat_colors = false;
        unsigned char model_customisation = 0;
        int main_hand = 0;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        bool text_filtering_enabled = false;
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        bool allow_listing = false;
#endif
#else
        ClientInformation client_information;
#endif
    };
} //ProtocolCraft

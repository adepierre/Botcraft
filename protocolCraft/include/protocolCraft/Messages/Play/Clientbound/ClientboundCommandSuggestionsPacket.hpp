#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundCommandSuggestionsPacket : public BaseMessage<ClientboundCommandSuggestionsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x10;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Command Suggestions";

        virtual ~ClientboundCommandSuggestionsPacket() override
        {

        }

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetStart(const int start_)
        {
            start = start_;
        }

        void SetLength(const int length__)
        {
            length_ = length__;
        }
#endif

        void SetSuggestions(const std::vector<std::string>& suggestions_)
        {
            suggestions = suggestions_;
        }

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        void SetTooltips(const std::vector<std::optional<Chat>>& tooltips_)
        {
            tooltips = tooltips_;
        }
#endif

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        int GetId_() const
        {
            return id_;
        }

        int GetStart() const
        {
            return start;
        }

        int GetLength() const
        {
            return length_;
        }
#endif

        const std::vector<std::string>& GetSuggestions() const
        {
            return suggestions;
        }

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        const std::vector<std::optional<Chat>>& GetTooltips() const
        {
            return tooltips;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            id_ = ReadData<VarInt>(iter, length);
            start = ReadData<VarInt>(iter, length);
            length_ = ReadData<VarInt>(iter, length);
#endif
            const int count = ReadData<VarInt>(iter, length);
            suggestions = std::vector<std::string>(count);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            tooltips = std::vector<std::optional<Chat>>(count);
#endif
            for (int i = 0; i < count; ++i)
            {
                suggestions[i] = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
                tooltips[i] = ReadOptional<Chat>(iter, length);
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            WriteData<VarInt>(id_, container);
            WriteData<VarInt>(start, container);
            WriteData<VarInt>(length_, container);
#endif
            WriteData<VarInt>(static_cast<int>(suggestions.size()), container);
            for (int i = 0; i < suggestions.size(); ++i)
            {
                WriteData<std::string>(suggestions[i], container);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
                WriteOptional<Chat>(tooltips[i], container);
#endif
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;



#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            output["id_"] = id_;
            output["start"] = start;
            output["length_"] = length_;
#endif
            output["suggestions"] = suggestions;

#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            output["tooltips"] = Json::Array();
            for (const auto& t : tooltips)
            {
                output["tooltips"].push_back(t.has_value() ? t.value().Serialize() : Json::Value());
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        int id_ = 0;
        int start = 0;
        int length_ = 0;
#endif
        std::vector<std::string> suggestions;
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        std::vector<std::optional<Chat>> tooltips;
#endif

    };
} //ProtocolCraft

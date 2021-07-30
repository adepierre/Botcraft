#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 356
#include "protocolCraft/Types/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundCommandSuggestionsPacket : public BaseMessage<ClientboundCommandSuggestionsPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x10;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x10;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x11;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x10;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x11;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Command Suggestions";
        }

        virtual ~ClientboundCommandSuggestionsPacket() override
        {

        }

#if PROTOCOL_VERSION > 356
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

#if PROTOCOL_VERSION > 356
        void SetTooltips(const std::vector<Chat>& tooltips_)
        {
            tooltips = tooltips_;
        }
#endif

#if PROTOCOL_VERSION > 356
        const int GetId_() const
        {
            return id_;
        }

        const int GetStart() const
        {
            return start;
        }

        const int GetLength() const
        {
            return length_;
        }
#endif

        const std::vector<std::string>& GetSuggestions() const
        {
            return suggestions;
        }

#if PROTOCOL_VERSION > 356
        const std::vector<Chat>& GetTooltips() const
        {
            return tooltips;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 356
            id_ = ReadVarInt(iter, length);
            start = ReadVarInt(iter, length);
            length_ = ReadVarInt(iter, length);
#endif
            int count = ReadVarInt(iter, length);
            suggestions = std::vector<std::string>(count);
#if PROTOCOL_VERSION > 356
            tooltips = std::vector<Chat>(count);
#endif
            for (int i = 0; i < count; ++i)
            {
                suggestions[i] = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 356
                bool has_tooltip = ReadData<bool>(iter, length);
                if (has_tooltip)
                {
                    tooltips[i].Read(iter, length);
                }
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

#if PROTOCOL_VERSION > 356
            WriteVarInt(id_, container);
            WriteVarInt(start, container);
            WriteVarInt(length_, container);
#endif
            WriteVarInt(suggestions.size(), container);
            for (int i = 0; i < suggestions.size(); ++i)
            {
                WriteData<std::string>(suggestions[i], container);
#if PROTOCOL_VERSION > 356
                bool has_tooltip = tooltips[i].GetText().empty();
                WriteData<bool>(has_tooltip, container);
                if (has_tooltip)
                {
                    tooltips[i].Write(container);
                }
#endif
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();



#if PROTOCOL_VERSION > 356
            object["id_"] = picojson::value((double)id_);
            object["start"] = picojson::value((double)start);
            object["length_"] = picojson::value((double)length_);
#endif
            object["suggestions"] = picojson::value(picojson::array_type, false);
            picojson::array& array_suggestions = object["suggestions"].get<picojson::array>();
            for (int i = 0; i < suggestions.size(); ++i)
            {
                array_suggestions.push_back(picojson::value(suggestions[i]));

            }


#if PROTOCOL_VERSION > 356
            object["tooltips"] = picojson::value(picojson::array_type, false);
            picojson::array& array_tooltips = object["tooltips"].get<picojson::array>();
            
            for (int i = 0; i < tooltips.size(); ++i) 
            {
                array_tooltips.push_back(tooltips[i].Serialize());
            }
#endif

            return value;
        }

    private:
#if PROTOCOL_VERSION > 356
        int id_;
        int start;
        int length_;
#endif
        std::vector<std::string> suggestions;
#if PROTOCOL_VERSION > 356
        std::vector<Chat> tooltips;
#endif

    };
} //ProtocolCraft
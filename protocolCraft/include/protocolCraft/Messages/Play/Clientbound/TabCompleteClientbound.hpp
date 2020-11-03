#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 356
#include "protocolCraft/Types/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class TabCompleteClientbound : public BaseMessage<TabCompleteClientbound>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x0F;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Tab Complete (Clientbound)";
        }

#if PROTOCOL_VERSION > 356
        void SetID(const int id_)
        {
            id = id_;
        }

        void SetStart(const int start_)
        {
            start = start_;
        }

        void SetLength(const int length_)
        {
            length = length_;
        }
#endif

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetMatches(const std::vector<std::string>& matches_)
        {
            matches = matches_;
        }

#if PROTOCOL_VERSION > 356
        void SetHasTooltip(const std::vector<bool>& has_tooltip_)
        {
            has_tooltip = has_tooltip_;
        }

        void SetTooltip(const std::vector<Chat>& tooltip_)
        {
            tooltip = tooltip_;
        }
#endif

#if PROTOCOL_VERSION > 356
        const int GetID() const
        {
            return id;
        }

        const int GetStart() const
        {
            return start;
        }

        const int GetLength() const
        {
            return length;
        }
#endif


        const int GetCount() const
        {
            return count;
        }

        const std::vector<std::string>& GetMatches() const
        {
            return matches;
        }

#if PROTOCOL_VERSION > 356
        const std::vector<bool>& GetHasTooltip() const
        {
            return has_tooltip;
        }

        const std::vector<Chat>& GetTooltip() const
        {
            return tooltip;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 356
            id = ReadVarInt(iter, length);
            start = ReadVarInt(iter, length);
            length = ReadVarInt(iter, length);
#endif
            count = ReadVarInt(iter, length);
            matches = std::vector<std::string>(count);
#if PROTOCOL_VERSION > 356
            has_tooltip = std::vector<bool>(count);
            tooltip = std::vector<Chat>(count);
#endif
            for (int i = 0; i < count; ++i)
            {
                matches[i] = ReadString(iter, length);
#if PROTOCOL_VERSION > 356
                has_tooltip[i] = ReadData<bool>(iter, length);
                if (has_tooltip[i])
                {
                    tooltip[i].Read(iter, length);
                }
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(count, container);
            for (int i = 0; i < count; ++i)
            {
                WriteString(matches[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["count"] = picojson::value((double)count);

            object["matches"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["matches"].get<picojson::array>();
            for(int i = 0; i < count; ++i)
            {
                array.push_back(picojson::value(matches[i]));
            }

            return value;
        }

    private:
#if PROTOCOL_VERSION > 356
        int id;
        int start;
        int length;
#endif
        int count;
        std::vector<std::string> matches;
#if PROTOCOL_VERSION > 356
        std::vector<bool> has_tooltip;
        std::vector<Chat> tooltip;
#endif

    };
} //ProtocolCraft
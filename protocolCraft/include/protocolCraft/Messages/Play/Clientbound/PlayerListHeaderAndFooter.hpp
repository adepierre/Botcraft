#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class PlayerListHeaderAndFooter : public BaseMessage<PlayerListHeaderAndFooter>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x4E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x53;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x54;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x53;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x53;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player List Header And Footer";
        }

        void SetHeader(const Chat& header_)
        {
            header = header_;
        }

        void SetFooter(const Chat& footer_)
        {
            footer = footer_;
        }


        const Chat& GetHeader() const
        {
            return header;
        }

        const Chat& GetFooter() const
        {
            return footer;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            header.Read(iter, length);
            footer.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            header.Write(container);
            footer.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["header"] = header.Serialize();
            object["footer"] = footer.Serialize();

            return value;
        }

    private:
        Chat header;
        Chat footer;

    };
} //ProtocolCraft
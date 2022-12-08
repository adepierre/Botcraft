#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundTabListPacket : public BaseMessage<ClientboundTabListPacket>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x53;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x53;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x5E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x5F;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x60;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x63;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x61;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Tab List";
        }

        virtual ~ClientboundTabListPacket() override
        {

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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["header"] = header.Serialize();
            output["footer"] = footer.Serialize();

            return output;
        }

    private:
        Chat header;
        Chat footer;

    };
} //ProtocolCraft
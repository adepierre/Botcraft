#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSetActionBarTextPacket : public BaseMessage<ClientboundSetActionBarTextPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x42;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Action Bar Text";

        virtual ~ClientboundSetActionBarTextPacket() override
        {

        }


        void SetText(const Chat& text_)
        {
            text = text_;
        }


        const Chat& GetText() const
        {
            return text;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            text = ReadData<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Chat>(text, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["text"] = text.Serialize();

            return output;
        }

    private:
        Chat text;

    };
} //ProtocolCraft
#endif

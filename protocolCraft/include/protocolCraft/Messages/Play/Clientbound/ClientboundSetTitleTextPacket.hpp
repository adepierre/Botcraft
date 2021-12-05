#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTitleTextPacket : public BaseMessage<ClientboundSetTitleTextPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x59;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x5A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Title Text";
        }

        virtual ~ClientboundSetTitleTextPacket() override
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
            text.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            text.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["text"] = text.Serialize();

            return output;
        }

    private:
        Chat text;

    };
} //ProtocolCraft
#endif
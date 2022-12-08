#if PROTOCOL_VERSION > 758
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSystemChatPacket : public BaseMessage<ClientboundSystemChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x5F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x62;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x60;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "System Chat";
        }

        virtual ~ClientboundSystemChatPacket() override
        {

        }

        void SetContent(const Chat& signed_content_)
        {
            content = signed_content_;
        }

#if PROTOCOL_VERSION < 760
        void SetTypeId(const int type_id_)
        {
            type_id = type_id_;
        }
#else
        void SetOverlay(const bool overlay_)
        {
            overlay = overlay_;
        }
#endif


        const Chat& GetContent() const
        {
            return content;
        }

#if PROTOCOL_VERSION < 760
        const int GetTypeId() const
        {
            return type_id;
        }
#else
        const bool GetOverlay() const
        {
            return overlay;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            content.Read(iter, length);
#if PROTOCOL_VERSION < 760
            type_id = ReadData<VarInt>(iter, length);
#else
            overlay = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            content.Write(container);
#if PROTOCOL_VERSION < 760
            WriteData<VarInt>(type_id, container);
#else
            WriteData<bool>(overlay, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["content"] = content.Serialize();
#if PROTOCOL_VERSION < 760
            output["type_id"] = type_id;
#else
            output["overlay"] = overlay;
#endif


            return output;
        }

    private:
        Chat content;
#if PROTOCOL_VERSION < 760
        int type_id;
#else
        bool overlay;
#endif
    };
} //ProtocolCraft
#endif

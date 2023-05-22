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
#if PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x64;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "System Chat";

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
        int GetTypeId() const
        {
            return type_id;
        }
#else
        bool GetOverlay() const
        {
            return overlay;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            content = ReadData<Chat>(iter, length);
#if PROTOCOL_VERSION < 760
            type_id = ReadData<VarInt>(iter, length);
#else
            overlay = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<Chat>(content, container);
#if PROTOCOL_VERSION < 760
            WriteData<VarInt>(type_id, container);
#else
            WriteData<bool>(overlay, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["content"] = content;
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

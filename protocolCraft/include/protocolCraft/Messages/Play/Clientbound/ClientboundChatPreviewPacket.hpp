#if PROTOCOL_VERSION > 758 && PROTOCOL_VERSION < 761
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPreviewPacket : public BaseMessage<ClientboundChatPreviewPacket>
    {
    public:
#if PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x0C;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Chat Preview";

        virtual ~ClientboundChatPreviewPacket() override
        {

        }

        void SetQueryId(const int query_id_)
        {
            query_id = query_id_;
        }

        void SetPreview(const std::optional<Chat>& preview_)
        {
            preview = preview_;
        }
        
        
        char GetQueryId() const
        {
            return query_id;
        }

        const std::optional<Chat>& Getpreview() const
        {
            return preview;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            query_id = ReadData<int>(iter, length);
            preview = ReadOptional<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(query_id, container);
            WriteOptional<Chat>(preview, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["query_id"] = query_id;
            if (preview.has_value())
            {
                output["preview"] = preview.value().Serialize();
            }


            return output;
        }

    private:
        int query_id;
        std::optional<Chat> preview;
    };
} //ProtocolCraft
#endif

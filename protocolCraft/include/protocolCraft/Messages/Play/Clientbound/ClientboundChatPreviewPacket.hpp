#if PROTOCOL_VERSION > 758 && PROTOCOL_VERSION < 761
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPreviewPacket : public BaseMessage<ClientboundChatPreviewPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x0C;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x0C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Preview";
        }

        virtual ~ClientboundChatPreviewPacket() override
        {

        }

        void SetQueryId(const int query_id_)
        {
            query_id = query_id_;
        }

        void SetPreview(const Chat& preview_)
        {
            preview = preview_;
        }
        
        
        const char GetQueryId() const
        {
            return query_id;
        }

        const Chat& Getpreview() const
        {
            return preview;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            query_id = ReadData<int>(iter, length);
            const bool has_preview = ReadData<bool>(iter, length);
            if (has_preview)
            {
                preview = ReadData<Chat>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(query_id, container);
            WriteData<bool>(preview.GetRawText().empty(), container);
            if (!preview.GetRawText().empty())
            {
                WriteData<Chat>(preview, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["query_id"] = query_id;
            if (!preview.GetRawText().empty())
            {
                output["preview"] = preview.Serialize();
            }


            return output;
        }

    private:
        int query_id;
        Chat preview;
    };
} //ProtocolCraft
#endif

#if PROTOCOL_VERSION > 758
#pragma once

#include <string>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPreviewPacket : public BaseMessage<ServerboundChatPreviewPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x05;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x06;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Preview";
        }

        virtual ~ServerboundChatPreviewPacket() override
        {

        }

        void SetQueryId(const int query_id_)
        {
            query_id = query_id_;
        }

        void SetQuery(const std::string& query_)
        {
            query = query_;
        }


        const int GetQueryId() const
        {
            return query_id;
        }

        const std::string& GetQuery() const
        {
            return query;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            query_id = ReadData<int>(iter, length);
            query = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(query_id, container);
            WriteData<std::string>(query, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["query_id"] = query_id;
            output["query"] = query;


            return output;
        }

    private:
        int query_id;
        std::string query;
    };
} //ProtocolCraft
#endif

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include <string>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPreviewPacket : public BaseMessage<ServerboundChatPreviewPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x06;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Preview";

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


        int GetQueryId() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["query_id"] = query_id;
            output["query"] = query;


            return output;
        }

    private:
        int query_id = 0;
        std::string query;
    };
} //ProtocolCraft
#endif

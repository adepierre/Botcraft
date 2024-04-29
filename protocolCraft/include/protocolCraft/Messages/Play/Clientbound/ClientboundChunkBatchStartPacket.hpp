#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChunkBatchStartPacket : public BaseMessage<ClientboundChunkBatchStartPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chunk Batch Start";

        virtual ~ClientboundChunkBatchStartPacket() override
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            return output;
        }

    private:

    };
} //ProtocolCraft
#endif

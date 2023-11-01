#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChunkBatchFinishedPacket : public BaseMessage<ClientboundChunkBatchFinishedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x0C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chunk Batch Finished";

        virtual ~ClientboundChunkBatchFinishedPacket() override
        {

        }

        void SetBatchSize(const int batch_size_)
        {
            batch_size = batch_size_;
        }


        int GetBatchSize() const
        {
            return batch_size;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            batch_size = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(batch_size, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["batch_size"] = batch_size;

            return output;
        }

    private:
        int batch_size = 0;
    };
} //ProtocolCraft
#endif

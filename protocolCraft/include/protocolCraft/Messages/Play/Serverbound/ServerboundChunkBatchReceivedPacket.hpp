#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChunkBatchReceivedPacket : public BaseMessage<ServerboundChunkBatchReceivedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chunk Batch Received";

        virtual ~ServerboundChunkBatchReceivedPacket() override
        {

        }

        void SetDesiredChunksPerTick(const float desired_chunks_per_tick_)
        {
            desired_chunks_per_tick = desired_chunks_per_tick_;
        }


        float GetDesiredChunksPerTick() const
        {
            return desired_chunks_per_tick;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            desired_chunks_per_tick = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(desired_chunks_per_tick, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["desired_chunks_per_tick"] = desired_chunks_per_tick;


            return output;
        }

    private:
        float desired_chunks_per_tick = 0.0f;
    };
} //ProtocolCraft
#endif

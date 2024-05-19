#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundDebugSamplePacket : public BaseMessage<ClientboundDebugSamplePacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x1B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Debug Sample";

        virtual ~ClientboundDebugSamplePacket() override
        {

        }


        void SetSample(const std::vector<long long int>& sample_)
        {
            sample = sample_;
        }

        void SetDebugSampleType(const int debug_sample_type_)
        {
            debug_sample_type = debug_sample_type_;
        }


        const std::vector<long long int>& GetSample() const
        {
            return sample;
        }

        int GetDebugSampleType() const
        {
            return debug_sample_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            sample = ReadData<std::vector<long long int>>(iter, length);
            debug_sample_type = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::vector<long long int>>(sample, container);
            WriteData<VarInt>(debug_sample_type, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["sample"] = sample;
            output["debug_sample_type"] = debug_sample_type;

            return output;
        }

    private:
        std::vector<long long int> sample;
        int debug_sample_type = 0;
    };
} //ProtocolCraft
#endif

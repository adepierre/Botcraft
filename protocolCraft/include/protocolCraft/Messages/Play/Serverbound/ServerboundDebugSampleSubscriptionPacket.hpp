#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundDebugSampleSubscriptionPacket : public BaseMessage<ServerboundDebugSampleSubscriptionPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x13;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Debug Sample Subscription";

        virtual ~ServerboundDebugSampleSubscriptionPacket() override
        {

        }


        void SetSampleType(const int sample_type_)
        {
            sample_type = sample_type_;
        }


        int GetSampleType() const
        {
            return sample_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            sample_type = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(sample_type, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["sample_type"] = sample_type;

            return output;
        }

    private:
        int sample_type = 0;
    };
} // ProtocolCraft
#endif

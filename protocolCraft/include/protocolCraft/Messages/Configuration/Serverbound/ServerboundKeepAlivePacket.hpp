#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundKeepAliveConfigurationPacket : public BaseMessage<ServerboundKeepAliveConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x03;

        static constexpr std::string_view packet_name = "Keep Alive (Configuration)";

        virtual ~ServerboundKeepAliveConfigurationPacket() override
        {

        }

        void SetId_(const long long int l)
        {
            id_ = l;
        }

        long long int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<long long int>(id_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;

            return output;
        }

    private:
        long long int id_ = 0;
    };
} //ProtocolCraft
#endif

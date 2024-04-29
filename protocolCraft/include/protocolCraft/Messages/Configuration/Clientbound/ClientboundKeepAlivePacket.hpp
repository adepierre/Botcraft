#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundKeepAliveConfigurationPacket : public BaseMessage<ClientboundKeepAliveConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x04;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Keep Alive (Configuration)";

        virtual ~ClientboundKeepAliveConfigurationPacket() override
        {

        }

        void SetId_(const long long int id__)
        {
            id_ = id__;
        }

        long long int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
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

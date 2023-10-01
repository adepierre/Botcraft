#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPongResponsePacket : public BaseMessage<ClientboundPongResponsePacket>
    {
    public:
#if   PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x34;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Pong Response";

        virtual ~ClientboundPongResponsePacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }


        int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(id_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id"] = id_;

            return output;
    }

    private:
        int id_ = 0;

    };
} //ProtocolCraft
#endif

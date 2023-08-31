#pragma once

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */ && PROTOCOL_VERSION < 756 /* < 1.17.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntityPacket : public BaseMessage<ClientboundRemoveEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */
        static constexpr int packet_id = 0x3A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Remove Entity";

        virtual ~ClientboundRemoveEntityPacket() override
        {

        }


        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }


        int GetEntityId() const
        {
            return entity_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;

            return output;
        }

    private:
        int entity_id = 0;

    };
} //ProtocolCraft
#endif

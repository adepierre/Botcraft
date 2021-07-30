#pragma once

#if PROTOCOL_VERSION > 754 && PROTOCOL_VERSION < 756
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntityPacket : public BaseMessage<ClientboundRemoveEntityPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x3A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Remove Entity";
        }

        virtual ~ClientboundRemoveEntityPacket() override
        {

        }


        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);

            return value;
        }

    private:
        int entity_id;

    };
} //ProtocolCraft
#endif
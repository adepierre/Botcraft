#pragma once

#if PROTOCOL_VERSION < 755
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacket : public BaseMessage<ClientboundMoveEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x2A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Move Entity";

        virtual ~ClientboundMoveEntityPacket() override
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
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
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

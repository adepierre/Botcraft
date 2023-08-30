#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundEntityEventPacket : public BaseMessage<ClientboundEntityEventPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x1C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Entity Event";

        virtual ~ClientboundEntityEventPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetEventId(const char event_id_)
        {
            event_id = event_id_;
        }


        int GetEntityId() const
        {
            return entity_id;
        }

        char GetEventId() const
        {
            return event_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<int>(iter, length);
            event_id = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(entity_id, container);
            WriteData<char>(event_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["event_id"] = event_id;

            return output;
        }

    private:
        int entity_id = 0;
        char event_id = 0;

    };
} //ProtocolCraft

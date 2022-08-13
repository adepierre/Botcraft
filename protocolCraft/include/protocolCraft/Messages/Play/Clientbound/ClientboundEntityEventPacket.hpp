#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundEntityEventPacket : public BaseMessage<ClientboundEntityEventPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x1B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x1B;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x18;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x1A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Event";
        }

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


        const int GetEntityId() const
        {
            return entity_id;
        }

        const char GetEventId() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["event_id"] = event_id;

            return output;
        }

    private:
        int entity_id;
        char event_id;

    };
} //ProtocolCraft
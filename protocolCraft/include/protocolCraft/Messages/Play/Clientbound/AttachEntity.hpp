#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class AttachEntity : public BaseMessage<AttachEntity>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x3D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x40;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x44;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x45;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x45;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Attach Entity";
        }

        void SetAttachedEntityId(const int attached_entity_id_)
        {
            attached_entity_id = attached_entity_id_;
        }

        void SetHoldingEntityId(const int holding_entity_id_)
        {
            holding_entity_id = holding_entity_id_;
        }


        const int GetAttachedEntityId() const
        {
            return attached_entity_id;
        }

        const int GetHoldingEntityId() const
        {
            return holding_entity_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            attached_entity_id = ReadData<int>(iter, length);
            holding_entity_id = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(attached_entity_id, container);
            WriteData<int>(holding_entity_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["attached_entity_id"] = picojson::value((double)attached_entity_id);
            object["holding_entity_id"] = picojson::value((double)holding_entity_id);

            return value;
        }

    private:
        int attached_entity_id;
        int holding_entity_id;

    };
} //ProtocolCraft
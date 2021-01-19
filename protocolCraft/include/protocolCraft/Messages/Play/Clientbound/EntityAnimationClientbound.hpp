#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityAnimationClientbound : public BaseMessage<EntityAnimationClientbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x06;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x06;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x06;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x06;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x05;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x05;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Animation (Clientbound)";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetAnimation(const unsigned char animation_)
        {
            animation = animation_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const unsigned char GetAnimation() const
        {
            return animation;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            animation = ReadData<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<unsigned char>(animation, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["animation"] = picojson::value((double)animation);

            return value;
        }

    private:
        int entity_id;
        unsigned char animation;

    };
} //ProtocolCraft
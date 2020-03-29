#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityAction : public BaseMessage<EntityAction>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x15;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x19;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1B;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Action";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetActionId(const int action_id_)
        {
            action_id = action_id_;
        }

        void SetJumpBoost(const int jump_boost_)
        {
            jump_boost = jump_boost_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetActionId() const
        {
            return action_id;
        }

        const int GetJumpBoost() const
        {
            return jump_boost;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            action_id = ReadVarInt(iter, length);
            jump_boost = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteVarInt(action_id, container);
            WriteVarInt(jump_boost, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["action_id"] = picojson::value((double)action_id);
            object["jump_boost"] = picojson::value((double)jump_boost);

            return value;
        }

    private:
        int entity_id;
        int action_id;
        int jump_boost;

    };
} //ProtocolCraft
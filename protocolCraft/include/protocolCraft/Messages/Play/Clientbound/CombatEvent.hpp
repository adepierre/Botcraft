#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    enum class CombatEventEvent
    {
        NoEvent = 0,
        EndCombat = 1,
        EntityDead = 2
    };

    class CombatEvent : public BaseMessage<CombatEvent>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x2D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x32;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x33;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x32;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Combat Event";
        }

        void SetEvent(const int event_)
        {
            event = event_;
        }

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

        void SetMessage(const Chat& message_)
        {
            message = message_;
        }


        const int GetEvent() const
        {
            return event;
        }

        const int GetDuration() const
        {
            return duration;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetPlayerId() const
        {
            return player_id;
        }

        const Chat& GetMessage() const
        {
            return message;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            event = ReadVarInt(iter, length);
            switch ((CombatEventEvent)event)
            {
            case CombatEventEvent::NoEvent:
                break;
            case CombatEventEvent::EndCombat:
                duration = ReadVarInt(iter, length);
                entity_id = ReadData<int>(iter, length);
                break;
            case CombatEventEvent::EntityDead:
                player_id = ReadVarInt(iter, length);
                entity_id = ReadData<int>(iter, length);
                message.Read(iter, length);
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(event, container);
            switch ((CombatEventEvent)event)
            {
            case CombatEventEvent::NoEvent:
                break;
            case CombatEventEvent::EndCombat:
                WriteVarInt(duration, container);
                WriteData<int>(entity_id, container);
                break;
            case CombatEventEvent::EntityDead:
                WriteVarInt(player_id, container);
                WriteData<int>(entity_id, container);
                message.Write(container);
            default:
                break;
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["event"] = picojson::value((double)event);
            switch ((CombatEventEvent)event)
            {
            case CombatEventEvent::NoEvent:
                break;
            case CombatEventEvent::EndCombat:
                object["duration"] = picojson::value((double)duration);
                object["entity_id"] = picojson::value((double)entity_id);
                break;
            case CombatEventEvent::EntityDead:
                object["player_id"] = picojson::value((double)player_id);
                object["entity_id"] = picojson::value((double)entity_id);
                object["message"] = message.Serialize();
            default:
                break;
            }

            return value;
        }

    private:
        int event;
        int duration;
        int entity_id;
        int player_id;
        Chat message;

    };
} //ProtocolCraft
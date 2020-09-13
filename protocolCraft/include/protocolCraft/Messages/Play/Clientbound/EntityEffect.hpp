#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityEffect : public BaseMessage<EntityEffect>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x52;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x58;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x5A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x59;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x59;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Effect";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetEffectId(const char effect_id_)
        {
            effect_id = effect_id_;
        }

        void SetAmplifier(const char amplifier_)
        {
            amplifier = amplifier_;
        }

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const char GetEffectId() const
        {
            return effect_id;
        }

        const char GetAmplifier() const
        {
            return amplifier;
        }

        const int GetDuration() const
        {
            return duration;
        }

        const char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            effect_id = ReadData<char>(iter, length);
            amplifier = ReadData<char>(iter, length);
            duration = ReadVarInt(iter, length);
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<char>(effect_id, container);
            WriteData<char>(amplifier, container);
            WriteVarInt(duration, container);
            WriteData<char>(flags, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["effect_id"] = picojson::value((double)effect_id);
            object["amplifier"] = picojson::value((double)amplifier);
            object["duration"] = picojson::value((double)duration);
            object["flags"] = picojson::value((double)flags);

            return value;
        }

    private:
        int entity_id;
        char effect_id;
        char amplifier;
        int duration;
        char flags;

    };
} //ProtocolCraft
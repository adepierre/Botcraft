#pragma once

#if PROTOCOL_VERSION > 440
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntitySoundEffect : public BaseMessage<EntitySoundEffect>
    {
    public:
        virtual const int GetId() const override
        {

#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x50;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x51;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x50;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x50;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Sound Effect";
        }

        void SetSoundId(const int sound_id_)
        {
            sound_id = sound_id_;
        }

        void SetSoundCategory(const int sound_category_)
        {
            sound_category = sound_category_;
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetVolume(const float volume_)
        {
            volume = volume_;
        }

        void SetPitch(const float pitch_)
        {
            pitch = pitch_;
        }


        const int GetSoundId() const
        {
            return sound_id;
        }

        const int GetSoundCategory() const
        {
            return sound_category;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const float GetVolume() const
        {
            return volume;
        }

        const float GetPitch() const
        {
            return pitch;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            sound_id = ReadVarInt(iter, length);
            sound_category = ReadVarInt(iter, length);
            entity_id = ReadVarInt(iter, length);
            volume = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(sound_id, container);
            WriteVarInt(sound_category, container);
            WriteVarInt(entity_id, container);
            WriteData<float>(volume, container);
            WriteData<float>(pitch, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["sound_id"] = picojson::value((double)sound_id);
            object["sound_category"] = picojson::value((double)sound_category);
            object["entity_id"] = picojson::value((double)entity_id);
            object["volume"] = picojson::value((double)volume);
            object["pitch"] = picojson::value((double)pitch);

            return value;
        }

    private:
        int sound_id;
        int sound_category;
        int entity_id;
        float volume;
        float pitch;

    };
} //ProtocolCraft
#endif

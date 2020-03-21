#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class NamedSoundEffect : public BaseMessage<NamedSoundEffect>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x19;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x19;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Named Sound Effect";
        }

        void SetSoundName(const std::string& sound_name_)
        {
            sound_name = sound_name_;
        }

        void SetSoundCategory(const int sound_category_)
        {
            sound_category = sound_category_;
        }

        void SetEffectPositionX(const int effect_position_x_)
        {
            effect_position_x = effect_position_x_;
        }

        void SetEffectPositionY(const int effect_position_y_)
        {
            effect_position_y = effect_position_y_;
        }

        void SetEffectPositionZ(const int effect_position_z_)
        {
            effect_position_z = effect_position_z_;
        }

        void SetVolume(const float volume_)
        {
            volume = volume_;
        }

        void SetPitch(const float pitch_)
        {
            pitch = pitch_;
        }


        const std::string& GetSoundName() const
        {
            return sound_name;
        }

        const int GetSoundCategory() const
        {
            return sound_category;
        }

        const int GetEffectPositionX() const
        {
            return effect_position_x;
        }

        const int GetEffectPositionY() const
        {
            return effect_position_y;
        }

        const int GetEffectPositionZ() const
        {
            return effect_position_z;
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
            sound_name = ReadString(iter, length);
            sound_category = ReadVarInt(iter, length);
            effect_position_x = ReadData<int>(iter, length);
            effect_position_y = ReadData<int>(iter, length);
            effect_position_z = ReadData<int>(iter, length);
            volume = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(sound_name, container);
            WriteVarInt(sound_category, container);
            WriteData<int>(effect_position_x, container);
            WriteData<int>(effect_position_y, container);
            WriteData<int>(effect_position_z, container);
            WriteData<float>(volume, container);
            WriteData<float>(pitch, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["sound_name"] = picojson::value(sound_name);
            object["sound_category"] = picojson::value((double)sound_category);
            object["effect_position_x"] = picojson::value((double)effect_position_x);
            object["effect_position_y"] = picojson::value((double)effect_position_y);
            object["effect_position_z"] = picojson::value((double)effect_position_z);
            object["volume"] = picojson::value((double)volume);
            object["pitch"] = picojson::value((double)pitch);

            return value;
        }

    private:
        std::string sound_name;
        int sound_category;
        int effect_position_x;
        int effect_position_y;
        int effect_position_z;
        float volume;
        float pitch;

    };
} //ProtocolCraft
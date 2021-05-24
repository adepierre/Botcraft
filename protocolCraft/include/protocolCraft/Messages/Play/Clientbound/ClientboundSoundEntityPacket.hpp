#pragma once

#if PROTOCOL_VERSION > 440
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSoundEntityPacket : public BaseMessage<ClientboundSoundEntityPacket>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x50;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Sound Entity";
        }

        virtual ~ClientboundSoundEntityPacket() override
        {

        }

        void SetSound(const int sound_)
        {
            sound = sound_;
        }

        void SetSource(const int source_)
        {
            source = source_;
        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetVolume(const float volume_)
        {
            volume = volume_;
        }

        void SetPitch(const float pitch_)
        {
            pitch = pitch_;
        }


        const int GetSound() const
        {
            return sound;
        }

        const int GetSource() const
        {
            return source;
        }

        const int GetId_() const
        {
            return id_;
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
            sound = ReadVarInt(iter, length);
            source = ReadVarInt(iter, length);
            id_ = ReadVarInt(iter, length);
            volume = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(sound, container);
            WriteVarInt(source, container);
            WriteVarInt(id_, container);
            WriteData<float>(volume, container);
            WriteData<float>(pitch, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["sound"] = picojson::value((double)sound);
            object["source"] = picojson::value((double)source);
            object["id_"] = picojson::value((double)id_);
            object["volume"] = picojson::value((double)volume);
            object["pitch"] = picojson::value((double)pitch);

            return value;
        }

    private:
        int sound;
        int source;
        int id_;
        float volume;
        float pitch;

    };
} //ProtocolCraft
#endif

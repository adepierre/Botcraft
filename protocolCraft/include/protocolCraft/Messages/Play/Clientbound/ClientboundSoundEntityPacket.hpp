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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x50;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x50;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x5B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x5C;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x5C;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x5F;
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

#if PROTOCOL_VERSION > 758
        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }
#endif


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

#if PROTOCOL_VERSION > 758
        const long long int GetSeed() const
        {
            return seed;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            sound = ReadData<VarInt>(iter, length);
            source = ReadData<VarInt>(iter, length);
            id_ = ReadData<VarInt>(iter, length);
            volume = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
#if PROTOCOL_VERSION > 758
            seed = ReadData<long long int>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(sound, container);
            WriteData<VarInt>(source, container);
            WriteData<VarInt>(id_, container);
            WriteData<float>(volume, container);
            WriteData<float>(pitch, container);
#if PROTOCOL_VERSION > 758
            WriteData<long long int>(seed, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["sound"] = sound;
            output["source"] = source;
            output["id_"] = id_;
            output["volume"] = volume;
            output["pitch"] = pitch;
#if PROTOCOL_VERSION > 758
            output["seed"] = seed;
#endif

            return output;
        }

    private:
        int sound;
        int source;
        int id_;
        float volume;
        float pitch;
#if PROTOCOL_VERSION > 758
        long long int seed;
#endif

    };
} //ProtocolCraft
#endif

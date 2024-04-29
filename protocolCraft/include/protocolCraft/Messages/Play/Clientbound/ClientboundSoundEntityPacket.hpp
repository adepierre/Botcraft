#pragma once

#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSoundEntityPacket : public BaseMessage<ClientboundSoundEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x50;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x67;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Sound Entity";

        virtual ~ClientboundSoundEntityPacket() override
        {

        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetSound(const int sound_)
        {
            sound = sound_;
        }
#else
        void SetSoundId(const int sound_id_)
        {
            sound_id = sound_id_;
        }

        void SetSound(const SoundEvent& sound_)
        {
            sound = sound_;
        }
#endif

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

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }
#endif


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        int GetSound() const
        {
            return sound;
        }
#else
        int GetSoundId() const
        {
            return sound_id;
        }

        const SoundEvent& GetSound() const
        {
            return sound;
        }
#endif

        int GetSource() const
        {
            return source;
        }

        int GetId_() const
        {
            return id_;
        }

        float GetVolume() const
        {
            return volume;
        }

        float GetPitch() const
        {
            return pitch;
        }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        long long int GetSeed() const
        {
            return seed;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            sound = ReadData<VarInt>(iter, length);
#else
            sound_id = ReadData<VarInt>(iter, length);
            if (sound_id == 0)
            {
                sound = ReadData<SoundEvent>(iter, length);
            }
            else
            {
                sound_id -= 1;
            }
#endif
            source = ReadData<VarInt>(iter, length);
            id_ = ReadData<VarInt>(iter, length);
            volume = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            seed = ReadData<long long int>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<VarInt>(sound, container);
#else
            if (sound.GetLocation().GetFull().empty())
            {
                WriteData<VarInt>(sound_id + 1, container);
            }
            else
            {
                WriteData<VarInt>(0, container);
                WriteData<SoundEvent>(sound, container);
            }
#endif
            WriteData<VarInt>(source, container);
            WriteData<VarInt>(id_, container);
            WriteData<float>(volume, container);
            WriteData<float>(pitch, container);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            WriteData<long long int>(seed, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["sound"] = sound;
#else
            if (sound.GetLocation().GetFull().empty())
            {
                output["sound"] = sound;
            }
            else
            {
                output["sound_id"] = sound_id;
            }
#endif
            output["source"] = source;
            output["id_"] = id_;
            output["volume"] = volume;
            output["pitch"] = pitch;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            output["seed"] = seed;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        int sound = 0;
#else
        int sound_id = 0;
        SoundEvent sound;
#endif
        int source = 0;
        int id_ = 0;
        float volume = 0.0f;
        float pitch = 0.0f;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        long long int seed = 0;
#endif

    };
} //ProtocolCraft
#endif

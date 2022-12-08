#if PROTOCOL_VERSION > 760
#pragma once


#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft 
{
    class SoundEvent : public NetworkType
    {
    public:
        virtual ~SoundEvent() override
        {

        }


        void SetSoundId(const int sound_id_)
        {
            sound_id = sound_id_;
        }

        void SetLocation(const Identifier& location_)
        {
            location = location_;
        }

        void SetRange(const float range_)
        {
            range = range_;
        }


        const int GetSoundId() const
        {
            return sound_id;
        }

        const Identifier& GetLocation() const
        {
            return location;
        }

        const float GetRange() const
        {
            return range;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            sound_id = ReadData<VarInt>(iter, length);
            if (sound_id == 0)
            {
                location.Read(iter, length);
                const bool has_range = ReadData<bool>(iter, length);
                if (has_range)
                {
                    range = ReadData<float>(iter, length);
                }
                else
                {
                    range = 0.0f;
                }
            }
            else
            {
                sound_id -= 1;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            if (location.GetFull().empty())
            {
                WriteData<VarInt>(sound_id + 1, container);
            }
            else
            {
                WriteData<VarInt>(0, container);
                location.Write(container);
                WriteData<bool>(range != 0.0f, container);
                if (range != 0.0f)
                {
                    WriteData<float>(range, container);
                }
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            if (location.GetFull().empty())
            {
                output["location"] = location.Serialize();
                if (range != 0.0f)
                {
                    output["range"] = range;
                }
            }
            else
            {
                output["sound_id"] = sound_id;
            }

            return output;
        }

    private:
        int sound_id;
        Identifier location;
        float range;
    };
} // ProtocolCraft
#endif

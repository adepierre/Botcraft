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

        void SetRange(const std::optional<float>& range_)
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

        const std::optional<float>& GetRange() const
        {
            return range;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            sound_id = ReadData<VarInt>(iter, length);
            if (sound_id == 0)
            {
                location = ReadData<Identifier>(iter, length);
                range = ReadOptional<float>(iter, length);
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
                WriteData<Identifier>(location, container);
                WriteOptional<float>(range, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            if (location.GetFull().empty())
            {
                output["location"] = location.Serialize();
                if (range.has_value())
                {
                    output["range"] = range.value();
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
        std::optional<float> range;
    };
} // ProtocolCraft
#endif

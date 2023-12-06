#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
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


        void SetLocation(const Identifier& location_)
        {
            location = location_;
        }

        void SetRange(const std::optional<float>& range_)
        {
            range = range_;
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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location = ReadData<Identifier>(iter, length);
            range = ReadOptional<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(location, container);
            WriteOptional<float>(range, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["location"] = location;
            if (range.has_value())
            {
                output["range"] = range.value();
            }

            return output;
        }

    private:
        Identifier location;
        std::optional<float> range;
    };
} // ProtocolCraft
#endif

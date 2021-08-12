#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyFloat : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyFloat()
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

        void SetMin(const float min_)
        {
            min = min_;
        }

        void SetMax(const float max_)
        {
            max = max_;
        }


        const char GetFlags() const
        {
            return flags;
        }

        const float GetMin() const
        {
            return min;
        }

        const float GetMax() const
        {
            return max;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
            if (flags & 0x01)
            {
                min = ReadData<float>(iter, length);
            }
            else
            {
                min = -std::numeric_limits<float>::max();
            }
            if (flags & 0x02)
            {
                max = ReadData<float>(iter, length);
            }
            else
            {
                max = std::numeric_limits<float>::max();
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            if (flags & 0x01)
            {
                WriteData<float>(min, container);
            }
            if (flags & 0x02)
            {
                WriteData<float>(max, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["flags"] = flags;
            output["min"] = min;
            output["max"] = max;

            return output;
        }

    private:
        char flags;
        float min;
        float max;
    };
}
#endif

#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyDouble : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyDouble()
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }
        
        void SetMin(const double min_)
        {
            min = min_;
        }
        
        void SetMax(const double max_)
        {
            max = max_;
        }
        
        
        const char GetFlags() const
        {
            return flags;
        }
        
        const char GetMin() const
        {
            return min;
        }
        
        const char GetMax() const
        {
            return max;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
            if (flags & 0x01)
            {
                min = ReadData<double>(iter, length);
            }
            else
            {
                min = -std::numeric_limits<double>::max();
            }
            if (flags & 0x02)
            {
                max = ReadData<double>(iter, length);
            }
            else
            {
                max = std::numeric_limits<double>::max();
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            if (flags & 0x01)
            {
                WriteData<double>(min, container);
            }
            if (flags & 0x02)
            {
                WriteData<double>(max, container);
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
        double min;
        double max;
    };
}
#endif

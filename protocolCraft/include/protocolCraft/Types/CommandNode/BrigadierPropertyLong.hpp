#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyLong : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyLong()
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }
        
        void SetMin(const long min_)
        {
            min = min_;
        }
        
        void SetMax(const long max_)
        {
            max = max_;
        }
        
        
        char GetFlags() const
        {
            return flags;
        }
        
        long long int GetMin() const
        {
            return min;
        }
        
        long long int GetMax() const
        {
            return max;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
            if (flags & 0x01)
            {
                min = ReadData<long long int>(iter, length);
            }
            else
            {
                min = std::numeric_limits<long long int>::min();
            }
            if (flags & 0x02)
            {
                max = ReadData<long long int>(iter, length);
            }
            else
            {
                max = std::numeric_limits<long long int>::max();
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            if (flags & 0x01)
            {
                WriteData<long long int>(min, container);
            }
            if (flags & 0x02)
            {
                WriteData<long long int>(max, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["flags"] = flags;
            output["min"] = min;
            output["max"] = max;

            return output;
        }

    private:
        char flags;
        long long int min;
        long long int max;
    };
}
#endif

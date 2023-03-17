#pragma once

#if PROTOCOL_VERSION > 761
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

#include <limits>

namespace ProtocolCraft
{
    class BrigadierPropertyTime : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyTime()
        {

        }

        void SetMin(const int min_)
        {
            min = min_;
        }
        
        
        int GetMin() const
        {
            return min;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            min = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(min, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["min"] = min;

            return output;
        }

    private:
        int min;
    };
}
#endif

#pragma once

#if PROTOCOL_VERSION > 344 && PROTOCOL_VERSION < 759
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyRange : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyRange()
        {

        }

        void SetDecimals(const double decimals_)
        {
            decimals = decimals_;
        }
        
        
        bool GetDecimals() const
        {
            return decimals;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            decimals = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(decimals, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["decimals"] = decimals;

            return output;
        }

    private:
        bool decimals = false;
    };
}
#endif

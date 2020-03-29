#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyRange : public BrigadierProperty
    {
    public:        
        void SetDecimals(const double decimals_)
        {
            decimals = decimals_;
        }
        
        
        const bool GetDecimals() const
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

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["decimals"] = picojson::value(decimals);

            return value;
        }

    private:
        bool decimals;
    };
}
#endif

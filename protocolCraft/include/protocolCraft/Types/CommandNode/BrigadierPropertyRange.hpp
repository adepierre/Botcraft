#pragma once

#if PROTOCOL_VERSION > 344
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["decimals"] = decimals;

            return output;
        }

    private:
        bool decimals;
    };
}
#endif

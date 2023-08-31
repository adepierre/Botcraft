#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyNone : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyNone()
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            return output;
        }

    private:
    };
}
#endif

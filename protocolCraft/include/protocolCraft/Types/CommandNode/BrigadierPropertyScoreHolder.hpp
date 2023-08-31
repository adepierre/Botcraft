#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyScoreHolder : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyScoreHolder()
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }
        
        
        char GetFlags() const
        {
            return flags;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["flags"] = flags;

            return output;
        }

    private:
        char flags = 0;
    };
}
#endif

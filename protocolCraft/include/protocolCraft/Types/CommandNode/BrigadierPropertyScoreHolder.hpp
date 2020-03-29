#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyScoreHolder : public BrigadierProperty
    {
    public:
        void SetFlags(const char flags_)
        {
            flags = flags_;
        }
        
        
        const char GetFlags() const
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

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["flags"] = picojson::value((double)flags);

            return value;
        }

    private:
        char flags;
    };
}
#endif

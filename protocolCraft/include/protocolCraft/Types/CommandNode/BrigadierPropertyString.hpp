#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyString : public BrigadierProperty
    {
    public:        
        void SetReadType(const int read_type_)
        {
            read_type = read_type_;
        }


        const int GetReadType() const
        {
            return read_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            read_type = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(read_type, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["read_type"] = picojson::value((double)read_type);

            return value;
        }

    private:
        int read_type;
    };
}
#endif

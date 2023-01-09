#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyString : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyString()
        {

        }

        void SetReadType(const int read_type_)
        {
            read_type = read_type_;
        }


        int GetReadType() const
        {
            return read_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            read_type = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(read_type, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["read_type"] = read_type;

            return output;
        }

    private:
        int read_type;
    };
}
#endif

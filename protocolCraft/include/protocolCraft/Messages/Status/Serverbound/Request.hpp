#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class Request : public BaseMessage<Request>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Request";
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            return value;
        }

    private:

    };
} // Botcraft
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class Pong : public BaseMessage<Pong>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x01;
        }

        virtual const std::string GetName() const override
        {
            return "Pong";
        }

        void SetPayload(const long long int payload_)
        {
            payload = payload_;
        }

        const long long int GetPayload() const
        {
            return payload;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            payload = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<long long int>(payload, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["payload"] = picojson::value((double)payload);

            return value;
        }

    private:
        long long int payload;
    };
} //ProtocolCraft
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestPacket : public BaseMessage<ServerboundPingRequestPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x01;
        }

        virtual const std::string GetName() const override
        {
            return "Ping Request";
        }

        virtual ~ServerboundPingRequestPacket() override
        {

        }

        void SetTime(const long long int time_)
        {
            time = time_;
        }

        const long long int GetTime() const
        {
            return time;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            time = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(time, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["time"] = picojson::value((double)time);

            return value;
        }

    private:
        long long int time;
    };
} // Botcraft
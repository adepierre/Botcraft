#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPongResponseStatusPacket : public BaseMessage<ClientboundPongResponseStatusPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Pong Response (Status)";

        virtual ~ClientboundPongResponseStatusPacket() override
        {

        }

        void SetTime(const long long int time_)
        {
            time = time_;
        }

        long long int GetTime() const
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
            WriteData<long long int>(time, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["time"] = time;

            return output;
        }

    private:
        long long int time = 0;
    };
} //ProtocolCraft

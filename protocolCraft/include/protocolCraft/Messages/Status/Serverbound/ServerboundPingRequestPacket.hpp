#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestPacket : public BaseMessage<ServerboundPingRequestPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Ping Request";

        virtual ~ServerboundPingRequestPacket() override
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["time"] = time;

            return output;
        }

    private:
        long long int time;
    };
} // ProtocolCraft

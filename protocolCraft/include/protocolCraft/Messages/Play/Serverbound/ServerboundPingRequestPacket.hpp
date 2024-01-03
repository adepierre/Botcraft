#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestPacket : public BaseMessage<ServerboundPingRequestPacket>
    {
    public:
#if PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x1E;
#else
#error "Protocol version not implemented"
#endif

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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            time = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
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
        long long int time;

    };
} //ProtocolCraft
#endif

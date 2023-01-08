#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientIntentionPacket : public BaseMessage<ServerboundClientIntentionPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Client Intention";

        virtual ~ServerboundClientIntentionPacket() override
        {

        }

        void SetProtocolVersion(const int p)
        {
            protocol_version = p;
        }

        void SetHostName(const std::string &s)
        {
            host_name = s;
        }

        void SetPort(const unsigned short p)
        {
            port = p;
        }

        void SetIntention(const int n)
        {
            intention = n;
        }

        const int GetProtocolVersion() const
        {
            return protocol_version;
        }

        const std::string& GetHostName() const
        {
            return host_name;
        }

        const unsigned short GetPort() const
        {
            return port;
        }

        const int GetIntention() const
        {
            return intention;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            protocol_version = ReadData<VarInt>(iter, length);
            host_name = ReadData<std::string>(iter, length);
            port = ReadData<unsigned short>(iter, length);
            intention = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(protocol_version, container);
            WriteData<std::string>(host_name, container);
            WriteData<unsigned short>(port, container);
            WriteData<VarInt>(intention, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["protocol_version"] = protocol_version;
            output["host_name"] = host_name;
            output["port"] = port;
            output["intention"] = intention;

            return output;
        }

    private:
        int protocol_version;
        std::string host_name;
        unsigned short port;
        int intention;
    };
} //ProtocolCraft

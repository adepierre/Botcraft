#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientIntentionPacket : public BaseMessage<ServerboundClientIntentionPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Client Intention";
        }

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
            protocol_version = ReadVarInt(iter, length);
            host_name = ReadString(iter, length);
            port = ReadData<unsigned short>(iter, length);
            intention = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(protocol_version, container);
            WriteString(host_name, container);
            WriteData<unsigned short>(port, container);
            WriteVarInt(intention, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["protocol_version"] = picojson::value((double)protocol_version);
            object["host_name"] = picojson::value(host_name);
            object["port"] = picojson::value((double)port);
            object["intention"] = picojson::value((double)intention);

            return value;
        }

    private:
        int protocol_version;
        std::string host_name;
        unsigned short port;
        int intention;
    };
} //ProtocolCraft
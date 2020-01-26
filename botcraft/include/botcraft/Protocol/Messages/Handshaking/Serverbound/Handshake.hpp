#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

namespace Botcraft
{
    class Handshake : public BaseMessage<Handshake>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Handshake";
        }

        void SetProtocolVersion(const int p)
        {
            protocol_version = p;
        }

        void SetServerAddress(const std::string &s)
        {
            server_address = s;
        }

        void SetServerPort(const unsigned short p)
        {
            server_port = p;
        }

        void SetNextState(const int n)
        {
            next_state = n;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(protocol_version, container);
            WriteString(server_address, container);
            WriteData<unsigned short>(server_port, container);
            WriteVarInt(next_state, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["protocol_version"] = picojson::value((double)protocol_version);
            object["server_address"] = picojson::value(server_address);
            object["server_port"] = picojson::value((double)server_port);
            object["next_state"] = picojson::value((double)next_state);

            return value;
        }

    private:
        int protocol_version;
        std::string server_address;
        unsigned short server_port;
        int next_state;
    };
} //Botcraft
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class PluginMessageClientbound : public BaseMessage<PluginMessageClientbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x18;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x19;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x18;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x19;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Plugin Message (clientbound)";
        }

        void SetChannel(const std::string& channel_)
        {
            channel = channel_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }


        const std::string& GetChannel() const
        {
            return channel;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            channel = ReadString(iter, length);
            data = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(channel, container);
            WriteByteArray(data, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["channel"] = picojson::value(channel);
            object["data"] = picojson::value("Vector of " + std::to_string(data.size()) + " unsigned chars");

            return value;
        }

    private:
        std::string channel;
        std::vector<unsigned char> data;

    };
} //ProtocolCraft
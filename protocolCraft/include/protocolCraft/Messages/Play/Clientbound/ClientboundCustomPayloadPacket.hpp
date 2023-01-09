#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomPayloadPacket : public BaseMessage<ClientboundCustomPayloadPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x15;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Custom Payload";

        virtual ~ClientboundCustomPayloadPacket() override
        {

        }

        void SetIdentifier(const std::string& identifier_)
        {
            identifier = identifier_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }


        const std::string& GetIdentifier() const
        {
            return identifier;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            identifier = ReadData<std::string>(iter, length);
            data = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(identifier, container);
            WriteByteArray(data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;
            output["data"] = "Vector of " + std::to_string(data.size()) + " unsigned chars";

            return output;
        }

    private:
        std::string identifier;
        std::vector<unsigned char> data;

    };
} //ProtocolCraft

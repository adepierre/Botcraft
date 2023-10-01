#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/ClientInformation.hpp"

namespace ProtocolCraft
{
    class ServerboundClientInformationConfigurationPacket : public BaseMessage<ServerboundClientInformationConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x00;

        static constexpr std::string_view packet_name = "Client Information (Configuration)";

        virtual ~ServerboundClientInformationConfigurationPacket() override
        {

        }


        void SetClientInformation(const ClientInformation& client_information_)
        {
            client_information = client_information_;
        }


        const ClientInformation& GetClientInformation() const
        {
            return client_information;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            client_information = ReadData<ClientInformation>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<ClientInformation>(client_information, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["client_information"] = client_information;

            return output;
        }

    private:
        ClientInformation client_information;

    };
} //ProtocolCraft
#endif

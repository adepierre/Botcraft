#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/Plugins/PluginLoader.hpp"
#include "protocolCraft/Utilities/Plugins/PluginObject.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomPayloadConfigurationPacket : public BaseMessage<ServerboundCustomPayloadConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x01;

        static constexpr std::string_view packet_name = "Custom Payload (Configuration)";

        virtual ~ServerboundCustomPayloadConfigurationPacket() override
        {

        }

        void SetIdentifier(const std::string& identifier_)
        {
            identifier = identifier_;
        }

        void SetRawData(const std::vector<unsigned char>& raw_data_)
        {
            raw_data = raw_data_;
        }

        void SetParsedData(const std::shared_ptr<PluginObject>& parsed_data_)
        {
            parsed_data = parsed_data_;
        }


        const std::string& GetIdentifier() const
        {
            return identifier;
        }

        const std::vector<unsigned char>& GetRawData() const
        {
            return raw_data;
        }

        const std::shared_ptr<PluginObject>& GetParsedData() const
        {
            return parsed_data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            identifier = ReadData<std::string>(iter, length);
            parsed_data = CreateObjectFromPlugin(identifier.c_str());
            if (parsed_data == nullptr)
            {
                raw_data = ReadByteArray(iter, length, length);
            }
            else
            {
                raw_data.clear();
                unsigned long long int data_size = static_cast<unsigned long long int>(length);
                const unsigned char* data_ptr = &(*iter);
                parsed_data->Read(data_ptr, data_size);
                iter += length - data_size;
                length = static_cast<size_t>(data_size);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(identifier, container);
            if (parsed_data == nullptr)
            {
                WriteByteArray(raw_data, container);
            }
            else
            {
                unsigned long long int serialized_length = 0;
                const unsigned char* serialized = parsed_data->Write(serialized_length);
                WriteByteArray(serialized, static_cast<size_t>(serialized_length), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["identifier"] = identifier;
            if (parsed_data == nullptr)
            {
                output["data"] = "Vector of " + std::to_string(raw_data.size()) + " unsigned chars";
            }
            else
            {
                const std::string json_serialized(parsed_data->Serialize());
                output["data"] = Json::Parse(json_serialized);
            }

            return output;
        }

    private:
        std::string identifier;
        std::vector<unsigned char> raw_data;
        std::shared_ptr<PluginObject> parsed_data;

    };
} //ProtocolCraft
#endif

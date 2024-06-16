#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/Plugins/PluginLoader.hpp"
#include "protocolCraft/Utilities/Plugins/PluginObject.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomPayloadConfigurationPacket : public BaseMessage<ServerboundCustomPayloadConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x02;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Custom Payload (Configuration)";

        DECLARE_FIELDS_TYPES(std::string, std::vector<unsigned char>, std::shared_ptr<PluginObject>);
        DECLARE_FIELDS_NAMES(Identifier,  RawData,                    ParsedData);

        GETTER_SETTER(Identifier);
        GETTER_SETTER(RawData);
        GETTER_SETTER(ParsedData);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetIdentifier(ReadData<std::string>(iter, length));
            SetParsedData(CreateObjectFromPlugin(GetIdentifier().c_str()));
            if (GetParsedData() == nullptr)
            {
                SetRawData(ReadByteArray(iter, length, length));
            }
            else
            {
                SetRawData({});
                unsigned long long int data_size = static_cast<unsigned long long int>(length);
                const unsigned char* data_ptr = &(*iter);
                GetParsedData()->Read(data_ptr, data_size);
                iter += length - data_size;
                length = static_cast<size_t>(data_size);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(GetIdentifier(), container);
            if (GetParsedData() == nullptr)
            {
                WriteByteArray(GetRawData(), container);
            }
            else
            {
                unsigned long long int serialized_length = 0;
                const unsigned char* serialized = GetParsedData()->Write(serialized_length);
                WriteByteArray(serialized, static_cast<size_t>(serialized_length), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Identifier)])] = GetIdentifier();
            if (GetParsedData() == nullptr)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::RawData)])] = "Vector of " + std::to_string(GetRawData().size()) + " unsigned chars";
            }
            else
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ParsedData)])] = Json::Parse(GetParsedData()->Serialize());
            }

            return output;
        }
    };
} //ProtocolCraft
#endif

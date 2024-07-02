#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/Plugins/PluginLoader.hpp"
#include "protocolCraft/Utilities/Plugins/PluginObject.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomPayloadPacket : public BaseMessage<ServerboundCustomPayloadPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Custom Payload";

        DECLARE_FIELDS(
            (std::string, Internal::Vector<unsigned char, void, 0>, std::shared_ptr<PluginObject>),
            (Identifier,  RawData,                                  ParsedData)
        );

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
                SetRawData(ReadData<Internal::Vector<unsigned char, void, 0>>(iter, length));
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
                WriteData<Internal::Vector<unsigned char, void, 0>>(GetRawData(), container);
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

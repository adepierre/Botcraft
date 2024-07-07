#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/Plugins/PluginLoader.hpp"
#include "protocolCraft/Utilities/Plugins/PluginObject.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomPayloadConfigurationPacket : public BaseMessage<ClientboundCustomPayloadConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Custom Payload (Configuration)";

    private:
        std::shared_ptr<PluginObject> ReadParsed(ReadIterator& iter, size_t& length) const
        {
            std::shared_ptr<PluginObject> parsed = CreateObjectFromPlugin(GetIdentifier().c_str());
            if (parsed != nullptr)
            {
                unsigned long long int data_size = static_cast<unsigned long long int>(length);
                const unsigned char* data_ptr = &(*iter);
                parsed->Read(data_ptr, data_size);
                iter += length - data_size;
                length = static_cast<size_t>(data_size);
            }

            return parsed;
        }

        void WriteParsed(const std::shared_ptr<PluginObject>& parsed, WriteContainer& container) const
        {
            if (parsed == nullptr)
            {
                return;
            }
            unsigned long long int serialized_length = 0;
            const unsigned char* serialized = parsed->Write(serialized_length);
            WriteByteArray(serialized, static_cast<size_t>(serialized_length), container);
        }

        std::optional<Json::Value> SerializeParsed(const std::shared_ptr<PluginObject>& parsed) const
        {
            if (parsed == nullptr)
            {
                return std::nullopt;
            }
            return Json::Parse(parsed->Serialize());
        }

        DECLARE_CONDITION(ParsedDataNull, GetParsedData() == nullptr);

        DECLARE_FIELDS(
            (std::string, Internal::CustomType<std::shared_ptr<PluginObject>, &THIS::ReadParsed, &THIS::WriteParsed, &THIS::SerializeParsed>, Internal::Conditioned<Internal::Vector<unsigned char, void, 0>, &THIS::ParsedDataNull>),
            (Identifier,  ParsedData,                                                                                                         RawData)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Identifier);
        GETTER_SETTER(ParsedData);
        GETTER_SETTER(RawData);
    };
} //ProtocolCraft
#endif

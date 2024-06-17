#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/Plugins/PluginLoader.hpp"
#include "protocolCraft/Utilities/Plugins/PluginObject.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomPayloadPacket : public BaseMessage<ClientboundCustomPayloadPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x19;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Custom Payload";

        DECLARE_FIELDS(
            (std::string, std::vector<unsigned char>, std::shared_ptr<PluginObject>),
            (Identifier,  RawData,                    ParsedData)
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

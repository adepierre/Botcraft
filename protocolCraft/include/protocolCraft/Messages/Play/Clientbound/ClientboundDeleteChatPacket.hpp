#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundDeleteChatPacket : public BaseMessage<ClientboundDeleteChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x1C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Delete Chat";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(MessageSignature);
        DECLARE_READ_WRITE_SERIALIZE;
#else
        // TODO: That looks like a Holder<std::array<unsigned char, 256>>
        DECLARE_FIELDS_TYPES(VarInt,             std::array<unsigned char, 256>);
        DECLARE_FIELDS_NAMES(MessageSignatureId, MessageSignature);
#endif

        GETTER_SETTER(MessageSignature);
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(MessageSignatureId);
#endif

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetMessageSignatureId(ReadData<VarInt>(iter, length) - 1);
            if (GetMessageSignatureId() == -1)
            {
                SetMessageSignature(ReadData<std::array<unsigned char, 256>>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetMessageSignatureId() + 1, container);
            if (GetMessageSignatureId() == -1)
            {
                WriteData<std::array<unsigned char, 256>>(GetMessageSignature(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::MessageSignatureId)])] = GetMessageSignatureId();
            if (GetMessageSignatureId() == -1)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::MessageSignature)])] = "Vector of " + std::to_string(GetMessageSignature().size()) + " unsigned char";
            }

            return output;
        }
#endif
    };
} //ProtocolCraft
#endif

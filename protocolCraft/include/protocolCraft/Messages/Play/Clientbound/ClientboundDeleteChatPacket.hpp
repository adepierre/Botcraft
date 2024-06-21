#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundDeleteChatPacket : public BaseMessage<ClientboundDeleteChatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Delete Chat";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::vector<unsigned char>),
            (MessageSignature)
        );
        DECLARE_READ_WRITE_SERIALIZE;
#else
        // TODO: That looks like a Holder<std::array<unsigned char, 256>>
        DECLARE_FIELDS(
            (VarInt,             std::array<unsigned char, 256>),
            (MessageSignatureId, MessageSignature)
        );
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

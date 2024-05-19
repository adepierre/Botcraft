#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
#include "protocolCraft/Types/SaltSignature.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatSender.hpp"
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include "protocolCraft/Types/Chat/PlayerChatMessage.hpp"
#else
#include "protocolCraft/Types/Chat/SignedMessageBody.hpp"
#include "protocolCraft/Types/Chat/FilterMask.hpp"
#endif
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"
#endif


namespace ProtocolCraft
{
    class ClientboundPlayerChatPacket : public BaseMessage<ClientboundPlayerChatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x39;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Chat";

        virtual ~ClientboundPlayerChatPacket() override
        {

        }

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        void SetSignedContent(const Chat& signed_content_)
        {
            signed_content = signed_content_;
        }

        void SetUnsignedContent(const std::optional<Chat>& unsigned_content_)
        {
            unsigned_content = unsigned_content_;
        }

        void SetTypeId(const int type_id_)
        {
            type_id = type_id_;
        }

        void SetSender(const ChatSender& sender_)
        {
            sender = sender_;
        }

        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

        void SetSaltSignature(const SaltSignature& salt_signature_)
        {
            salt_signature = salt_signature_;
        }


        const Chat& GetSignedContent() const
        {
            return signed_content;
        }

        const std::optional<Chat>& GetUnsignedContent() const
        {
            return unsigned_content;
        }

        int GetTypeId() const
        {
            return type_id;
        }

        const ChatSender& GetSender() const
        {
            return sender;
        }

        long long int GetTimestamp() const
        {
            return timestamp;
        }

        const SaltSignature& GetSaltSignature()
        {
            return salt_signature;
        }
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetMessage(const PlayerChatMessage& message_)
        {
            message = message_;
        }
#else
        void SetSender(const UUID& sender_)
        {
            sender = sender_;
        }

        void SetIndex(const int index_)
        {
            index = index_;
        }

        void SetSignature(const std::optional<std::array<unsigned char, 256>>& signature_)
        {
            signature = signature_;
        }

        void SetBody(const SignedMessageBody& body_)
        {
            body = body_;
        }

        void SetUnsignedContent(const std::optional<Chat>& unsigned_content_)
        {
            unsigned_content = unsigned_content_;
        }

        void SetFilterMask(const FilterMask& filter_mask_)
        {
            filter_mask = filter_mask_;
        }
#endif

        void SetChatType(const ChatTypeBoundNetwork& chat_type_)
        {
            chat_type = chat_type_;
        }


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        const PlayerChatMessage& GetMessage_() const
        {
            return message;
        }
#else
        const UUID& GetSender() const
        {
            return sender;
        }

        int GetIndex() const
        {
            return index;
        }

        const std::optional<std::array<unsigned char, 256>>& GetSignature() const
        {
            return signature;
        }

        const SignedMessageBody& GetBody() const
        {
            return body;
        }

        const std::optional<Chat>& GetUnsignedContent() const
        {
            return unsigned_content;
        }

        const FilterMask& GetFilterMask() const
        {
            return filter_mask;
        }
#endif

        const ChatTypeBoundNetwork& GetChatType() const
        {
            return chat_type;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
            signed_content = ReadData<Chat>(iter, length);
            unsigned_content = ReadData<std::optional<Chat>>(iter, length);
            type_id = ReadData<VarInt>(iter, length);
            sender = ReadData<ChatSender>(iter, length);
            timestamp = ReadData<long long int>(iter, length);
            salt_signature = ReadData<SaltSignature>(iter, length);
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            message = ReadData<PlayerChatMessage>(iter, length);
#else
            sender = ReadData<UUID>(iter, length);
            index = ReadData<VarInt>(iter, length);
            signature = ReadData<std::optional<std::array<unsigned char, 256>>>(iter, length);
            body = ReadData<SignedMessageBody>(iter, length);
            unsigned_content = ReadData<std::optional<Chat>>(iter, length);
            filter_mask = ReadData<FilterMask>(iter, length);
#endif
            chat_type = ReadData<ChatTypeBoundNetwork>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
            WriteData<Chat>(signed_content, container);
            WriteOptional<Chat>(unsigned_content, container);
            WriteData<VarInt>(type_id, container);
            WriteData<ChatSender>(sender, container);
            WriteData<long long int>(timestamp, container);
            WriteData<SaltSignature>(salt_signature, container);
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<PlayerChatMessage>(message, container);
#else
            WriteData<UUID>(sender, container);
            WriteData<VarInt>(index, container);
            WriteData<std::optional<std::array<unsigned char, 256>>>(signature, container);
            WriteData<SignedMessageBody>(body, container);
            WriteData<std::optional<Chat>>(unsigned_content, container);
            WriteData<FilterMask>(filter_mask, container);
#endif
            WriteData<ChatTypeBoundNetwork>(chat_type, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
            output["signed_content"] = signed_content;
            if (unsigned_content.has_value())
            {
                output["unsigned_content"] = unsigned_content.value();
            }
            output["type_id"] = type_id;
            output["sender"] = sender;
            output["timestamp"] = timestamp;
            output["salt_signature"] = salt_signature;
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["message"] = message;
#else
            output["sender"] = sender;
            output["index"] = index;
            if (signature.has_value())
            {
                output["signature"] = "Vector of " + std::to_string(signature.value().size()) + " unsigned chars.";
            }
            output["body"] = body;
            if (!unsigned_content.has_value())
            {
                output["unsigned_content"] = unsigned_content.value();
            }
            output["filter_mask"] = filter_mask;
#endif
            output["chat_type"] = chat_type;
#endif


            return output;
        }

    private:
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        Chat signed_content;
        std::optional<Chat> unsigned_content;
        int type_id = 0;
        ChatSender sender;
        long long int timestamp = 0;
        SaltSignature salt_signature;
#else
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        PlayerChatMessage message;
#else
        UUID sender = {};
        int index = 0;
        std::optional<std::array<unsigned char, 256>> signature;
        SignedMessageBody body;
        std::optional<Chat> unsigned_content;
        FilterMask filter_mask;
#endif
        ChatTypeBoundNetwork chat_type;
#endif
    };
} //ProtocolCraft
#endif

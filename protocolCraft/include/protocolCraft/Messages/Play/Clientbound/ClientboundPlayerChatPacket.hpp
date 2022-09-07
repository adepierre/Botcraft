#if PROTOCOL_VERSION > 758
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 760
#include "protocolCraft/Types/SaltSignature.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatSender.hpp"
#else
#include "protocolCraft/Types/Chat/PlayerChatMessage.hpp"
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"
#endif


namespace ProtocolCraft
{
    class ClientboundPlayerChatPacket : public BaseMessage<ClientboundPlayerChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x30;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x33;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Chat";
        }

        virtual ~ClientboundPlayerChatPacket() override
        {

        }

#if PROTOCOL_VERSION < 760
        void SetSignedContent(const Chat& signed_content_)
        {
            signed_content = signed_content_;
        }

        void SetUnsignedContent(const Chat& unsigned_content_)
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

        const Chat& GetUnsignedContent() const
        {
            return unsigned_content;
        }

        const int GetTypeId() const
        {
            return type_id;
        }

        const ChatSender& GetSender() const
        {
            return sender;
        }

        const long long int GetTimestamp() const
        {
            return timestamp;
        }

        const SaltSignature& GetSaltSignature()
        {
            return salt_signature;
        }
#else
        void SetMessage(const PlayerChatMessage& message_)
        {
            message = message_;
        }

        void SetChatType(const ChatTypeBoundNetwork& chat_type_)
        {
            chat_type = chat_type_;
        }


        const PlayerChatMessage& GetMessage_() const
        {
            return message;
        }

        const ChatTypeBoundNetwork& GetChatType() const
        {
            return chat_type;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 760
            signed_content.Read(iter, length);
            const bool has_unsigned_content = ReadData<bool>(iter, length);
            unsigned_content = Chat();
            if (has_unsigned_content)
            {
                unsigned_content.Read(iter, length);
            }
            type_id = ReadData<VarInt>(iter, length);
            sender.Read(iter, length);
            timestamp = ReadData<long long int>(iter, length);
            salt_signature.Read(iter, length);
#else
            message.Read(iter, length);
            chat_type.Read(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION < 760
            signed_content.Write(container);
            WriteData<bool>(!unsigned_content.GetRawText().empty(), container);
            if (!unsigned_content.GetRawText().empty())
            {
                unsigned_content.Write(container);
            }
            WriteData<VarInt>(type_id, container);
            sender.Write(container);
            WriteData<long long int>(timestamp, container);
            salt_signature.Write(container);
#else
            message.Write(container);
            chat_type.Write(container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 760
            output["signed_content"] = signed_content.Serialize();
            if (!unsigned_content.GetRawText().empty())
            {
                output["unsigned_content"] = unsigned_content.Serialize();
            }
            output["type_id"] = type_id;
            output["sender"] = sender.Serialize();
            output["timestamp"] = timestamp;
            output["salt_signature"] = salt_signature.Serialize();
#else
            output["message"] = message.Serialize();
            output["chat_type"] = chat_type.Serialize();
#endif


            return output;
        }

    private:
#if PROTOCOL_VERSION < 760
        Chat signed_content;
        Chat unsigned_content;
        int type_id;
        ChatSender sender;
        long long int timestamp;
        SaltSignature salt_signature;
#else
        PlayerChatMessage message;
        ChatTypeBoundNetwork chat_type;
#endif
    };
} //ProtocolCraft
#endif

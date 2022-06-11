#if PROTOCOL_VERSION > 758
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/SaltSignature.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatSender.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerChatPacket : public BaseMessage<ClientboundPlayerChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x30;
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

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
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
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
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
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["signed_content"] = signed_content.Serialize();
            if (!unsigned_content.GetRawText().empty())
            {
                output["unsigned_content"] = unsigned_content.Serialize();
            }
            output["type_id"] = type_id;
            output["sender"] = sender.Serialize();
            output["timestamp"] = timestamp;
            output["salt_signature"] = salt_signature.Serialize();


            return output;
        }

    private:
        Chat signed_content;
        Chat unsigned_content;
        int type_id;
        ChatSender sender;
        long long int timestamp;
        SaltSignature salt_signature;
    };
} //ProtocolCraft
#endif

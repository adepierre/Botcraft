#pragma once

#if PROTOCOL_VERSION > 758
#include <string>

#if PROTOCOL_VERSION < 760
#include "protocolCraft/Types/SaltSignature.hpp"
#else
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif
#endif
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPacket : public BaseMessage<ServerboundChatPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Chat";

        virtual ~ServerboundChatPacket() override
        {

        }

        void SetMessage(const std::string &s)
        {
            message = s;
        }

#if PROTOCOL_VERSION > 758
        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

#if PROTOCOL_VERSION < 760
        void SetSaltSignature(const SaltSignature& salt_signature_)
        {
            salt_signature = salt_signature_;
        }

#else
        void SetSalt(const long long int salt_)
        {
            salt = salt_;
        }

#if PROTOCOL_VERSION < 761
        void SetSignature(const std::vector<unsigned char>& signature_)
        {
            signature = signature_;
        }
#else
        void SetSignature(const std::optional<std::vector<unsigned char>>& signature_)
        {
            signature = signature_;
        }
#endif
#endif

#if PROTOCOL_VERSION < 761
        void SetSignedPreview(const bool signed_preview_)
        {
            signed_preview = signed_preview_;
        }
#endif
#endif

#if PROTOCOL_VERSION > 759
        void SetLastSeenMessages(const LastSeenMessagesUpdate& last_seen_messages_)
        {
            last_seen_messages = last_seen_messages_;
        }
#endif


        const std::string& GetMessage() const
        {
            return message;
        }

#if PROTOCOL_VERSION > 758
        long long int GetTimestamp() const
        {
            return timestamp;
        }

#if PROTOCOL_VERSION < 760
        const SaltSignature& GetSaltSignature() const
        {
            return salt_signature;
        }
#else
        long long int GetSalt() const
        {
            return salt;
        }

#if PROTOCOL_VERSION < 761
        const std::vector<unsigned char>& GetSignature() const
        {
            return signature;
        }
#else
        const std::optional<std::vector<unsigned char>>& GetSignature() const
        {
            return signature;
        }
#endif
#endif

#if PROTOCOL_VERSION < 761
        bool GetSignedPreview() const
        {
            return signed_preview;
        }
#endif
#endif
#if PROTOCOL_VERSION > 759
        const LastSeenMessagesUpdate& GetLastSeenMessages() const
        {
            return last_seen_messages;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            message = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 758
            timestamp = ReadData<long long int>(iter, length);
#if PROTOCOL_VERSION < 760
            salt_signature = ReadData<SaltSignature>(iter, length);
#else
            salt = ReadData<long long int>(iter, length);
#if PROTOCOL_VERSION < 761
            signature = ReadVector<unsigned char>(iter, length);
#else
            signature = ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadByteArray(i, l, 256);
                }
            );
#endif
#endif
#if PROTOCOL_VERSION < 761
            signed_preview = ReadData<bool>(iter, length);
#endif
#endif
#if PROTOCOL_VERSION > 759
            last_seen_messages = ReadData<LastSeenMessagesUpdate>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(message, container);
#if PROTOCOL_VERSION > 758
            WriteData<long long int>(timestamp, container);
#if PROTOCOL_VERSION < 760
            WriteData<SaltSignature>(salt_signature, container);
#else
            WriteData<long long int>(salt, container);

#if PROTOCOL_VERSION < 761
            WriteVector<unsigned char>(signature, container);
#else
            WriteOptional<std::vector<unsigned char>>(signature, container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                }
            );
#endif
#endif
#if PROTOCOL_VERSION < 761
            WriteData<bool>(signed_preview, container);
#endif
#endif
#if PROTOCOL_VERSION > 759
            WriteData<LastSeenMessagesUpdate>(last_seen_messages, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["message"] = message;
#if PROTOCOL_VERSION > 758
            output["timestamp"] = timestamp;
#if PROTOCOL_VERSION < 760
            output["salt_signature"] = salt_signature;
#else
            output["salt"] = salt;
#if PROTOCOL_VERSION < 761
            output["signature"] = "Vector of " + std::to_string(signature.size()) + " unsigned char";
#else
            if (signature.has_value())
            {
                output["signature"] = "Vector of " + std::to_string(signature.value().size()) + " unsigned char";
            }
#endif
#endif
#if PROTOCOL_VERSION < 761
            output["signed_preview"] = signed_preview;
#endif
#endif
#if PROTOCOL_VERSION > 759
            output["last_seen_messages"] = last_seen_messages;
#endif

            return output;
        }

    private:
        std::string message;
#if PROTOCOL_VERSION > 758
        long long int timestamp;
#if PROTOCOL_VERSION < 760
        SaltSignature salt_signature;
#else
        long long int salt;
#if PROTOCOL_VERSION < 761
        std::vector<unsigned char> signature;
#else
        std::optional<std::vector<unsigned char>> signature;
#endif
#endif
#if PROTOCOL_VERSION < 761
        bool signed_preview;
#endif
#endif
#if PROTOCOL_VERSION > 759
        LastSeenMessagesUpdate last_seen_messages;
#endif
    };
} //ProtocolCraft

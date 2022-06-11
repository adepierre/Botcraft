#pragma once

#if PROTOCOL_VERSION > 758
#include <string>

#include "protocolCraft/Types/SaltSignature.hpp"
#endif
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPacket : public BaseMessage<ServerboundChatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x02;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x02;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x03;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x03;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x03;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x03;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x03;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x03;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x04;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat";
        }

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

        void SetSaltSignature(const SaltSignature& salt_signature_)
        {
            salt_signature = salt_signature_;
        }

        void SetSignedPreview(const bool signed_preview_)
        {
            signed_preview = signed_preview_;
        }
#endif


        const std::string& GetMessage() const
        {
            return message;
        }

#if PROTOCOL_VERSION > 758
        const long long int GetTimestamp() const
        {
            return timestamp;
        }

        const SaltSignature& GetSaltSignature() const
        {
            return salt_signature;
        }

        const bool GetSignedPreview() const
        {
            return signed_preview;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            message = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 758
            timestamp = ReadData<long long int>(iter, length);
            salt_signature.Read(iter, length);
            signed_preview = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(message, container);
#if PROTOCOL_VERSION > 758
            WriteData<long long int>(timestamp, container);
            salt_signature.Write(container);
            WriteData<bool>(signed_preview, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["message"] = message;
#if PROTOCOL_VERSION > 758
            output["timestamp"] = timestamp;
            output["salt_signature"] = salt_signature.Serialize();
            output["signed_preview"] = signed_preview;
#endif

            return output;
        }

    private:
        std::string message;
#if PROTOCOL_VERSION > 758
        long long int timestamp;
        SaltSignature salt_signature;
        bool signed_preview;
#endif
    };
} //ProtocolCraft

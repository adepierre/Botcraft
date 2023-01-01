#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 754
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundResourcePackPacket : public BaseMessage<ClientboundResourcePackPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x34;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x37;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x39;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x39;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x38;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x3C;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x3C;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x3A;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x3D;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x3C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Ressource Pack";
        }

        virtual ~ClientboundResourcePackPacket() override
        {

        }

        void SetUrl(const std::string& url_)
        {
            url = url_;
        }

        void SetHash(const std::string& hash_)
        {
            hash = hash_;
        }

#if PROTOCOL_VERSION > 754
        void SetRequired(const bool required_)
        {
            required = required_;
        }

        void SetPrompt(const Chat& prompt_)
        {
            prompt = prompt_;
        }
#endif


        const std::string& GetUrl() const
        {
            return url;
        }

        const std::string& GetHash() const
        {
            return hash;
        }

#if PROTOCOL_VERSION > 754
        const bool GetRequired() const
        {
            return required;
        }

        const Chat& GetPrompt() const
        {
            return prompt;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            url = ReadData<std::string>(iter, length);
            hash = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 754
            required = ReadData<bool>(iter, length);
            const bool has_prompt = ReadData<bool>(iter, length);
            if (has_prompt)
            {
                prompt = ReadData<Chat>(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(url, container);
            WriteData<std::string>(hash, container);
#if PROTOCOL_VERSION > 754
            WriteData<bool>(required, container);
            if (prompt.GetRawText().empty())
            {
                WriteData<bool>(false, container);
            }
            else
            {
                WriteData<bool>(true, container);
                WriteData<Chat>(prompt, container);
            }
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["url"] = url;
            output["hash"] = hash;
#if PROTOCOL_VERSION > 754
            output["required"] = required;
            output["prompt"] = prompt.Serialize();
#endif

            return output;
        }

    private:
        std::string url;
        std::string hash;
#if PROTOCOL_VERSION > 754
        bool required;
        Chat prompt;
#endif

    };
} //ProtocolCraft
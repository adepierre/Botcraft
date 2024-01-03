#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */ && PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackConfigurationPacket : public BaseMessage<ClientboundResourcePackConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x06;

        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

        virtual ~ClientboundResourcePackConfigurationPacket() override
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

        void SetRequired(const bool required_)
        {
            required = required_;
        }

        void SetPrompt(const std::optional<Chat>& prompt_)
        {
            prompt = prompt_;
        }


        const std::string& GetUrl() const
        {
            return url;
        }

        const std::string& GetHash() const
        {
            return hash;
        }

        bool GetRequired() const
        {
            return required;
        }

        const std::optional<Chat>& GetPrompt() const
        {
            return prompt;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            url = ReadData<std::string>(iter, length);
            hash = ReadData<std::string>(iter, length);
            required = ReadData<bool>(iter, length);
            prompt = ReadOptional<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(url, container);
            WriteData<std::string>(hash, container);
            WriteData<bool>(required, container);
            WriteOptional<Chat>(prompt, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["url"] = url;
            output["hash"] = hash;
            output["required"] = required;
            if (prompt.has_value())
            {
                output["prompt"] = prompt.value();
            }

            return output;
        }

    private:
        std::string url;
        std::string hash;
        bool required = false;
        std::optional<Chat> prompt;
    };
} //ProtocolCraft
#endif

#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundResourcePackPacket : public BaseMessage<ClientboundResourcePackPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x42;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ressource Pack";

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

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        void SetRequired(const bool required_)
        {
            required = required_;
        }

        void SetPrompt(const std::optional<Chat>& prompt_)
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

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        bool GetRequired() const
        {
            return required;
        }

        const std::optional<Chat>& GetPrompt() const
        {
            return prompt;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            url = ReadData<std::string>(iter, length);
            hash = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
            required = ReadData<bool>(iter, length);
            prompt = ReadOptional<Chat>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(url, container);
            WriteData<std::string>(hash, container);
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
            WriteData<bool>(required, container);
            WriteOptional<Chat>(prompt, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["url"] = url;
            output["hash"] = hash;
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
            output["required"] = required;
            if (prompt.has_value())
            {
                output["prompt"] = prompt.value();
            }
#endif

            return output;
        }

    private:
        std::string url;
        std::string hash;
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        bool required = false;
        std::optional<Chat> prompt;
#endif

    };
} //ProtocolCraft

#if PROTOCOL_VERSION > 758
#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundServerDataPacket : public BaseMessage<ClientboundServerDataPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x3F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x42;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x41;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Server Data";
        }

        virtual ~ClientboundServerDataPacket() override
        {

        }


        void SetMotd(const Chat& motd_)
        {
            motd = motd_;
        }

        void SetIconBase64(const std::string& icon_base_64_)
        {
            icon_base_64 = icon_base_64_;
        }

#if PROTOCOL_VERSION < 761
        void SetPreviewsChat(const bool previews_chat_)
        {
            previews_chat = previews_chat_;
        }
#endif

#if PROTOCOL_VERSION > 759
        void SetEnforcesSecureChat(const bool enforces_secure_chat_)
        {
            enforces_secure_chat = enforces_secure_chat_;
        }
#endif


        const Chat& GetMotd() const
        {
            return motd;
        }

        const std::string& GetIconBase64() const
        {
            return icon_base_64;
        }

#if PROTOCOL_VERSION < 761
        const bool GetPreviewsChat() const
        {
            return previews_chat;
        }
#endif

#if PROTOCOL_VERSION > 759
        const bool GetEnforcesSecureChat() const
        {
            return enforces_secure_chat;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const bool has_motd = ReadData<bool>(iter, length);
            motd = Chat();
            if (has_motd)
            {
                motd = ReadData<Chat>(iter, length);
            }
            const bool has_icon_base_64 = ReadData<bool>(iter, length);
            icon_base_64 = "";
            if (has_icon_base_64)
            {
                icon_base_64 = ReadData<std::string>(iter, length);
            }
#if PROTOCOL_VERSION < 761
            previews_chat = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 759
            enforces_secure_chat = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(!motd.GetRawText().empty(), container);
            if (!motd.GetRawText().empty())
            {
                WriteData<Chat>(motd, container);
            }
            WriteData<bool>(!icon_base_64.empty(), container);
            if (!icon_base_64.empty())
            {
                WriteData<std::string>(icon_base_64, container);
            }
#if PROTOCOL_VERSION < 761
            WriteData<bool>(previews_chat, container);
#endif
#if PROTOCOL_VERSION > 759
            WriteData<bool>(enforces_secure_chat, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            if (!motd.GetRawText().empty())
            {
                output["motd"] = motd.Serialize();
            }
            if (!icon_base_64.empty())
            {
                output["icon_base_64"] = icon_base_64;
            }
#if PROTOCOL_VERSION < 761
            output["previews_chat"] = previews_chat;
#endif
#if PROTOCOL_VERSION > 759
            output["enforces_secure_chat"] = enforces_secure_chat;
#endif


            return output;
        }

    private:
        Chat motd;
        std::string icon_base_64;
#if PROTOCOL_VERSION < 761
        bool previews_chat;
#endif
#if PROTOCOL_VERSION > 759
        bool enforces_secure_chat;
#endif

    };
} //ProtocolCraft
#endif

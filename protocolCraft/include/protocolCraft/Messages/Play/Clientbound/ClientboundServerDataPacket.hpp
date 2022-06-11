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

        void SetPreviewsChat(const bool previews_chat_)
        {
            previews_chat = previews_chat_;
        }


        const Chat& GetMotd() const
        {
            return motd;
        }

        const std::string& GetIconBase64() const
        {
            return icon_base_64;
        }

        const bool GetPreviewsChat() const
        {
            return previews_chat;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const bool has_motd = ReadData<bool>(iter, length);
            motd = Chat();
            if (has_motd)
            {
                motd.Read(iter, length);
            }
            const bool has_icon_base_64 = ReadData<bool>(iter, length);
            icon_base_64 = "";
            if (has_icon_base_64)
            {
                icon_base_64 = ReadData<std::string>(iter, length);
            }
            previews_chat = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(!motd.GetRawText().empty(), container);
            if (!motd.GetRawText().empty())
            {
                motd.Write(container);
            }
            WriteData<bool>(!icon_base_64.empty(), container);
            if (!icon_base_64.empty())
            {
                WriteData<std::string>(icon_base_64, container);
            }
            WriteData<bool>(previews_chat, container);
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
            output["previews_chat"] = previews_chat;


            return output;
        }

    private:
        Chat motd;
        std::string icon_base_64;
        bool previews_chat;

    };
} //ProtocolCraft
#endif

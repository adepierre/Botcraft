#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatTypeBoundNetwork : public NetworkType
    {
    public:
        virtual ~ChatTypeBoundNetwork() override
        {

        }

        void SetChatType(const int chat_type_)
        {
            chat_type = chat_type_;
        }

        void SetName(const Chat& name_)
        {
            name = name_;
        }

        void SetTargetName(const Chat& target_name_)
        {
            target_name = target_name_;
        }


        const int GetChatType() const
        {
            return chat_type;
        }

        const Chat& GetName() const
        {
            return name;
        }

        const Chat& GetTargetName() const
        {
            return target_name;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            chat_type = ReadData<VarInt>(iter, length);
            name.Read(iter, length);
            const bool has_target_name = ReadData<bool>(iter, length);
            if (has_target_name)
            {
                target_name.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(chat_type, container);
            name.Write(container);
            WriteData<bool>(!target_name.GetRawText().empty(), container);
            if (!target_name.GetRawText().empty())
            {
                target_name.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["chat_type"] = chat_type;
            output["name"] = name.Serialize();
            if (!target_name.GetRawText().empty())
            {
                output["target_name"] = target_name.Serialize();
            }


            return output;
        }

    private:
        int chat_type;
        Chat name;
        Chat target_name;
    };
}
#endif

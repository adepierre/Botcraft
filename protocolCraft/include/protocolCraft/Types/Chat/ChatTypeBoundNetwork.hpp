#if PROTOCOL_VERSION > 759 /* > 1.19 */
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

        void SetTargetName(const std::optional<Chat>& target_name_)
        {
            target_name = target_name_;
        }


        int GetChatType() const
        {
            return chat_type;
        }

        const Chat& GetName() const
        {
            return name;
        }

        const std::optional<Chat>& GetTargetName() const
        {
            return target_name;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            chat_type = ReadData<VarInt>(iter, length);
            name = ReadData<Chat>(iter, length);
            target_name = ReadOptional<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(chat_type, container);
            WriteData<Chat>(name, container);
            WriteOptional<Chat>(target_name, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["chat_type"] = chat_type;
            output["name"] = name;
            if (target_name.has_value())
            {
                output["target_name"] = target_name.value();
            }


            return output;
        }

    private:
        int chat_type = 0;
        Chat name;
        std::optional<Chat> target_name;
    };
}
#endif

#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatMessageContent : public NetworkType
    {
    public:
        virtual ~ChatMessageContent() override
        {

        }

        void SetPlain(const std::string& plain_)
        {
            plain = plain_;
        }

        void SetDecorated(const std::optional<Chat>& decorated_)
        {
            decorated = decorated_;
        }


        const std::string& GetPlain() const
        {
            return plain;
        }

        const std::optional<Chat>& GetDecorated() const
        {
            return decorated;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            plain = ReadData<std::string>(iter, length);
            decorated = ReadData<std::optional<Chat>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(plain, container);
            WriteData<std::optional<Chat>>(decorated, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["plain"] = plain;
            if (decorated.has_value())
            {
                output["decorated"] = decorated.value();
            }

            return output;
        }

    private:
        std::string plain;
        std::optional<Chat> decorated;
    };
}
#endif

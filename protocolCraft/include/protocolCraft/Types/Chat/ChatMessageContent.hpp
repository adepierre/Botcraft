#if PROTOCOL_VERSION > 759
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

        void SetDecorated(const Chat& decorated_)
        {
            decorated = decorated_;
        }


        const std::string& GetPlain() const
        {
            return plain;
        }

        const Chat& GetDecorated() const
        {
            return decorated;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            plain = ReadData<std::string>(iter, length);
            const bool has_decorated = ReadData<bool>(iter, length);
            if (has_decorated)
            {
                decorated.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(plain, container);
            WriteData<bool>(!decorated.GetRawText().empty(), container);
            if (!decorated.GetRawText().empty())
            {
                decorated.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["plain"] = plain;
            if (!decorated.GetRawText().empty())
            {
                output["decorated"] = decorated.Serialize();
            }

            return output;
        }

    private:
        std::string plain;
        Chat decorated;
    };
}
#endif

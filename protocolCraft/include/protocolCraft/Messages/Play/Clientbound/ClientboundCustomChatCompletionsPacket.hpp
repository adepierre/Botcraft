#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomChatCompletionsPacket : public BaseMessage<ClientboundCustomChatCompletionsPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x15;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Custom Chat Completion Packet";
        }

        virtual ~ClientboundCustomChatCompletionsPacket() override
        {

        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetEntries(const std::vector<std::string>& entries_)
        {
            entries = entries_;
        }


        const int GetAction() const
        {
            return action;
        }

        const std::vector<std::string>& GetEntries() const
        {
            return entries;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = ReadData<VarInt>(iter, length);
            entries = std::vector<std::string>(ReadData<VarInt>(iter, length));
            for (int i = 0; i < entries.size(); ++i)
            {
                entries[i] = ReadData<std::string>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(action, container);
            WriteData<VarInt>(entries.size(), container);
            for (int i = 0; i < entries.size(); ++i)
            {
                WriteData<std::string>(entries[i], container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["action"] = action;
            output["entries"] = entries;

            return output;
        }

    private:
        int action;
        std::vector<std::string> entries;

    };
} //ProtocolCraft
#endif

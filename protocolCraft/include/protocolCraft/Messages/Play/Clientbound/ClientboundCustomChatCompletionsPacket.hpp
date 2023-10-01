#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomChatCompletionsPacket : public BaseMessage<ClientboundCustomChatCompletionsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x17;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Custom Chat Completion Packet";

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


        int GetAction() const
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
            entries = ReadVector<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(action, container);
            WriteVector<std::string>(entries, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["action"] = action;
            output["entries"] = entries;

            return output;
        }

    private:
        int action = 0;
        std::vector<std::string> entries;

    };
} //ProtocolCraft
#endif
